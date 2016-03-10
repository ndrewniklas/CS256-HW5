//Andrew Niklas
//Homework 5
//Completed

#include <cmath>
#include <cstdlib>
#include <ctime>
#include<SDL2/SDL_ttf.h>


#include "Game.h"

Game::Game() 
	: width(DEFAULT_WIDTH), height(DEFAULT_HEIGHT), 
	  start(0), last(0), current(0), 
	  good(true), running(false), 
	  showStats(false), collisions(0), runTime(0), maxVelocity(0),
	  particles(std::vector<Particle>())
{
	// Seed the random number generator
	srand(time(0));
	
	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		good = false;
		return;
	}
	
	// initialize SDL window
	window = SDL_CreateWindow("Gravity", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		good = false;
		return;
	}
	
	// initialize SDL renderer
	renderer = SDL_CreateRenderer(window, -1, 
			SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		good = false;
		return;
	}
	
	// initialize particle texture
	SDL_Surface* bmp = SDL_LoadBMP("particle.bmp");
	if (bmp == NULL)
	{
		good = false;
		return;
	}
	particleTexture = SDL_CreateTextureFromSurface(renderer, bmp);
	SDL_FreeSurface(bmp);
	if (particleTexture == NULL)
	{
		good = false;
		return;
	}
	
	// initialize our particles
	for (int i = 0; i < PARTICLE_COUNT; ++i)
	{
		particles.push_back(randomParticle());
	}
	
	// initialize text printing
	TTF_Init();
	TTF_Font* font = TTF_OpenFont("arial.ttf", 12);
	SDL_Color textColor = { 255, 255, 255 };
}

Game::~Game()
{
	if (!good)
	{
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
	}
	if (particleTexture != NULL)
	{
		SDL_DestroyTexture(particleTexture);
	}
	if (renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}
	TTF_CloseFont(font);
    font = NULL;
	TTF_Quit();
	
	SDL_Quit();
}

int Game::operator()()
{
	if (!good)
	{
		return -1;
	}
	running = true;
	SDL_Event event;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	start = SDL_GetTicks();
	last = start;

	while (running) // every iteration is 1 frame
	{
		current = SDL_GetTicks();
		while (SDL_PollEvent(&event))
		{
			handleEvent(event);
		}
		update((current - last) / 1000.0);
		render();
		last = current;
	}
	//runTime = (SDL_GetTicks() - start) / 1000.0;
	//std::cout << "\n\n  End of Game Statistics  " << std::endl;
	//std::cout << "Collisions: " << collisions << std::endl;
	//std::cout << "Max Velocity: " << maxVelocity << std::endl;
	//std::cout << "Run time: " << runTime << " seconds" << std::endl;

	return 0;
}

// dt is time since last frame in seconds
void Game::update(double dt)
{
	std::cout << dt << " sec since last frame.\n";

	//point to hold acceleration
	Point a;
	
	
	// Replace with your game logic!
	int i = 0;
	for(Particle& p1 : particles){
		int j = 0;
		for(Particle& p2 : particles){
			if(&p1 != &p2){
				a = calcGrav(p1, p2, i, j);
				p1.updateVelocity(a, dt);
			}
			++j;
		}
		++i;
	}
	//check if at edge of window
	for(Particle& p : particles){
		boundaryChk(p);
	}
	//collision check using 2D bool array
	for(int i = 0; i < particles.size(); ++i){
		for(int j = 0; j < particles.size(); ++j){
			if(colliding[i][j]){
				collideCalc(particles[i], particles[j]);
				colliding[i][j] = false;
				colliding[j][i] = false;
			}
		}
	}
	//update position based on new velocity given dt
	for(Particle& p : particles){
		if(p.velocityMagnitude() > maxVelocity){
			maxVelocity = p.velocityMagnitude();
		}
		p.updatePos(dt);
	}
	
}

Point Game::calcGrav(Particle& p1, Particle& p2, const int i, const int j){
	Point pt1 = p1.getPos();
	Point pt2 = p2.getPos();
	
	double r = pt1.distance(pt2);
	if(r <= p1.getRadius() + p2.getRadius()){
		colliding[i][j] = true;
		
		double radiSum = p1.getRadius() + p2.getRadius();
		double overlap = radiSum - r;
		double angle = atan2(pt1.yDiff(pt2), pt1.xDiff(pt2));
		p1.fixPos((overlap/2), angle - PI);
		p2.fixPos((overlap/2), angle);
		
		return Point(0, 0);
	}else{
		colliding[i][j] = false;
	}
	double accel = G * (p2.getMass() / (r * r));
	
	double angle = atan2(pt1.yDiff(pt2), pt1.xDiff(pt2));
	return Point(accel * cos(angle), accel * sin(angle));	
}

void Game::boundaryChk(Particle& p){
	double r = p.getRadius();
	if(p.getPos().getX() - r <= 0){
		p.fixPos(p.getRadius() - 1, 0);
		p.negateVelocity('x');
	}
	if(p.getPos().getX() + r >= width){
		p.fixPos(p.getRadius() - 1, PI);
		p.negateVelocity('x');
	}
	if(p.getPos().getY() + r >= height){
		p.fixPos(p.getRadius() - 1, -PI/2);
		p.negateVelocity('y');
	}
	if(p.getPos().getY() - r <= 0){
		p.fixPos(p.getRadius() - 1, PI/2);
		p.negateVelocity('y');
	}
}

void Game::collideCalc(Particle& p1, Particle& p2){
	++collisions;
	// std::cout << "B O O M" << std::endl;
	double v1 = p1.velocityMagnitude();
	double v2 = p2.velocityMagnitude();
	double m1 = p1.getMass();
	double m2 = p2.getMass();
	double v1Angle = p1.velocityAngle();
	double v2Angle = p2.velocityAngle();
	double dy = p1.getPos().yDiff(p2.getPos());
	double dx = p1.getPos().xDiff(p2.getPos());
	double phi = atan2(dy, dx);
	// v1 calculations
	double v1Sub = (v1 * cos(v1Angle - phi) * (m1 - m2) + (2 * m2 * v2 * cos(v2Angle - phi))) / (m1 + m2);
	
	double v1x = (v1Sub * cos(phi)) + (v1 * sin(v1Angle - phi) * cos(phi + PI/2));
	
	double v1y = (v1Sub * sin(phi)) + (v1 * sin(v1Angle - phi) * sin(phi + PI/2));
	
	// v2 calculations
	phi += PI;
	double v2Sub = (v2 * cos(v2Angle - phi) * (m2 - m1) + (2 * m1 * v1 * cos(v1Angle - phi))) / (m1 + m2);
	
	double v2x = (v2Sub * cos(phi)) + (v2 * sin(v2Angle - phi) * cos(phi + PI/2));
	
	double v2y = (v2Sub * sin(phi)) + (v2 * sin(v2Angle - phi) * sin(phi + PI/2));
	
	// update velocities
	p1.updateVelocity(v1x, v1y);
	p2.updateVelocity(v2x, v2y);
}

void Game::render()
{
	SDL_RenderClear(renderer);
	
	// rendering here would place objects beneath the particles
	
	for (Particle& p : particles)
	{
		drawParticle(p);
	}
	
	// rendering here would place objects on top of the particles
	if(showStats){
		
		// printStats(getStats());
		std::string test = "This is a test!";
		printStats(font, test, textColor);
	}
	
	SDL_RenderPresent(renderer);
}

void Game::handleEvent(const SDL_Event& event)
{
	switch (event.type)
	{
	// Add your own event handling here if desired
	case SDL_QUIT:
		running = false;
		break;
	case SDL_KEYUP:
		if(event.key.keysym.sym == SDLK_ESCAPE){
			running = false;
		}else if(event.key.keysym.sym == SDLK_s){
			showStats = true;
		}
		break;
	default:
		break;
	}
}

void Game::drawParticle(Particle& p)
{
	SDL_Rect dst;
	double shift = p.getRadius();
	dst.x = (int) (p.getPos().getX() - shift);
	dst.y = (int) (p.getPos().getY() - shift);
	dst.w = shift * 2;
	dst.h = shift * 2;
	SDL_RenderCopy(renderer, particleTexture, NULL, &dst);
}

Particle Game::randomParticle() const
{
	Point pos(rand() % width, rand() % height);
	
	// using random percentage of MAX_MASS
	double mass = ((double) rand() / RAND_MAX) * MAX_MASS + 1.0;
	
	return Particle(pos, mass);
}

void Game::printStats(TTF_Font* font, std::string text, SDL_Color& textColor){
	
	std::cout << "loaded font" << std::endl;
	std::cout << (font == NULL ? "null" : "not null") << std::endl;
	
	// SDL_Color White = { 255, 255, 255 };
	std::cout << "set color" << std::endl;
	
	SDL_Surface* textSurface; 
	if(!(textSurface = TTF_RenderText_Solid(font, "text.c_str()", textColor))){
		std::cout << TTF_GetError() << std::endl;
	}
	std::cout << "created Surface Message" << std::endl;
	
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, textSurface);
	std::cout << "created texture" << std::endl;
	
	SDL_Rect Message_rect; //create a rect
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect
	Message_rect.x = 0; // DEFAULT_WIDTH - 100;  //controls the rect's x coordinate 
	Message_rect.y = 0; // DEFAULT_HEIGHT + 100; // controls the rect's y coordinte
	std::cout << "created rect" << std::endl;
	
	SDL_FreeSurface(textSurface);
	
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	//renderer's name, the Message, crop size, rect which is the size and coordinate of your texture
	std::cout << "render copy" << std::endl;

	SDL_DestroyTexture(Message);
}

std::string Game::getStats(){
	std::string statsText;
	
	runTime = (SDL_GetTicks() - start) / 1000.0;
	statsText.append("  Game Statistics  \nCollisions: ");
	statsText.append(std::to_string(collisions));
	statsText.append("\nMax Velocity: ");
	statsText.append(std::to_string(maxVelocity));
	statsText.append("\nRun time: ");
	statsText.append(std::to_string(runTime));
	statsText.append(" seconds");
	
	return statsText;	
}





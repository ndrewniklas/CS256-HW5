//Andrew Niklas
//Homework 5
//Completed

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Game.h"

Game::Game() 
	: width(DEFAULT_WIDTH), height(DEFAULT_HEIGHT), 
	  start(0), last(0), current(0), 
	  good(true), running(false), 
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

	return 0;
}

int Game::operator()(int n)
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

	char step;
	while (running){
		std::cin >> step;
		if(step == 'n') // every iteration is 1 frame
		{
			current = SDL_GetTicks();
			while (SDL_PollEvent(&event))
			{
				handleEvent(event);
			}
			update((current - last) / 1000.0);
			render();
			last = current;
		}else if (step == 'q'){
			running = false;
			return (1);
		}
	}

	return 0;
}

// dt is time since last frame in seconds
void Game::update(double dt)
{
	std::cout << dt << " sec since last frame.\n";

	Point a;
	
	// Replace with your game logic!
	for(Particle& p1 : particles){
		for(Particle& p2 : particles){
			if(&p1 != &p2){
				a = calcGrav(p1, p2);
				p1.updateVelocity(a, dt);
				
				//collision check using 2D bool array
			}
		}
	}
	for(Particle& p : particles){
		//check if at edge of window
		boundaryChk(p);
	}
	
	for(Particle& p : particles){		
		// update position based on new velocity given dt
		p.updatePos(a, dt);
	}
}

Point Game::calcGrav(Particle& p1, const Particle& p2){
	Point pt1 = p1.getPos();
	Point pt2 = p2.getPos();
	
	double r = pt1.distance(pt2);
	double accel = G * (p2.getMass() / r * r);
	
	double angle = atan2(pt1.xDiff(pt2), pt1.yDiff(pt2));
	return Point(accel * cos(angle), accel * sin(angle));	
}

void Game::boundaryChk(Particle& p){
	double r = p.getRadius();
	if(p.getPos().getX() - r <= 0 || p.getPos().getX() + r >= width){
		p.negateVelocity('x');
	}
	if(p.getPos().getY() + r >= height || p.getPos().getY() - r <= 0){
		p.negateVelocity('y');
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	
	// rendering here would place objects beneath the particles
	
	for (const Particle& p : particles)
	{
		drawParticle(p);
	}
	
	// rendering here would place objects on top of the particles
	
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
		}
	default:
		break;
	}
}

void Game::drawParticle(const Particle& p)
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

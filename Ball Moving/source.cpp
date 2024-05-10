
#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BALL_WIDTH = 70;
const int BALL_HEIGHT = 70;
const int BALL_SPEED = 5;

// Function to generate random number between min and max
int getRandom(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main(int argc, char* args[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Moving Ball", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Load ball image
    SDL_Texture* ballTexture = NULL;
    SDL_Surface* surface = IMG_Load("./Assets/football.png");
    if (surface == NULL) {
        printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
        return 1;
    }
    ballTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Set initial position of the ball
    int ballX = SCREEN_WIDTH / 2;
    int ballY = SCREEN_HEIGHT / 2;

    // Set initial velocity of the ball
    int velX = getRandom(-BALL_SPEED, BALL_SPEED);
    int velY = getRandom(-BALL_SPEED, BALL_SPEED);

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    // Main loop
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Move the ball
        ballX += velX;
        ballY += velY;

        // Check boundaries
        if (ballX < 0 || ballX + BALL_WIDTH > SCREEN_WIDTH) {
            velX = -velX;
            ballX += velX;
        }
        if (ballY < 0 || ballY + BALL_HEIGHT > SCREEN_HEIGHT) {
            velY = -velY;
            ballY += velY;
        }

        // Render the ball
        SDL_Rect ballRect = { ballX, ballY, BALL_WIDTH, BALL_HEIGHT };
        SDL_RenderCopy(renderer, ballTexture, NULL, &ballRect);

        // Update screen
        SDL_RenderPresent(renderer);

        // Delay to control frame rate
        SDL_Delay(30);
    }

    // Destroy texture, window, and renderer
    SDL_DestroyTexture(ballTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();

    return 0;
}

#pragma once

// Game of pong
void pongGame();

// Game of snake
void snakeGame();

// Compute the modulo operation supporting negative numbers, for example mod(-1,8)=7
int mod(int x, int N);

// Explosion animation from the given origin
void animate_explosion(int x, int y, float velocity);

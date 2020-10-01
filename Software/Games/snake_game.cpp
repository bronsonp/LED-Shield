#include "games.h"
#include "LED_Shield.h"
#include "Arduino.h"

extern LED_Shield led_shield;

#define max_snake_length 7

// List of directions (in clockwise order)
enum class direction {
  North = 0,
  East = 1,
  South = 2,
  West = 3
};

// Compute the next position ID in a given direction of motion, including wrap-around at the edges.
// The ID numbers are in the sequence:
//   7   6   5   4   3   2   1   0
//  15  14  13  12  11  10   9   8
//  23  22  21  20  19  18  17  16
//  31  30  29  28  27  26  25  24
int getNextPosition(int position, direction dir) 
{
  // convert to x,y coords
  // where x = [7 6 5 4 3 2 1 0] from left to right
  // and y = [0; 1; 2; 3] from top to bottom
  int x = position % 8;
  int y = position / 8;

  // move in the given direction
  if (dir == direction::North) {
    y = mod(y - 1, 4);
  } else if (dir == direction::South) {
    y = mod(y + 1, 4);
  } else if (dir == direction::East) {
    x = mod(x - 1, 8);
  } else if (dir == direction::West) {
    x = mod(x + 1, 8);
  }

  // convert back to position
  return x + 8*y;
}

// Run the snake game
void snakeGame()
{
  for (;;) {
    int i;
    unsigned long last_millis;
  
    // The length of the snake 
    int snake_length = 5;
    
    // The direction of the snake 
    direction snake_direction = direction::West;
    
    // The time in milliseconds between movements of the snake
    // Adjust this to make the game faster or slower 
    unsigned int delay_time = 200;
    
    // LED IDs occupied by the snake
    int snake_position [max_snake_length]; 
  
    // Between movements, read the next direction from the left joystick and store it here
    direction new_direction;
  
    // Initialise the snake
    for (i = 0; i < max_snake_length; i++) {
      snake_position[i] = 0;
    }
    snake_direction = direction::West;
  
    // main game loop
    for (;;) {
      // Move the snake:
      
      // Copy the 'head' of the snake towards the tail, overwriting the old tail position
      for (i = snake_length - 1; i >= 1; i--) {
        snake_position[i] = snake_position[i - 1];
      }
    
      // Fill in a new head position
      snake_position[0] = getNextPosition(snake_position[1], snake_direction);
      // check if this position collides with any other part of the snake
      if (led_shield.get(snake_position[0])) {
        // fail
        animate_explosion(snake_position[0] % 8, snake_position[0] / 8, 0.03);
        delay(100);
        led_shield.allOff();
        led_shield.write();
        break;
      }
      
      // Draw the snake onto the LEDs (first erase all LEDs)
      led_shield.allOff();
      for (i = 0; i < snake_length; i++) {
        led_shield.on( snake_position[i] );
      }
    
      // Commit these values to the LEDs
      led_shield.write();
    
      // Wait the specified time, meanwhile, detect if the user is tilting the joystick
      new_direction = snake_direction;
      last_millis = millis();
      while (millis() - last_millis < delay_time) {
        
        // Is the left joystick pressed?
        if (led_shield.left_joystick_pressed()) {
          // quit
          return;
        }
  
        // decide on the direction of the snake using the left joystick
        int left_x = led_shield.left_joystick_x();
        int left_y = led_shield.left_joystick_y();
    
        // Cannot turn 180 degrees in a single step (so include rules about which directions are allowed)
    
        // Turning North:
        if (left_y < 200 && snake_direction != direction::South) {
          new_direction = direction::North;
        }
    
        // Turning West:
        else if (left_x < 200 && snake_direction != direction::East) {
          new_direction = direction::West;
        }
    
        // Turning South:
        else if (left_y > 800 && snake_direction != direction::North) {
          new_direction = direction::South;
        }
    
        // Turning East:
        else if (left_x > 800 && snake_direction != direction::West) {
          new_direction = direction::East;
        }
      }
  
      // Set the new direction 
      snake_direction = new_direction;
    }
  }

}

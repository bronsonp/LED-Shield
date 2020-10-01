#include "games.h"
#include "LED_Shield.h"
#include "Arduino.h"

extern LED_Shield led_shield;

// Play the game 
void pongGame() 
{ 
  for (;;) {
    // Position of the ball 
    int ball_x = 2;
    int ball_y = 1; 
    
    // Velocity of the ball
    int ball_vx = 1;
    int ball_vy = 1;
    
    // Width of the paddles
    int paddle_width = 3;
    
    // The time in milliseconds between movements of the ball
    // Adjust this to make the game faster or slower 
    unsigned int delay_time = 200;
  
    // Other variables
    int i;
    int number_of_bounces = 0;
    unsigned long last_millis;
    
    for (;;) {
  
      // how many paddle positions are there?
      int num_positions = 5 - paddle_width;

      // erase the board
      led_shield.allOff();
      // draw the ball
      led_shield.on( ball_x + 8*ball_y );
  
      // Wait the specified time, meanwhile, move the paddles
      last_millis = millis();
      while (millis() - last_millis < delay_time) {
        
        // Is the left joystick pressed?
        if (led_shield.left_joystick_pressed()) {
          // quit
          return;
        }
  
        // Is the right joystick pressed?
        if (led_shield.right_joystick_pressed()) {
          // change paddle width
          paddle_width = 1 + mod(paddle_width - 2, 4);
          // wait for joystick to be released 
          while (led_shield.right_joystick_pressed()) {
            /* wait */
          }
          number_of_bounces = 0;
        }
  
        // detect paddle position based on y axis of joystick
        int left_y = led_shield.left_joystick_y();
        int right_y = led_shield.right_joystick_y();
  
        // carve up the ADC range into how many positions there are and detect which position each paddle is in
        int left_paddle_position = round( (float)left_y / 1023.0 * (num_positions - 1) );
        int right_paddle_position = round( (float)right_y / 1023.0 * (num_positions - 1) );
  
        // draw LHS paddle
        for (i = 0; i < left_paddle_position; i++) {
          led_shield.off(i * 8 + 7);
        }
        for (i = left_paddle_position; i < (left_paddle_position + paddle_width); i++) {
          led_shield.on(i * 8 + 7);
        }
        for (i = (left_paddle_position + paddle_width); i < 4; i++) {
          led_shield.off(i * 8 + 7);
        }
  
        // draw RHS paddle
        for (i = 0; i < right_paddle_position; i++) {
          led_shield.off(i * 8);
        }
        for (i = right_paddle_position; i < (right_paddle_position + paddle_width); i++) {
          led_shield.on(i * 8);
        }
        for (i = (right_paddle_position + paddle_width); i < 4; i++) {
          led_shield.off(i * 8);
        }
  
        // update LEDs
        led_shield.write();
      }

      // move the ball
      ball_x += ball_vx;
      ball_y += ball_vy;
  
      // bounce off the walls
      if (ball_y == 0 || ball_y == 3) {
        ball_vy = -ball_vy;
      }

      // bounce off the paddles 
      if (ball_x == 1 || ball_x == 6) {
        int paddle_location = (ball_x + ball_vx) + 8*ball_y;
        bool hits_paddle = led_shield.get(paddle_location);
  
        if (hits_paddle) {
          // swap x velocity
          ball_vx = -ball_vx;
          
          // sometimes reset y velocity 
          i = random(ball_vy == 0 ? 5 : 9);
          if (i == 0 && ball_y > 0) {
            ball_vy = -1;
          } else if (i == 1) {
            ball_vy = 0;
          } else if (i == 2 && ball_y < 3) {
            ball_vy = 1;
          }
    
          // count how many bounces 
          number_of_bounces++;
          // decrease the size of the paddle
          if ((paddle_width == 4 && number_of_bounces >= 4) 
             ||(number_of_bounces >= 10)) {  
            paddle_width = 1 + mod(paddle_width - 2, 4);
            number_of_bounces = 0;
          }
        } else {
          // missed!
          // erase all
          led_shield.allOff();
          
          // show an explosion 
          animate_explosion(ball_x, ball_y, 0.05);
          break;
        }
      }
    }
  }
}

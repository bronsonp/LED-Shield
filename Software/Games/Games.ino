#include "LED_Shield.h"
#include "games.h"


LED_Shield led_shield;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  led_shield.begin();
}

void loop() {
  // Run the games in sequence. Games return when they are finished.

  // Play the pong game
  pongGame();
  
  // Turn off all LEDs and wait for the joystick to be released
  led_shield.allOff();
  led_shield.write();
  wait_for_left_joystick_release();
    
  // Play the snake game
  snakeGame();

  // Turn off all LEDs and wait for the joystick to be released
  led_shield.allOff();
  led_shield.write();
  wait_for_left_joystick_release();
}

void wait_for_left_joystick_release() {
  while (led_shield.left_joystick_pressed()) {
    /* wait */
  }
}

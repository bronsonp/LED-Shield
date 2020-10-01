#include "games.h"
#include "LED_Shield.h"
#include "Arduino.h"

extern LED_Shield led_shield;

// Compute the modulo operation supporting negative numbers, for example mod(-1,8)=7
int mod(int x, int N) 
{
  return (x + N) % N;
}

// Explosion animation from the given origin
void animate_explosion(int x, int y, float velocity) 
{
  int i, j;
  int target_id = x + 8*y;
  // Blink the given light
  for (i = 400; i > 50; i /= 2) {
    led_shield.on(target_id);
    led_shield.write();
    delay(i);
    
    led_shield.off(target_id);
    led_shield.write();
    delay(i/2);
  }

  // Spread outwards from this point
  unsigned long start_time = millis();
  unsigned long time = 0;
  while (time < 1000) {
    // loop over all LEDs
    for (j = 0; j < 4; j++) {
      for (i = 0; i < 8; i++) {
        // calculate distance from this LED to the explosion origin
        float distance = sqrt((j-y)*(j-y) + (i-x)*(i-x));
  
        // turn on if the explosion has reached this point
        float shockwave_arrival_time = distance / velocity;
        if (time >= shockwave_arrival_time) {
          led_shield.on(i + 8*j);
        }
      }
    }

    // update time 
    time = millis() - start_time;

    // commit values to the LEDs
    led_shield.write();
  }
}

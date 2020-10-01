#include "LED_Shield.h"
LED_Shield led_shield;

void setup() {
  // put your setup code here, to run once:
  led_shield.begin();
}

void loop() {
  // Turn on all lights then wait half a second
  led_shield.allOn(); // all lights will go on the next time we call led_shield.write() 
  led_shield.write(); // update the actual lights
  delay(500); // 500 ms = half a second

  // Light up each row one at a time
  
  // Top row
  led_shield.allOff(); // start with all lights off
  // turn on LEDs 0 through 7
  led_shield.on(0);
  led_shield.on(1);
  led_shield.on(2);
  led_shield.on(3);
  led_shield.on(4);
  led_shield.on(5);
  led_shield.on(6);
  led_shield.on(7);
  // update the lights with these new settings
  led_shield.write();
  // wait 
  delay(300);

  // Second row
  led_shield.allOff(); // start with all lights off
  // turn on LEDs 8 through 15
  led_shield.on(8);
  led_shield.on(9);
  led_shield.on(10);
  led_shield.on(11);
  led_shield.on(12);
  led_shield.on(13);
  led_shield.on(14);
  led_shield.on(15);
  // update the lights with these new settings
  led_shield.write();
  // wait 
  delay(300);
}

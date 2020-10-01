/**
 * Driver code for the JCU LED Shield soldering challenge
 * 
 * Bronson Philippa, September 2020
 * Driver version 1.0
**/

class LED_Shield {
public:
  // Constructor
  LED_Shield();

  // Initialise hardware
  void begin();

  // Turn on a particular LED. 
  // Returns true/false depending upon whether it was previously on/off, respectively.
  // You must call write() after this function to commit the values to the controllers.
  bool on(int id);

  // Turn off a particular LED. 
  // Returns true/false depending upon whether it was previously on/off, respectively.
  // You must call write() after this function to commit the values to the controllers.
  bool off(int id);

  // Toggle the given LED
  // Return true/false depending upon whether it is now on/off, respectively.
  // You must call write() after this function to commit the values to the controllers.
  bool toggle(int id);
  
  // Get whether a given LED is on or off
  bool get(int id);

  // Turn all lights on.
  // You must call write() after this function to commit the values to the controllers.
  void allOn();
  
  // Turn all lights off.
  // You must call write() after this function to commit the values to the controllers.
  void allOff();

  // Read switch SW1 (returns true when switch is pressed)
  bool read_SW1();

  // Read switch SW2 (returns true when switch is pressed)
  bool read_SW2();

  // Read switch SW3 (returns true when switch is pressed)
  bool read_SW3();

  // Read switch SW4 (returns true when switch is pressed)
  bool read_SW4();

  // Read left joystick press (return true when pressed down)
  bool left_joystick_pressed();

  // Read right joystick press (return true when pressed down)
  bool right_joystick_pressed();

  // Read left joystick X axis
  int left_joystick_x();

  // Read left joystick Y axis
  int left_joystick_y();

  // Read right joystick X axis 
  int right_joystick_x();

  // Read right joystick Y axis 
  int right_joystick_y();

  // Direct access to data (if you modify this, you must call write() to commit the changes).
  bool D[32];

  // Write the LED status to the controllers so that they change to the new values
  void write();
};

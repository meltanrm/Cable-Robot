//**********************************************************************************
// This code can be used to test the abilities of the 3-axis joystick to move a motor.

// Moving the joystick in the positive x direction moves the motor clockwise.
// Joystick reading thresholds have been used to make the motor:
// - Turn slowly if the joystick is only partly pushed.
// - Turn quickly if the joystick is fully engaged.
// Similar code also implements this for negative x joystick movements moving the motor counterclockwise.
// Feel free to modify the code to check z and y joystick motions as well.

// Before running this code, it is suggested to run the Joystick_graphs code first.
// Check the joystick readings: 
// - Make sure incremental movements of the joystick are distinguishable.
// - Make note of where you could set a threshold past which motor motion chages from slow to fast.
// Modify the code below with the thresholds that are appropriate for your joystick.

// Make sure to check that the step, dir and joystick pins are in agreement with your circuit.
//**********************************************************************************

// Define pin connections & motor's steps per revolution
const int dirPin = 6;
const int stepPin = 7;
const int stepsPerRevolution = 200;

void setup() {
  // Declare pins as outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}
void loop() {
  // Read joystick inputs from analog pins
  int x = analogRead(A0);
//  int y = analogRead(A1);
//  int z = analogRead(A2);

  if (x < 350) {
    // Set motor direction clockwise
    digitalWrite(dirPin, HIGH); 
    // Spin motor slowly
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(3000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(3000);
  }

  else if (x < 150) {
    // Set motor direction clockwise
    digitalWrite(dirPin, HIGH); 
    // Spin motor quickly
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }

  else if (x > 550) {
    // Set motor direction counterclockwise
    digitalWrite(dirPin, LOW);
    // Spin motor slowly
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(3000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(3000);
  }
  
  else if (x > 750) {
    // Set motor direction counterclockwise
    digitalWrite(dirPin, LOW);
    // Spin motor quickly
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }

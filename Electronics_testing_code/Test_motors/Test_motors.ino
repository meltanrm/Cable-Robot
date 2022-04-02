//**********************************************************************************
// This code can be used to test the motors.
 
// If the electronic circuit is correctly set up, the motors should repeatedly move:
// - One full rotation clockwise (slowly).
// - One full rotation counterclockwise (quickly).

// Make sure to check that the step and dir pins are in agreement with your circuit.
//**********************************************************************************

// Define pin connections & motor's steps per revolution
const int dirPin1 = 6;
const int stepPin1 = 7;
const int dirPin2 = 8;
const int stepPin2 = 9;
const int dirPin3 = 10;
const int stepPin3 = 11;
const int dirPin4 = 12;
const int stepPin4 = 13;
const int stepsPerRevolution = 200;

void setup()
{
  // Declare pins as outputs
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  pinMode(stepPin4, OUTPUT);
  pinMode(dirPin4, OUTPUT);
}
void loop()
{
  // Set motor direction clockwise
  digitalWrite(dirPin1, HIGH);
  digitalWrite(dirPin2, HIGH);
  digitalWrite(dirPin3, HIGH);
  digitalWrite(dirPin4, HIGH);

  // Spin motor slowly
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin1, HIGH);
    digitalWrite(stepPin2, HIGH);
    digitalWrite(stepPin3, HIGH);
    digitalWrite(stepPin4, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin1, LOW);
    digitalWrite(stepPin2, LOW);
    digitalWrite(stepPin3, LOW);
    digitalWrite(stepPin4, LOW);
    delayMicroseconds(2000);
  }
  delay(1000); // Wait a second
  
  // Set motor direction counterclockwise
  digitalWrite(dirPin1, LOW);
  digitalWrite(dirPin2, LOW);
  digitalWrite(dirPin3, LOW);
  digitalWrite(dirPin4, LOW);

  // Spin motor quickly
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin1, HIGH);
    digitalWrite(stepPin2, HIGH);
    digitalWrite(stepPin3, HIGH);
    digitalWrite(stepPin4, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin1, LOW);
    digitalWrite(stepPin2, LOW);
    digitalWrite(stepPin3, LOW);
    digitalWrite(stepPin4, LOW);
    delayMicroseconds(1000);
  }
  delay(1000); // Wait a second
}

#include <AccelStepper.h>

const int dirPin = 6;
const int stepPin = 7;
const int stepsPerRevolution = 200;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}
void loop() {
  int x = analogRead(A0);
  int y = analogRead(A1);
  int z = analogRead(A2);

  if (x < 350) { // DO NOT USE WHILE STATEMENT
    // Set motor direction clockwise
    digitalWrite(dirPin, HIGH); 
    // Spin motor slowly
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }

  else if (x < 400) { // DO NOT USE WHILE STATEMENT
    // Set motor direction clockwise
    digitalWrite(dirPin, HIGH); 
    // Spin motor slowly
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(3000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(3000);
  }

  else if (x > 880) {
    // Set motor direction counterclockwise
    digitalWrite(dirPin, LOW);
    // Spin motor slowly
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(3000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(3000);
  }
  
  else if (x > 890) {
    // Set motor direction counterclockwise
    digitalWrite(dirPin, LOW);
    // Spin motor slowly
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }

//  if (y < 300) {
//  //Send an ASCII 'i',
//  Keyboard.write(105);
//  }
//  
//  if (y >900) {
//  //Send an ASCII 'k',
//  Keyboard.write(107);
//  }
//  
//  if (z < 300) {
//  //Send an ASCII 'q',
//  Keyboard.write(113);
//  }
//  
//  if (z >900) {
//  //Send an ASCII 'e',
//  Keyboard.write(101);
//  }
}

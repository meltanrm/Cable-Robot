//**********************************************************************************
// This code can be used to test the connection between a encoder and motor.

// Before running this code, it is suggested to run the Test_encoder code first to test the ability of the encoder 
// to track rotation by manually turning the shaft, without a motor or connections involved.

// Go to Tools -> Serial Monitor and run the code.
// This code should move the motor by a full rotation clockwise, followed by a full rotation counterclockwise.
// If your encoder and motor are correctly connected, the start position displayed on the serial monitor should be identical to the end position, 
// i.e. 0 (unless steps were skipped by the motor). 
// The position displayed when the motor switches from turning clockwise to turning counterclockwise should be 200, 
// since that is the number of steps taken by the motor to acheive 1 full rotation. 


// Make sure to check that the step, dir and encoder pins are in agreement with your circuit.
// Also check that the attachInterrupt numbers correspond the correct pins where the encoder is connected. 
// Correspondance between attachInterrupt numbers and pins can be found at the bottom of the following page:
// https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/ (Accessed 2 April 2022)
//**********************************************************************************

volatile long temp, counter = 0; // This variable will increase or decrease depending on the rotation of encoder

// Define pin connections & motor's steps per revolution
const int dirPin1 = 6; 
const int stepPin1 = 7;
const int stepsPerRevolution = 200;
int startPos;
int oneRotationPos;
int endPos;

void setup(){
  Serial.begin (9600);

  // Declare pins as outputs
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  
  // Define encoder pins 
  pinMode(20, INPUT_PULLUP); 
  pinMode(21, INPUT_PULLUP); 
  
  //Setting up interrupt
  //A rising pulse from the encoder's A output will activate ai0(). AttachInterrupt 0 is digital pin 20 on the Arduino MEGA.
  attachInterrupt(3, ai0, RISING);  
  //A rising pulse from the encoder's B output will activate ai1(). AttachInterrupt 1 is digital pin 21 on the Arduino MEGA.
  attachInterrupt(2, ai1, RISING);
}
void loop(){
  startPos = counter;
  Serial.println("Start Position: ");
  Serial.println(startPos); 

  // Set motor direction clockwise
  digitalWrite(dirPin1, HIGH);
  // Spin motor slowly
  for(int x = 0; x < stepsPerRevolution; x++){
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(2000);
  }
  delay(1000); // Wait a second

  oneRotationPos = counter;
  Serial.println("Position after 1 rotation: ");
  Serial.println(oneRotationPos);
  
  // Set motor direction counterclockwise
  digitalWrite(dirPin1, LOW);
  // Spin motor quickly
  for(int x = 0; x < stepsPerRevolution; x++){
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(1000);
  }
  delay(1000); // Wait a second

  endPos = counter;
  Serial.println("End Position: ");
  Serial.println(endPos);
}

// ai0() is activated if digital pin 20 goes from LOW to HIGH
void ai0(){
  // Check pin 21 to determine the direction
  if(digitalRead(21)==LOW){
    counter++;
  }
  else{
    counter--;
  }
}

// ai1() is activated if digital pin 21 goes from LOW to HIGH
void ai1(){
  // Check with pin 20 to determine the direction
  if(digitalRead(20)==LOW){
    counter--;
  }
  else{
    counter++;
  }
}

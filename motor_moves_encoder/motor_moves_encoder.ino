volatile long temp, counter = 0; //This variable will increase or decrease depending on the rotation of encoder
const int dirPin1 = 6; // motor 1 
const int stepPin1 = 7;
const int stepsPerRevolution = 200;
    
void setup() {
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  
  Serial.begin (9600);

  pinMode(20, INPUT_PULLUP); // internal pullup input pin 2 
  pinMode(21, INPUT_PULLUP); // internal pullup input pin 3
   //Setting up interrupt
  //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  attachInterrupt(3, ai0, RISING);
   
  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  attachInterrupt(2, ai1, RISING);
}
   
void loop() {
  
  
  // Send the value of counter
  if( counter != temp ){
    Serial.println (counter);
    temp = counter;
  }
  
  digitalWrite(dirPin1, HIGH);
  
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(2000);
  }
  delay(1000); // Wait a second
  
  digitalWrite(dirPin1, LOW);
  
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(1000);
  }
  delay(1000); // Wait a second
}
   
void ai0() {
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if(digitalRead(21)==LOW) {
    counter++;
  }else{
    counter--;
  }
}
   
void ai1() {
  // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if(digitalRead(20)==LOW) {
    counter--;
  }else{
    counter++;
  } 
}

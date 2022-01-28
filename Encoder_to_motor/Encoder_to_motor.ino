volatile long temp, counter = 0; //This variable will increase or decrease depending on the rotation of encoder
const int stepPin1 = 7;
const int dirPin1 = 6;
const int stepPin1 = 11;
const int dirPin1 = 10;

#define CLK 2
#define DT 3
//ensure you change the attachInterrupt pins as well 
 
void setup() {
  Serial.begin (9600);
  
  // declaring pins as encoder outputs 
  pinMode(CLK, INPUT_PULLUP); // internal pullup input pin 2 
  pinMode(DT, INPUT_PULLUP); // internalเป็น pullup input pin 3

  // declaring pins as motor outputs 
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  
   //Setting up interrupt
  //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  attachInterrupt(0, ai0, RISING);
   
  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  attachInterrupt(1, ai1, RISING);
  }
   
  void loop() {
  // Send the value of counter
    if( counter != temp ){
      Serial.println (counter);
      temp = counter;
    }
  }
   
  void ai0() {
    // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
    // Check pin 3 to determine the direction
    if(digitalRead(3)==LOW) {
    // ai0 is activated if DigitalPin nr 18 is going from LOW to HIGH
    // Check pin 19 to determine the direction
    if(digitalRead(DT)==LOW) {
      counter++;
      digitalWrite(dirPin1, HIGH);
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(1000);      
    }else{
      counter--;
      digitalWrite(dirPin1, LOW);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(1000);
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(1000);
    }
  }
   
  void ai1() {
    // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
    // Check with pin 2 to determine the direction
    if(digitalRead(2)==LOW) {
    // ai0 is activated if DigitalPin nr 19 is going from LOW to HIGH
    // Check with pin 18 to determine the direction
    if(digitalRead(CLK)==LOW) {
      counter--;
    }else{
      counter++;
    }
  }

volatile long temp, counter = 0; //This variable will increase or decrease depending on the rotation of encoder
    
void setup() {
  Serial.begin (9600);

  pinMode(20, INPUT_PULLUP); // internal pullup input pin 20 
  
  pinMode(21, INPUT_PULLUP); // internal pullup input pin 21
   //Setting up interrupt
  //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 20 on moust Arduino.
  attachInterrupt(3, ai0, RISING);
   
  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 21 on moust Arduino.
  attachInterrupt(2, ai1, RISING);
}
   
void loop() {
// Send the value of counter
  if( counter != temp ){
    Serial.println (counter);
    temp = counter;
  }
}
 
void ai0() {
  // ai0 is activated if DigitalPin nr 20 is going from LOW to HIGH
  // Check pin 21 to determine the direction
  if(digitalRead(21)==LOW) {
    counter++;
  }else{
    counter--;
  }
}
   
void ai1() {
  // ai0 is activated if DigitalPin nr 21 is going from LOW to HIGH
  // Check with pin 20 to determine the direction
  if(digitalRead(20)==LOW) {
  counter--;
  }else{
  counter++;
  }
}

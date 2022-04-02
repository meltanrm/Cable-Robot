
//**********************************************************************************
// This code can be used to test the ability of the encoder to track rotation.

// Go to Tools -> Serial Monitor and run the code.
// Turn the encoder shaft to see how the counter displayed on the serial monitor evolves.
// One full rotation should make the counter number change by 200.

// Make sure to check that the encoder pins are in agreement with your circuit.
// Also check that the attachInterrupt numbers correspond the correct pins where the encoder is connected. 
// Correspondance between attachInterrupt numbers and pins can be found at the bottom of the following page:
// https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/ (Accessed 2 April 2022)
//**********************************************************************************

volatile long temp, counter = 0; // This variable will increase or decrease depending on the rotation of encoder
    
void setup(){
  Serial.begin (9600);

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
  // Print the value of the counter
  if( counter != temp ){
    Serial.println (counter);
    temp = counter;
  }
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

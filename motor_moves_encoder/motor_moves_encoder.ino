volatile long temp, counter = 0; //This variable will increase or decrease depending on the rotation of encoder
// Define pin connections & motor's steps per revolution
const int dirPin1 = 6; // motor 1 
const int stepPin1 = 7;
const int stepsPerRevolution = 200;
int startPos;
int endPos;

void setup()
{
  Serial.begin (9600);

  // Encoder 
  pinMode(20, INPUT_PULLUP); // internal pullup input pin 20 
  pinMode(21, INPUT_PULLUP); // internal pullup input pin 21

  // Setting up interrupt
  attachInterrupt(3, ai0, RISING); 
  attachInterrupt(2, ai1, RISING);

  // Declare pins as Outputs
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
}
void loop()
{
  // Send the value of counter
//  if( counter != temp ){
//    Serial.println (counter);
//    temp = counter;
//  }

  startPos = counter;
  Serial.println("Start Pos");
  Serial.println(startPos); 

  // Set motor direction clockwise
  digitalWrite(dirPin1, HIGH);

  // Spin motor slowly
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(2000);
  }
  delay(1000); // Wait a second
  
  // Set motor direction counterclockwise
  digitalWrite(dirPin1, LOW);
  
  // Spin motor quickly
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(1000);
  }
  delay(1000); // Wait a second

  endPos = counter;
  Serial.println("End Pos");
  Serial.println(endPos);
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

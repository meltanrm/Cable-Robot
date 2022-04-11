//**********************************************************************************
// This code can be used to check the functionality of the 3-axis joystick.
// It was adapted from https://www.crazy-logic.co.uk/archives/1053 (Accessed 1 April 2022)

// Tools -> Serial Plotter and run the code.
// 3 lines giving joystick readings for the x, y and z axis respectively, should appear. 
// In our circuit, we chose not to connect the joystick button pin, as we do not need it.
// Feel free to modify the code though and get an extra line for the joystick button readings.

// Make sure to check that joystick pins are in agreement with your circuit. 
//**********************************************************************************

void setup() {
  // initialize serial communication at 9600 bits per second:
  pinMode(A3, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // Read joystick inputs from analog pins
  int x = analogRead(A0);
  int y = analogRead(A1);
  int z = analogRead(A2);
//  int btn = analogRead(A3);  

  String st = String(x) + " " + String(y) + " " + String(z); // + " " + String(btn);
  Serial.println(st);
  delay(10);
}

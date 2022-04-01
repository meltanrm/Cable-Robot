//The following code was adapted from https://www.crazy-logic.co.uk/archives/1053 (Accessed 1 April 2022)

void setup() {
  // initialize serial communication at 9600 bits per second:
  pinMode(A3, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // read the inputs on analog pins
  int x = analogRead(A0);
  int y = analogRead(A1);
  int z = analogRead(A2);
  int btn = analogRead(A3);  

  String st = String(x) + " " + String(y) + " " + String(z) + " " + String(btn);
  Serial.println(st);
  delay(10);
}

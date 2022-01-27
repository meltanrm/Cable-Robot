void setup() {
// initialize serial communication at 9600 bits per second:
pinMode(A3, INPUT_PULLUP);
Serial.begin(9600);
}
// the loop routine runs over and over again forever:
void loop() {
// read the input on analog pin 0:
int p = analogRead(A0);
int t = analogRead(A1);
int r = analogRead(A2);
int b = analogRead(A3);

String st = String(p) + " " + String(t) + " " + String(r) + " " + String(b);
Serial.println(st);
delay (10);
}

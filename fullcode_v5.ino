const int dirPinB = 6; // motor B
const int stepPinB = 7;
const int dirPinD = 8; // motor D spool
const int stepPinD = 9;
const int dirPinA = 10; // motor A
const int stepPinA = 11;
const int dirPinC = 12; // motor C
const int stepPinC = 13;
const int stepsPerRevolution = 200;

void setup() {
  Serial.begin(9600);

  // Declare motor control pins as Outputs
  pinMode(stepPinB, OUTPUT);
  pinMode(dirPinB, OUTPUT);
  pinMode(stepPinD, OUTPUT);
  pinMode(dirPinD, OUTPUT);
  pinMode(stepPinA, OUTPUT);
  pinMode(dirPinA, OUTPUT);
  pinMode(stepPinC, OUTPUT);
  pinMode(dirPinC, OUTPUT);

}

void recvInputCoord() {
  float x_coord;
  float y_coord;
  float z_coord;
  float Cp[3] = {0, 0, 0};
  Serial.begin(9600);

  Serial.println("Please input X coordinate: ");
  while (Serial.available() == 0) {
  }
  x_coord = Serial.parseInt();
//  delayMicroseconds(100000);
  Serial.println(x_coord);


  Serial.println("Please input Y coordinate: "); //Prompt User for Input
  while (Serial.available() == 0) {
  }
  y_coord = Serial.parseInt();
//  delayMicroseconds(100000);
  Serial.println(y_coord);

  Serial.println("Please input Z coordinate: "); //Prompt User for Input
  while (Serial.available() == 0) {
  }
  z_coord = Serial.parseInt();
//  delayMicroseconds(100000);
  Serial.println(z_coord);

  Serial.println("55");
  // From cm to metres
  Cp[0] = x_coord/100;
  Cp[1] = y_coord/100;
  Cp[2] = z_coord/100;

  Serial.println("61");

  Serial.println("Your input coordinates are: ");
  Serial.println(x_coord);
  Serial.println(y_coord);
  Serial.println(z_coord);
}

// Function calculates line length
float lineLength(float coord1[3], float coord2[3]) {
  float diff[3];
  float modResult;
  for (int i = 0; i < 3; i++) {
    diff[i] = (coord2[i] - coord1[i]);
  }
//  modResult = (sqrt(sq(diff[1]) + sq(diff[2]) + sq(diff[3]))) / 100;
  modResult = (sqrt(sq(diff[0]) + sq(diff[1]) + sq(diff[2]))) / 100;
  return modResult;
}

void loop() {
  float lineLength(float coord1[], float coord2[]);

  float Cp[3] = {0, 0, 0};// declare array to store input coordinates


  float height_upper = 1.397; // height (in metres) from top board to level with frame (0.038m above the ground)
  float height_lower = 0; // height

  // SHOULD ALL THESE BE 100 INSTEAD OF 1000?

  // coord of line rollers and vertices(for D)
  float D_1[] = { -70.785 / 1000, -40.865 / 1000, height_upper};
  float D_1atplat[] = { -70.785 / 1000, -40.865 / 1000, height_lower};
  float D_2[] = {0, 80.736 / 1000, height_upper};
  float D_2atplat[] = {0, 80.736 / 1000, height_lower};
  float D_3[] = {70.785 / 1000, 40.865 / 1000, height_upper};
  float D_3atplat[] = {70.785 / 1000, 40.865 / 1000, height_lower};

  // coord of line anchors
  float a1_1[] = { -70.785 / 1000, -530 / 1000, height_lower};
  float a1_2[] = {70.785 / 1000, -530 / 1000, height_lower};
  float a2_1[] = { -530 / 1000, 224.26 / 1000, height_lower};
  float a2_2[] = { -530 / 1000, 387.731 / 1000, height_lower};
  float a3_1[] = {530 / 1000, 387.731 / 1000, height_lower};
  float a3_2[] = {530 / 1000, 224.26 / 1000, height_lower};

  // line lengths at origin
  // only distance that is necessry is the line anchor to the platform vertex (we only care aboutchanges in lengths)
  float l_a1_0 = lineLength(a2_1, D_1atplat);
  float l_a2_0 = lineLength(a2_2, D_2atplat);
  float l_b1_0 = lineLength(a1_1, D_3atplat);
  float l_b2_0 = lineLength(a1_2, D_1atplat);
  float l_c1_0 = lineLength(a3_1, D_2atplat);
  float l_c2_0 = lineLength(a3_2, D_3atplat);

  float l_d1_0 = lineLength(D_1atplat, D_1); // from line D rollers to platform vertices
  float l_d2_0 = lineLength(D_2atplat, D_2);
  float l_d3_0 = lineLength(D_3atplat, D_3);


  recvInputCoord(); // receives input coordinates in cm, converted to metres in function

  // coordinates of triangle platform vertices wrt center of platform, Cp
  float V_1[] = {D_1[0] + Cp[0], D_1[1] + Cp[1], 0 + Cp[2]}; // lined up with D_1
  float V_2[] = {D_2[0] + Cp[0], D_2[1] + Cp[1], 0 + Cp[2]}; // lined up with D_2
  float V_3[] = {D_3[0] + Cp[0], D_3[1] + Cp[1], 0 + Cp[2]}; // lined up with D_3

  // calculation of cable lengths
  // total change in lengths from one point to another = (spool to roller) + (roller to anchor) + (anchor to platform vertex)
  float l_a1 = lineLength(a2_1, V_1);
  float l_a2 = lineLength(a2_2, V_2);
  float l_b1 = lineLength(a1_1, V_3);
  float l_b2 = lineLength(a1_2, V_1);
  float l_c1 = lineLength(a3_1, V_2);
  float l_c2 = lineLength(a3_2, V_3);

  float l_d1 = lineLength(V_1, D_1);
  float l_d2 = lineLength(V_2, D_2);
  float l_d3 = lineLength(V_3, D_3);

  // calculate difference between desired lengths and current lengths
  float lineDiffa1 = l_a1 - l_a1_0; // repeatd for all other lines
  float lineDiffa2 = l_a2 - l_a2_0;
  float lineDiffb1 = l_b1 - l_b1_0;
  float lineDiffb2 = l_b2 - l_b2_0;
  float lineDiffc1 = l_c1 - l_c1_0;
  float lineDiffc2 = l_c2 - l_c2_0;
  float lineDiffd1 = l_d1 - l_d1_0; // LINE DIFF FOR D
  float lineDiffd2 = l_d2 - l_d2_0;
  float lineDiffd3 = l_d3 - l_d3_0;

  // find the corresponding rotations required
  float spoolDiameter = 0.11; // meters
  float spoolCirc = PI * spoolDiameter;


  // for each of the below, a1 and a2 should be equal, same for b1 and b2, and c1 and c2
  int motorSteps_a1 = (abs(lineDiffa1) / (spoolCirc)) * 8.45 * 200; // 8.45 turns of motor is one turn of spool; motor has 200 steps per turn
  int motorSteps_b1 = (abs(lineDiffb1) / (spoolCirc)) * 8.45 * 200;
  int motorSteps_c1 = (abs(lineDiffc1) / (spoolCirc)) * 8.45 * 200;
  int motorSteps_d1 = (abs(lineDiffd1) / (spoolCirc)) * 8.45 * 200;


  Serial.println(motorSteps_a1);
  Serial.println(motorSteps_b1);
  Serial.println(motorSteps_c1);
  Serial.println(motorSteps_d1);

  // Motor A
  if (lineDiffa1 > 0) {
    digitalWrite(dirPinA, HIGH); // set direction to clockwise
//    for (int x = 0; x < 1000; x++)
    for (int x = 0; x < motorSteps_a1; x++)
    {
      digitalWrite(stepPinA, HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPinA, LOW);
      delayMicroseconds(2000);
    }
  }
  else {
    digitalWrite(dirPinA, LOW);
//    for (int x = 0; x < 1000; x++)
    for (int x = 0; x < motorSteps_a1; x++)
    {
      digitalWrite(stepPinA, HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPinA, LOW);
      delayMicroseconds(2000);
    }
  }


  // Motor B

  if (lineDiffb1 > 0) {
    digitalWrite(dirPinB, HIGH); // set direction to clockwise
//    for (int x = 0; x < 500; x++)
    for (int x = 0; x < motorSteps_b1; x++)
    {
      digitalWrite(stepPinB, HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPinB, LOW);
      delayMicroseconds(2000);
    }
  }
  else {
    digitalWrite(dirPinB, LOW);
//    for (int x = 0; x < 500; x++)
    for (int x = 0; x < motorSteps_b1; x++)
    {
      digitalWrite(stepPinB, HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPinB, LOW);
      delayMicroseconds(2000);
    }
  }

  // Motor C

  if (lineDiffc1 > 0) {
    digitalWrite(dirPinC, HIGH); // set direction to clockwise
//    for (int x = 0; x < 500; x++)
    for (int x = 0; x < motorSteps_c1; x++)
    {
      digitalWrite(stepPinC, HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPinC, LOW);
      delayMicroseconds(2000);
    }
  }
  else {
    digitalWrite(dirPinC, LOW);
//    for (int x = 0; x < 500; x++)
    for (int x = 0; x < motorSteps_c1; x++)
    {
      digitalWrite(stepPinC, HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPinC, LOW);
      delayMicroseconds(2000);
    }
  }

  // Motor D

  if (lineDiffd1 > 0) {
    digitalWrite(dirPinD, HIGH); // set direction to clockwise
//    for (int x = 0; x < 500; x++)
    for (int x = 0; x < motorSteps_d1; x++)
    {
      digitalWrite(stepPinD, HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPinD, LOW);
      delayMicroseconds(2000);
    }
  }
  else {
    digitalWrite(dirPinD, LOW);
//    for (int x = 0; x < 500; x++)
    for (int x = 0; x < motorSteps_d1; x++)
    {
      digitalWrite(stepPinD, HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPinD, LOW);
      delayMicroseconds(2000);
    }
  }
  // reassign values of lengths

  l_a1_0 = l_a1;
  l_a2_0 = l_a2;
  l_b1_0 = l_b1;
  l_b2_0 = l_b2;
  l_c1_0 = l_c1;
  l_c2_0 = l_c2;
  l_d1_0 = l_d1;
  l_d2_0 = l_d2;
  l_d3_0 = l_d3;

}
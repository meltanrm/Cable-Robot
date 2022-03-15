const int dirPinB = 6; // motor B
const int stepPinB = 7;
const int dirPinD = 8; // motor D spool
const int stepPinD = 9;
const int dirPinA = 10; // motor A
const int stepPinA = 11;
const int dirPinC = 12; // motor C
const int stepPinC = 13;
const int stepsPerRevolution = 200;
float Cp[3] = {0, 0, 0};

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
//  float Cp[3] = {0, 0, 0};
  Serial.begin(9600);

  Serial.println("Please input X coordinate: ");
  while (Serial.available() == 0) {
  }
  x_coord = Serial.parseInt();
  Serial.println(x_coord);


  //delay(5000);
  Serial.println("Please input Y coordinate: "); //Prompt User for Input
  while (Serial.available() == 0) {
  }
  y_coord = Serial.parseInt();
  Serial.println(y_coord);

  //delay(5000);
  Serial.println("Please input Z coordinate: "); //Prompt User for Input
  while (Serial.available() == 0) {
  }
  z_coord = Serial.parseInt();
  Serial.println(z_coord);

  // From cm to metres
  Cp[0] = x_coord/100;
  Cp[1] = y_coord/100;
  Cp[2] = z_coord/100;


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

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void loop() {
  float lineLength(float coord1[], float coord2[]);


  float height_upper = 1.397; // height (in metres) from top board to level with frame (0.038m above the ground)
  float height_lower = 0; // height


  // coord of line rollers and vertices(for D)
  float D_1[] = { -70.785 / 100, -40.865 / 100, height_upper};
  float D_1atplat[] = { -70.785 / 100, -40.865 / 100, height_lower};
  float D_2[] = {0, 80.736 / 100, height_upper};
  float D_2atplat[] = {0, 80.736 / 100, height_lower};
  float D_3[] = {70.785 / 100, 40.865 / 100, height_upper};
  float D_3atplat[] = {70.785 / 100, 40.865 / 100, height_lower};

  // coord of line anchors
  float a1_1[] = { -70.785 / 100, -530 / 100, height_lower};
  float a1_2[] = {70.785 / 100, -530 / 100, height_lower};
  float a2_1[] = { -530 / 100, 224.26 / 100, height_lower};
  float a2_2[] = { -530 / 100, 387.731 / 100, height_lower};
  float a3_1[] = {530 / 100, 387.731 / 100, height_lower};
  float a3_2[] = {530 / 100, 224.26 / 100, height_lower};

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
  int motorSteps_a1 = ((lineDiffa1) / (spoolCirc)) * 8.45 * 200; // 8.45 turns of motor is one turn of spool; motor has 200 steps per turn
  int motorSteps_b1 = ((lineDiffb1) / (spoolCirc)) * 8.45 * 200;
  int motorSteps_c1 = ((lineDiffc1) / (spoolCirc)) * 8.45 * 200;
  int motorSteps_d1 = ((lineDiffd1) / (spoolCirc)) * 8.45 * 200;
  
  Serial.println(motorSteps_a1);
  Serial.println(motorSteps_b1);
  Serial.println(motorSteps_c1);
  Serial.println(motorSteps_d1);

  int abs_a = abs(motorSteps_a1);
  int abs_b = abs(motorSteps_b1);
  int abs_c = abs(motorSteps_c1);
  int abs_d = abs(motorSteps_d1);
  int stepsArray[] = {abs_a,abs_b,abs_c,abs_d};
  Serial.println("Unsorted array: ");
  for (int i = 0; i < 4; i++) {
    Serial.println(stepsArray[i]);
  }
  
  qsort(stepsArray,4, sizeof(stepsArray[0]), cmpfunc); // This sorts array in ascending order
  Serial.println("Sorted array: ");
  for (int i = 0; i < 4; i++) {
    Serial.println(stepsArray[i]);
  }

  //  SET CLOCKWISE OR ANTICLOCKWISE
    if (lineDiffa1 >= 0){
      digitalWrite(dirPinA, HIGH);
    }
    else {
      digitalWrite(dirPinA, LOW);
    }
    
    if (lineDiffb1 >= 0){
      digitalWrite(dirPinB, HIGH);
    }
    else {
      digitalWrite(dirPinB, LOW);
    }
    
    if (lineDiffc1 >= 0){
      digitalWrite(dirPinC, HIGH);
    }
    else {
      digitalWrite(dirPinC, LOW);
    }
    
    if (lineDiffd1 >= 0){
      digitalWrite(dirPinD, HIGH);
    }
    else {
      digitalWrite(dirPinD, LOW);
    }

  for(int x = 0; x < stepsArray[0]; x++)
  {
    digitalWrite(stepPinA, HIGH);
    digitalWrite(stepPinB, HIGH);
    digitalWrite(stepPinC, HIGH);
    digitalWrite(stepPinD, HIGH);
    delayMicroseconds(4000);
    digitalWrite(stepPinA, LOW);
    digitalWrite(stepPinB, LOW);
    digitalWrite(stepPinC, LOW);
    digitalWrite(stepPinD, LOW);
  }

  for(int x = 0; x < stepsArray[1]; x++)
  {
    if (stepsArray[1] > abs_a) {
      digitalWrite(stepPinB, HIGH);
      digitalWrite(stepPinC, HIGH);
      digitalWrite(stepPinD, HIGH);
      delayMicroseconds(4000);
      digitalWrite(stepPinB, LOW);
      digitalWrite(stepPinC, LOW);
      digitalWrite(stepPinD, LOW);
    }
    if (stepsArray[1] > abs_b) {
      digitalWrite(stepPinA, HIGH);
      digitalWrite(stepPinC, HIGH);
      digitalWrite(stepPinD, HIGH);
      delayMicroseconds(4000);
      digitalWrite(stepPinA, LOW);
      digitalWrite(stepPinC, LOW);
      digitalWrite(stepPinD, LOW);
    }
    if (stepsArray[1] > abs_c) {
      digitalWrite(stepPinA, HIGH);
      digitalWrite(stepPinB, HIGH);
      digitalWrite(stepPinD, HIGH);
      delayMicroseconds(4000);
      digitalWrite(stepPinA, LOW);
      digitalWrite(stepPinB, LOW);
      digitalWrite(stepPinD, LOW);
    }
    if (stepsArray[1] > abs_d) {
      digitalWrite(stepPinA, HIGH);
      digitalWrite(stepPinB, HIGH);
      digitalWrite(stepPinC, HIGH);
      delayMicroseconds(4000);
      digitalWrite(stepPinA, LOW);
      digitalWrite(stepPinB, LOW);
      digitalWrite(stepPinC, LOW);
    }
    
  }

  for(int x = 0; x < stepsArray[2]; x++)
  {
    if ((stepsArray[2] > abs_a) && (stepsArray[2] > abs_b)) {
      digitalWrite(stepPinC, HIGH);
      digitalWrite(stepPinD, HIGH);
      delayMicroseconds(4000);
      digitalWrite(stepPinC, LOW);
      digitalWrite(stepPinD, LOW);
    }

    if ((stepsArray[2] > abs_a) && (stepsArray[2] > abs_c)) {
      digitalWrite(stepPinB, HIGH);
      digitalWrite(stepPinD, HIGH);
      delayMicroseconds(4000);
      digitalWrite(stepPinB, LOW);
      digitalWrite(stepPinD, LOW);
    }

    if ((stepsArray[2] > abs_a) && (stepsArray[2] > abs_d)) {
      digitalWrite(stepPinB, HIGH);
      digitalWrite(stepPinC, HIGH);
      delayMicroseconds(4000);
      digitalWrite(stepPinB, LOW);
      digitalWrite(stepPinC, LOW);
    }
    if ((stepsArray[2] > abs_b) && (stepsArray[2] > abs_c)) {
      digitalWrite(stepPinA, HIGH);
      digitalWrite(stepPinD, HIGH);
      delayMicroseconds(4000);
      digitalWrite(stepPinA, LOW);
      digitalWrite(stepPinD, LOW);
    }
    if ((stepsArray[2] > abs_b) && (stepsArray[2] > abs_d)) {
      digitalWrite(stepPinA, HIGH);
      digitalWrite(stepPinC, HIGH);
      delayMicroseconds(4000);
      digitalWrite(stepPinA, LOW);
      digitalWrite(stepPinC, LOW);
    }
    if ((stepsArray[2] > abs_c) && (stepsArray[2] > abs_d)) {
      digitalWrite(stepPinA, HIGH);
      digitalWrite(stepPinB, HIGH);
      delayMicroseconds(4000);
      digitalWrite(stepPinA, LOW);
      digitalWrite(stepPinB, LOW);
    }

  }

  for(int x = 0; x < stepsArray[3]; x++)
  {
    if (stepsArray[3] == abs_a) {
      digitalWrite(stepPinA, HIGH);
      delayMicroseconds(4000);
      digitalWrite(stepPinA, LOW);
    }
    if (stepsArray[3] == abs_b) {
      digitalWrite(stepPinB, HIGH);
      delayMicroseconds(4000);
      digitalWrite(stepPinB, LOW);
    }
    if (stepsArray[3] == abs_c) {
      digitalWrite(stepPinC, HIGH);
      delayMicroseconds(4000);
      digitalWrite(stepPinC, LOW);
    }
    if (stepsArray[3] == abs_d) {
      digitalWrite(stepPinD, HIGH);
      delayMicroseconds(4000);
      digitalWrite(stepPinD, LOW);
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



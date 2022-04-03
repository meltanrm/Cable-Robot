// set serial monitor settings (newline--> no line ending)

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
 
  Serial.begin(9600);

  Serial.println("Please input X coordinate: ");
  while (Serial.available() == 0) {
  }
  x_coord = Serial.parseInt();
  Serial.println(x_coord);

  Serial.println("Please input Y coordinate: "); //Prompt User for Input
  while (Serial.available() == 0) {
  }
  y_coord = Serial.parseInt();
  Serial.println(y_coord);

  Serial.println("Please input Z coordinate: "); //Prompt User for Input
  while (Serial.available() == 0) {
  }
  z_coord = Serial.parseInt();
  //Serial.println(z_coord);

// all input coordinates in cm 
  Cp[0] = x_coord;
  Cp[1] = y_coord;
  Cp[2] = z_coord;

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
        diff[i] = (coord2[i] - coord1[i]);  // coordinates in cm
      }
      modResult = (sqrt(sq(diff[0]) + sq(diff[1]) + sq(diff[2]))); // modResut in cm
      return modResult;
    }

void loop() {
  float lineLength(float coord1[], float coord2[]);

  float height_upper = 1.397*100; // height (in cm) from top board to level with frame (0.038m above the ground)
  float height_lower = 0; 

  // coord of line rollers and vertices(for D), all outputs in cm
  float D_1[] = { -70.785 / 10, -40.865 / 10, height_upper};
  float D_1atplat[] = { -70.785 / 10, -40.865 / 10, height_lower};
  float D_2[] = {0, 80.736 / 100, height_upper};
  float D_2atplat[] = {0, 80.736 / 10, height_lower};
  float D_3[] = {70.785 / 10, 40.865 / 10, height_upper};
  float D_3atplat[] = {70.785 / 10, 40.865 / 10, height_lower};
  
  // coord of line anchors
  float a1_1[] = { -70.785 / 10, -530 / 10, height_lower};
  float a1_2[] = {70.785 / 10, -530 / 10, height_lower};
  float a2_1[] = { -530 / 10, 224.26 / 10, height_lower};
  float a2_2[] = { -530 / 10, 387.731 / 10, height_lower};
  float a3_1[] = {530 / 10, 387.731 / 10, height_lower};
  float a3_2[] = {530 / 10, 224.26 / 10, height_lower};

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
  float spoolDiameter = 11; // cm
  float spoolCirc = PI * spoolDiameter;

  // for each of the below, a1 and a2 should be equal, same for b1 and b2, and c1 and c2
  // 10 turns of motor is one turn of spool; motor has 200 steps per turn 
  int motorSteps_a1 = ((lineDiffa1) / (spoolCirc)) * 10 * 200; 
  int motorSteps_b1 = ((lineDiffb1) / (spoolCirc)) * 10 * 200;
  int motorSteps_c1 = ((lineDiffc1) / (spoolCirc)) * 10 * 200;
  int motorSteps_d1 = ((lineDiffd1) / (spoolCirc)) * 10 * 200;
  
  int abs_a = abs(motorSteps_a1);
  int abs_b = abs(motorSteps_b1);
  int abs_c = abs(motorSteps_c1);
  int abs_d = abs(motorSteps_d1);
  
  int stepsArray[] = {abs_a,abs_b,abs_c,abs_d};

  // for checking the number of motor steps per spool:
   /* Serial.println("These are the motor steps:");
      Serial.println(abs_a);
      Serial.println(abs_b);
      Serial.println(abs_c);
      Serial.println(abs_d); */

// Compare all 4 values to find highest
  int highVal = stepsArray[0];
  for (int n = 1; n < 4; n++) {
   if (stepsArray[n] > highVal) {
        highVal = stepsArray[n];
   }
  }
  
//  COUNTERS
  int count_a = 0;
  int count_b = 0;
  int count_c = 0;
  int count_d = 0;
  
  for(int x = 0; x < highVal; x++){
//  SET CLOCKWISE OR ANTICLOCKWISE
    if (lineDiffa1 > 0){
      digitalWrite(dirPinA, LOW);
    }
    else {
      digitalWrite(dirPinA, HIGH);
    }
    
    if (lineDiffb1 > 0){
      digitalWrite(dirPinB, HIGH);
    }
    else {
      digitalWrite(dirPinB, LOW);
    }
    
    if (lineDiffc1 > 0){
      digitalWrite(dirPinC, HIGH);
    }
    else {
      digitalWrite(dirPinC, LOW);
    }
    
    if (lineDiffd1 > 0){
      digitalWrite(dirPinD, HIGH);
    }
    else {
      digitalWrite(dirPinD, LOW);
    }
    
//    LOOP continues until value of counter reaches motorsteps
//    For all 4: IF - high, delay,low


    if (count_a < abs_a) {
     // Serial.println("motor A moves");
      digitalWrite(stepPinA, HIGH);
    }
    
    if (count_b < abs_b) {
      //Serial.println("motor B moves");
      digitalWrite(stepPinB, HIGH);
    }
    if (count_c < abs_c) {
     digitalWrite(stepPinC, HIGH);
   }
    if (count_d < abs_d) {
      digitalWrite(stepPinD, HIGH);
    }
    
    // make sure delay only happens once
    if (count_a < abs_a||count_b < abs_b||count_c < abs_c||count_d < abs_d) {
     // Serial.println("delay1");
      delayMicroseconds(1000);
    }
   
  
    if (count_a < abs_a) {
     // Serial.println("motor A low");
      digitalWrite(stepPinA, LOW);
    }
   
    if (count_b < abs_b) {
      digitalWrite(stepPinB, LOW);
    }
    if (count_c < abs_c) {
      digitalWrite(stepPinC, LOW);
    }
    if (count_d < abs_d) {
      digitalWrite(stepPinD, LOW);
    }
    
  

    if (count_a < abs_a) {
     // Serial.println("delay 2");
      delayMicroseconds(1000);
    }
   
    if (count_b < abs_b) {
      delayMicroseconds(4000);
    }
    if (count_c < abs_c) {
      delayMicroseconds(4000);
    }
    if (count_d < abs_d) {
      delayMicroseconds(4000);
    }
   

//    Update counters
    count_a = count_a + 1;
    count_b = count_b + 1;
    count_c = count_c + 1;
    count_d = count_d + 1;
    
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

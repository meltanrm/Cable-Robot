// code for cable robot, wokring from input coordinates
// 21.01.22

#include <AccelStepper.h>

 // Define pin connections & motor's steps per revolution
  const int dirPin = 2;
  const int stepPin = 3;
  const int stepsPerRevolution = 200;


void setup() {
  // put your setup code here, to run once:

  // Declare motor control pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  mystepper.setSpeed(stepsPerSecond);

  // DECLARE ALL VARIABLES AND COORDINATES HERE

  // calculate length required for each of the cables INITIALLY
  
  float Cp[3]; // declare array to store input coordinates
  Cp = { 0, 0, 0};

  float height_upper= 1.397; // height (in metres) from top board to level with frame (0.038m above the ground)
  float height_lower= 0; // height 

  // coord of line rollers and vertices(for D)
  float D_1[]= {-70.785, -40.865, height_upper};
  float D_1atplat[] = {-70.785, -40.865, height_lower};
  float D_2[]= {0, 80.736, height_upper};
  float D_2atplat[] = {0, 80.736, height_lower};
  float D_3[]= {70.785, 40.865, height_upper};
  float D_3atplat[] = {70.785, 40.865, height_lower};

  // coord of line anchors
  float a1_1[] = {-70.785, -530, height_lower};
  float a1_2[] = {70.785, -530, height_lower};
  float a2_1[] = {-530, 224.26, height_lower};
  float a2_2[] = {-530, 387.731, height_lower};
  float a3_1[] = {530, 387.731, height_lower};
  float a3_2[] = {530, 224.26, height_lower};

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

  // declare all variables used in loop:
  float l_a1, l_a2, l_b1, l_b2, l_c1, l_c2, l_d1, l_d2, l_d3;
  


  
}

void loop() {

  recvInputCoord(); // receives input coordinates

  // coordinates of triangle platform vertices wrt center of platform, Cp
  float V_1[] = {D_1[0]+Cp[0], D_1[1]+Cp[1], 0+Cp[2]}; // lined up with D_1
  float V_2[] = {D_2[0]+Cp[0], D_2[1]+Cp[1], 0+Cp[2]}; // lined up with D_2
  float V_3[] = {D_3[0]+Cp[0], D_3[1]+Cp[1], 0+Cp[2]}; // lined up with D_3

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
  float spoolCirc = pi*spoolDiameter;

  // for each of the below, a1 and a2 should be equal, same for b1 and b2, and c1 and c2
  float motorSteps_a1 = (lineDiffa1/(spoolCirc))*8.45*200; // 8.45 turns of motor is one turn of spool; motor has 200 steps per turn
  float motorSteps_a2 = (lineDiffa2/(spoolCirc))*8.45*200;  // can be deleted??
  float motorSteps_b1 = (lineDiffb1/(spoolCirc))*8.45*200;
  float motorSteps_b2 = (lineDiffb2/(spoolCirc))*8.45*200; // can be deleted??
  float motorSteps_c1 = (lineDiffc1/(spoolCirc))*8.45*200;
  float motorSteps_c2 = (lineDiffc2/(spoolCirc))*8.45*200; // can be deleted??
  float motorSteps_d1 = (lineDiffd1/(spoolCirc))*8.45*200;
  float motorSteps_d2 = (lineDiffd2/(spoolCirc))*8.45*200;  // can be deleted??
  float motorSteps_d3 = (lineDiffd3/(spoolCirc))*8.45*200;  // can be deleted??
  
  // case for negative and positive changes in legths

  // Motor A
  if (lineDiffa1>0){
    digitalWrite(dirPin, HIGH); // set direction to clockwise
    for (int x=0; x<motorSteps_a1;x++)
    {
      digitalWrite(stepPin, HIGH);      // HOW TO DO THIS???
      delayMicroseconds(lineDiffa1 * 8.45 / (0.11 * pi));  
      delay(BRAKE);
    }
  }
  else {
    digitalWrite(dirPin, LOW);
    for (int x=0; x<motorSteps_a1;x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(lineDiffa1 * 8.45 / (0.11 * pi));  
      delay(BRAKE);
    }
  }

  // Motor B
  
    if (lineDiffb1>0){
    digitalWrite(dirPin, HIGH); // set direction to clockwise
    for (int x=0; x<motorSteps_b1;x++)
    {
      digitalWrite(stepPin, HIGH);      // HOW TO DO THIS???
      delayMicroseconds(lineDiffb1 * 8.45 / (0.11 * pi));  
      delay(BRAKE);
    }
  }
  else {
    digitalWrite(dirPin, LOW); // set direction to anticlockwise
    for (int x=0; x<motorSteps_b1;x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(lineDiffb1 * 8.45 / (0.11 * pi));  
      delay(BRAKE);
    }
  }

  // Motor C

    if (lineDiffc1>0){
    digitalWrite(dirPin, HIGH); // set direction to clockwise
    for (int x=0; x<motorSteps_c1;x++)
    {
      digitalWrite(stepPin, HIGH);      // HOW TO DO THIS???
      delayMicroseconds(lineDiffc1 * 8.45 / (0.11 * pi));  
      delay(BRAKE);
    }
  }
  else {
    digitalWrite(dirPin, LOW);
    for (int x=0; x<motorSteps_c1;x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(2000);
      delayMicroseconds(lineDiffc1 * 8.45 / (0.11 * pi));  
      delay(BRAKE);
    }
  }

  // Motor D
 
    if (lineDiffd1>0){
    digitalWrite(dirPin, HIGH); // set direction to clockwise
    for (int x=0; x<motorSteps_d1;x++)
    {
      digitalWrite(stepPin, HIGH);      // HOW TO DO THIS???
      delayMicroseconds(lineDiffd1 * 8.45 / (0.11 * pi));  
      delay(BRAKE);
    }
  }
  else {
    digitalWrite(dirPin, LOW);
    for (int x=0; x<motorSteps_d1;x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(lineDiffd1 * 8.45 / (0.11 * pi));  
      delay(BRAKE);
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

float lineLength(float coord1[], float coord2[]){
  float diff[3];
  float modResult;
  diff = (coord2-coord1);
  modResult = sqrt(sq(diff[1]), sq(diff[2]), sq(diff[3]));
  return modResult;
}

 void recvInputCoord() {
    int counter = 0;
    char endMarker = '\n';
    float character[3];
    boolean newData = false;
    
    while (Serial.available() > 0 && newData == false) {
        character = Serial.read();
        
        if (counter < 4) {
            Cp[counter] = character[counter];
            counter++;
        }
        else {
            Serial.print("The inputted coordinate is: "); // terminate the string
            
            Serial.println("x coordinate: " Cp[0]); // print out array
            Serial.println("y coordinate: " Cp[1]); 
            Serial.println("z coordinate: " Cp[2]); 
            }
            
            counter = 0; 
            newData = true;
        }
    }
}

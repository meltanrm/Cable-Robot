// code for cable robot, wokring from input coordinates
// 21.01.22

//#include <AccelStepper.h>
#include <Keypad.h>

 // Define pin connections & motor's steps per revolution
  const int dirPinB = 6; // motor B
  const int stepPinB = 7;
  const int dirPinD = 8; // motor D spool
  const int stepPinD = 9;
  const int dirPinA = 10; // motor A
  const int stepPinA = 11;
  const int dirPinC = 12; // motor C
  const int stepPinC = 13;
  const int stepsPerRevolution = 200;

// code for keypad
const byte ROWS = 4; //four rows
  const byte COLS = 4; //three columns
  char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };
  byte rowPins[ROWS] = {25, 26, 27, 28}; //connect to the row pinouts of the keypad
  byte colPins[COLS] = {29, 30, 31, 32}; //connect to the column pinouts of the keypad

  Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



void setup() {

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
    int counter = 0;
    char endMarker = '*';
    float character[3];
    float lineLength(float coord1[], float coord2[]){
      float diff[3];
      boolean newData = false;
    
      while (Serial.available() > 0 && newData == false) {
        character = (keypad.getKey())/100; // input in cm, converted to metres
        
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

void loop() {
  
  // COPIED ALL DEFINITIONS FROM SETUP
  float lineLength(float coord1[], float coord2[]);

  // calculate length required for each of the cables INITIALLY
  
  float Cp[3] = {0, 0, 0};// declare array to store input coordinates


  float height_upper= 1.397; // height (in metres) from top board to level with frame (0.038m above the ground)
  float height_lower= 0; // height 

  // coord of line rollers and vertices(for D)
  float D_1[]= {-70.785/1000, -40.865/1000, height_upper};
  float D_1atplat[] = {-70.785/1000, -40.865/1000, height_lower};
  float D_2[]= {0, 80.736/1000, height_upper};
  float D_2atplat[] = {0, 80.736/1000, height_lower};
  float D_3[]= {70.785/1000, 40.865/1000, height_upper};
  float D_3atplat[] = {70.785/1000, 40.865/1000, height_lower};

  // coord of line anchors
  float a1_1[] = {-70.785/1000, -530/1000, height_lower};
  float a1_2[] = {70.785/1000, -530/1000, height_lower};
  float a2_1[] = {-530/1000, 224.26/1000, height_lower};
  float a2_2[] = {-530/1000, 387.731/1000, height_lower};
  float a3_1[] = {530/1000, 387.731/1000, height_lower};
  float a3_2[] = {530/1000, 224.26/1000, height_lower};

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


  
  // FINISHED COPYING DEFINITIONS FROM SETUP

  recvInputCoord(); // receives input coordinates in cm, converted to metres in function
  

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
  float spoolCirc = PI*spoolDiameter;

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
    digitalWrite(dirPinA, HIGH); // set direction to clockwise
    for (int x=0; x<motorSteps_a1;x++)
    {
    digitalWrite(stepPinA, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPinA, LOW);
    delayMicroseconds(2000);
    }
  }
  else {
    digitalWrite(dirPinA, LOW);
    for (int x=0; x<motorSteps_a1;x++)
    {
    digitalWrite(stepPinA, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPinA, LOW);
    delayMicroseconds(2000);
    }
  }


  // Motor B
  
  if (lineDiffb1>0){
    digitalWrite(dirPinB, HIGH); // set direction to clockwise
    for (int x=0; x<motorSteps_b1;x++)
    {
    digitalWrite(stepPinB, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPinB, LOW);
    delayMicroseconds(2000);
    }
  }
  else {
    digitalWrite(dirPinB, LOW);
    for (int x=0; x<motorSteps_b1;x++)
    {
    digitalWrite(stepPinB, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPinB, LOW);
    delayMicroseconds(2000);
    }
  }

  // Motor C
  
     if (lineDiffc1>0){
    digitalWrite(dirPinC, HIGH); // set direction to clockwise
    for (int x=0; x<motorSteps_c1;x++)
    {
    digitalWrite(stepPinC, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPinC, LOW);
    delayMicroseconds(2000);
    }
  }
  else {
    digitalWrite(dirPinC, LOW);
    for (int x=0; x<motorSteps_c1;x++)
    {
    digitalWrite(stepPinC, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPinC, LOW);
    delayMicroseconds(2000);
    }
  }

  // Motor D
 
    if (lineDiffd1>0){
      digitalWrite(dirPinD, HIGH); // set direction to clockwise
      for (int x=0; x<motorSteps_d1;x++)
      {
      digitalWrite(stepPinD, HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPinD, LOW);
      delayMicroseconds(2000);
      }
    }
    else {
      digitalWrite(dirPinD, LOW);
      for (int x=0; x<motorSteps_d1;x++)
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
 


  float modResult;
  float coord2[], coord1[];
  float diff[] = (coord2-coord1);
  modResult = sqrt(sq(diff[1]), sq(diff[2]), sq(diff[3]));
  return modResult;

}

// Code to move final prototype of cable robot - 5 May 2022

// THIS IS JUST THE TEMPLATE - COORDINATES AND MEASUREMENTS STILL TO BE ADDED

// NOTES:
// Set the serial monitor from newline --> no line ending
// All input coordinates are in cm
// All coordinates, cable lengths and spool dimensions are in cm

// Pins and motors set-up: direction and steps
  const int dirPinA =  // motor A
  const int stepPinA =
  const int dirPinB =  // motor B
  const int stepPinB = 
  const int dirPinC =  // motor C
  const int stepPinC = 
  const int dirPinD = // motor D spool
  const int stepPinD = 

// Initialising coordinates of platform
float P[3] = {0, 0, 0};

void setup() {
  Serial.begin(9600);

  // Declaring pins as outputs
    pinMode(stepPinA, OUTPUT);
    pinMode(dirPinA, OUTPUT);
    pinMode(stepPinB, OUTPUT);
    pinMode(dirPinB, OUTPUT);
    pinMode(stepPinC, OUTPUT);
    pinMode(dirPinC, OUTPUT);
    pinMode(stepPinD, OUTPUT);
    pinMode(dirPinD, OUTPUT);
}

// Function to receive input coordinates:

void recvInputCoord() {

  Serial.println("Please input X coordinate: "); //Prompt User for Input
  while (Serial.available() == 0) {
  }
  P[0] = Serial.parseInt();

  Serial.println("Please input Y coordinate: "); //Prompt User for Input
  while (Serial.available() == 0) {
  }
  P[1] = Serial.parseInt();

  Serial.println("Please input Z coordinate: "); //Prompt User for Input
  while (Serial.available() == 0) {
  }
  P[2] = Serial.parseInt();

  Serial.println("Your input coordinates are: ");
  Serial.println(P[0]);
  Serial.println(P[1]);
  Serial.println(P[2]);
}

// Function to calculate cable lengths:

float cableLength(float coord1[3], float coord2[3]) {
     float diff[3];
     float modResult;
     for (int i = 0; i < 3; i++) {
        diff[i] = (coord2[i] - coord1[i]); 
     }
     modResult = (sqrt(sq(diff[0]) + sq(diff[1]) + sq(diff[2])));  
     
     return modResult;
}

void loop() {

  // Initialise cableLength function
     float lineLength(float coord1[], float coord2[]);

  // Height of prototype
    float height = 

  // Coordinates of line rollers

  // Coordinates of platform vertices at starting position

  // Coordinates of line anchors

  // Cable lengths at starting point
    // Two cables (1 and 2) come from each of the spools (A to C)
    // Three cables come from spool D
    // Distance calculated: line anchors to platform vertices
      float cable_a1_0
      float cable_a2_0
      float cable_b1_0
      float cable_b2_0
      float cable_c1_0
      float cable_c2_0
      float cable_d1_0 = height; // Applies only at start when cables are vertical
      float cable_d2_0 = height; 
      float cable_d3_0 = height;
  
  // Receives input coordinates
  recvInputCoord();

  // Coordinates of 3 platform vertices at new position
    float v1[] = {D_1[0] + P[0], D_1[1] + P[1], 0 + P[2]};
    float v2[] = {D_2[0] + P[0], D_2[1] + P[1], 0 + P[2]}; 
    float v3[] = {D_3[0] + P[0], D_3[1] + P[1], 0 + P[2]};

 // Cable lengths at new position
    // Distance calculated: line anchors to platform vertices
    float cable_a1
    float cable_a2
    float cable_b1
    float cable_b2
    float cable_c1
    float cable_c2
    float cable_d1
    float cable_d2
    float cable_d3

 // Calculate cable length difference: desired length - current length
    // Only required to be calculated for one cable per spool - works geometrically 
    float lineDiffa1 = l_a1 - l_a1_0; 
    float lineDiffb1 = l_b1 - l_b1_0;
    float lineDiffc1 = l_c1 - l_c1_0;
    float lineDiffd1 = l_d1 - l_d1_0; 

 // Moving the motors by desired amount
    // Finding the corresponding rotations required
    float spoolDiameter = 
    float spoolCirc = PI * spoolDiameter;
    
    // 200 motor steps per motor turn --> 10 motor turns = 1 spool turn
    int motorSteps_a1 = ((lineDiffa1) / (spoolCirc)) * 10 * 200; 
    int motorSteps_b1 = ((lineDiffb1) / (spoolCirc)) * 10 * 200;
    int motorSteps_c1 = ((lineDiffc1) / (spoolCirc)) * 10 * 200;
    int motorSteps_d1 = ((lineDiffd1) / (spoolCirc)) * 10 * 200;

    // Absolute values of motor steps
    int abs_a = abs(motorSteps_a1);
    int abs_b = abs(motorSteps_b1);
    int abs_c = abs(motorSteps_c1);
    int abs_d = abs(motorSteps_d1);
    
        // for checking the number of motor steps per spool:
         /* Serial.println("These are the motor steps:");
            Serial.println(abs_a);
            Serial.println(abs_b);
            Serial.println(abs_c);
            Serial.println(abs_d); */

    // Large 'for' loop to set motors to move at the same time
      // Loop continues until value of counter reaches value of motor steps
      // For all 4 spools: set direction of turns, comparison of counter vs. motorsteps, 
      // set pin HIGH, delay, set pin LOW.
    
      // Compare all 4 values to find highest
      int highVal = stepsArray[0];
      for (int n = 1; n < 4; n++) {
         if (stepsArray[n] > highVal) {
              highVal = stepsArray[n];
         }
      }
  
      // Counters
      int count_a = 0;
      int count_b = 0;
      int count_c = 0;
      int count_d = 0;

      for(int x = 0; x < highVal; x++){
        // Set direction of pins
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

        // Set pins HIGH
          if (count_a < abs_a) {
            digitalWrite(stepPinA, HIGH);
          }
          if (count_b < abs_b) {
            digitalWrite(stepPinB, HIGH);
          }
          if (count_c < abs_c) {
            digitalWrite(stepPinC, HIGH);
          }
          if (count_d < abs_d) {
            digitalWrite(stepPinD, HIGH);
          }


        // Delay 
          if (count_a < abs_a||count_b < abs_b||count_c < abs_c||count_d < abs_d) {
            delayMicroseconds(1000);
          }

        // Set pins LOW
          if (count_a < abs_a) {
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
          
        // Delay 
          if (count_a < abs_a||count_b < abs_b||count_c < abs_c||count_d < abs_d) {
            delayMicroseconds(1000);
          }
          
       // Update counters
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

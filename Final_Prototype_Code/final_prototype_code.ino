// Code to move final prototype of cable robot - 5 May 2022

// THIS IS JUST THE TEMPLATE - COORDINATES AND MEASUREMENTS STILL TO BE ADDED

// NOTES:
// Set the serial monitor from newline --> no line ending
// All input coordinates are in cm
// All coordinates, cable lengths and spool dimensions are in cm

// Pins and motors set-up: direction and steps
  const int dirPinA = 10; // motor A
  const int stepPinA = 11;
  const int dirPinB = 6; // motor B
  const int stepPinB = 7;
  const int dirPinC = 12; // motor C
  const int stepPinC = 13;
  const int dirPinD = 8; // motor D spool
  const int stepPinD = 9;

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

  float bounds_x[] = {-33.5,28.0};
  float bounds_y[] = {-50.5,50.5};
  float bounds_z[] = {0,30};
  
  bool dum = true;

  while(dum){
    int counter = 0;
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

    if ((P[0] < bounds_x[0]) || (P[0] > bounds_x[1])) {
      counter++;
    }
    if ((P[1] < bounds_y[0]) || (P[1] > bounds_y[1])) {
      counter++;
    }
    if ((P[2] < bounds_z[0]) || (P[2] > bounds_z[1])) {
      counter++;
    }
    if (counter == 0) {
      dum = false;
      break;
    }

    Serial.println("Sorry, you input was out of bounds.");
    Serial.println("Please input coordinates within the boundaries.");
    Serial.println("X bounds: -33.5 to 28.0 cm");
    Serial.println("Y bounds: -50.5 to 50.5 cm");
    Serial.println("Z bounds: 0 to 30 cm"); 
  }
  
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
     float cableLength(float coord1[], float coord2[]);

  // Height of prototype
    float height_upper = 56.4196 - 26.6; // relative to height of line anchors
    float height_lower = 0; // height of line anchors set as zero

  // Coordinates of line rollers for D spool (used below)
    float D1[] = {4.8948, 0, height_upper};
    float D2[] = {-12.5185, -10.0536, height_upper};
    float D3[] = {-12.5185, 10.0536, height_upper};

  // Coordinates of platform vertices at starting position
    float P1_0[]= {D1[0], D1[1], height_lower};
    float P2_0[]= {D2[0], D2[1], height_lower};
    float P3_0[]= {D3[0], D3[1], height_lower};

  // Coordinates of line anchors
    float a1[] = {28.6891, -41.2129, height_lower};
    float a2[] = {11.2757, -51.2665, height_lower};
    float b1[] = {28.6891, 41.2129, height_lower};
    float b2[] = {11.2757, 51.2665, height_lower};
    float c1[] = {-34.0, -10.0536, height_lower};
    float c2[] = {-34.0, 10.0536, height_lower};

  // Cable lengths at starting point
    // Two cables (1 and 2) come from each of the spools (A to C)
    // Three cables come from spool D
    // Distance calculated: line anchors to platform vertices
      float l_a1_0 = 47.5885;
      float l_a2_0 = 47.5885;
      float l_b1_0 = 47.5885;
      float l_b2_0 = 47.5885;
      float l_c1_0 = 21.4815;
      float l_c2_0 = 21.4815;
      float l_d1_0 = height_upper; // Applies only at start when cables are vertical
      float l_d2_0 = height_upper; 
      float l_d3_0 = height_upper;
  
  // Receives input coordinates
    recvInputCoord();

  // Coordinates of 3 platform vertices at new position
    float v1[] = {D1[0] + P[0], D1[1] + P[1], D1[2] + P[2]};
    float v2[] = {D2[0] + P[0], D2[1] + P[1], D2[2] + P[2]}; 
    float v3[] = {D3[0] + P[0], D3[1] + P[1], D3[2] + P[2]};

 // Cable lengths at new position
    // Distance calculated: line anchors to platform vertices
    float l_a1 = cableLength(a1, v1);
    float l_a2 = cableLength(a2, v2);
    float l_b1 = cableLength(b1, v1);
    float l_b2 = cableLength(b2, v3);
    float l_c1 = cableLength(c1, v2);
    float l_c2 = cableLength(c2, v3);
    float l_d1 = cableLength(v1, D1);
    float l_d2 = cableLength(v2, D2);
    float l_d3 = cableLength(v3, D3);
      

 // Calculate cable length difference: desired length - current length
    // Only required to be calculated for one cable per spool - works geometrically 
    float lineDiffa1 = l_a1 - l_a1_0; 
    float lineDiffb1 = l_b1 - l_b1_0;
    float lineDiffc1 = l_c1 - l_c1_0;
    float lineDiffd1 = l_d1 - l_d1_0; 

 // Moving the motors by desired amount
    // Finding the corresponding rotations required
    float spoolDiameter = 11;
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
  
    int stepsArray[] = {abs_a,abs_b,abs_c,abs_d};
    
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
            digitalWrite(dirPinC, LOW);
          }
          else {
            digitalWrite(dirPinC, HIGH);
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

//testing that the keypad input is being received
#include <Keypad.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {25, 26, 27, 28}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {29, 30, 31, 32}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup(){
  Serial.begin(9600);
}

void loop(){

  int key = int(keypad.getKey());
    int keyAsANumber = key - 48;


  if (key){
    Serial.println(keyAsANumber+4);
  }
}

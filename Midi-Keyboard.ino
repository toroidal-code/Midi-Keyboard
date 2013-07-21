#include <Keypad.h>

const byte rows = 9;
const byte cols = 6;
const int  midiNotes[] = {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84};
char keys[rows][cols] = {
  {0,1,2,3,4,5}, 
  {6,7,8,9,10,11}, 
  {12,13,14,15,16,17}, 
  {18,19,20,21,22,23}, 
  {24,25,26,27,28,29}, 
  {30,31,32,33,34,35}, 
  {36,37,38,39,40,41}, 
  {42,43,44,45,46,47}, 
  {48,49,50,51,52,53},  
};

char oldKeySwitch[54]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char keySwitch[54]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//MEGA2560 pinout header: 53,51,49,47,45,43,41,39,37,35,33,31,29,27,25,23
byte megaRowPins[rows] = {53, 51, 49, 47, 45, 31, 29, 27, 25};
byte megaColPins[cols] = {43, 41, 39, 37, 35, 33};
//byte rowPins[rows] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
//byte colPins[cols] = {A5, A4, A3, A2, A1, A0};
byte teensyRowPins[rows] = {0, 1, 2, 3, 4, 11, 12, 13, 15};
byte teensyColPins[cols] = {5, 6, 7, 8, 9, 10};


Keypad keypad = Keypad(makeKeymap(keys),teensyRowPins,teensyColPins,rows,cols); 

void setup(){
//  Serial.begin(31250);
  Serial.begin(115200);
  keypad.setDebounceTime(0); 
  keypad.setHoldTime(1000000); 
} 

void loop(){
 keypad.getKeys(); 
 if(1){
   for (int i=0; i<LIST_MAX; i++)   // Scan the entire list for any active keys.
      {
        if (keypad.key[i].kchar)    // Check for an active key.
        {
          switch (keypad.key[i].kstate) {
              case PRESSED:
                  if (keypad.key[i].stateChanged)
                  {
                    keySwitch[i] = 1;
                    if (keySwitch[i] == 1 && oldKeySwitch[i] == 0)
                      noteOn(0x90, midiNotes[keypad.key[i].kchar], 0x7F);
                  }
                  break;
              case RELEASED:
                  if (keypad.key[i].stateChanged)
                  {
                    keySwitch[i] = 0;
                    if (keySwitch[i] == 0 && oldKeySwitch[i] == 1)
                      noteOn(0x90, midiNotes[keypad.key[i].kchar], 0x00);
                  }  
                  break;
          }
        }
        for (int j=0; j<LIST_MAX; j++){
          oldKeySwitch[j] = keySwitch[j];
        }
      }
 }
} 

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}





#include <TVout.h>
#include <fontALL.h>

TVout TV;
unsigned char x,y;
int del = 7000;
int cl = 0;

char inData[50]; // Allocate some space for the string
char inChar; // Where to store the character read
int index = 0; // Index into array; where to store the character

void setup()  {
  Serial.begin(9600);
  Serial.print("Power On\n");
  x=0;
  y=0;
  TV.begin(NTSC);  //for devices with only 1k sram(m168) use TV.begin(_NTSC,128,56)
  TV.select_font(font8x8ext);
}

void loop() {
  



  
  while(Serial.available() > 0)
  // Don't read unless you know there is data
  
  {
      if(index < 49) // One less than the size of the array
      {
          inChar = Serial.read(); // Read a character
          Serial.print("Index: ");
          Serial.print(index);
          Serial.print("\n");
          Serial.print("Char: ");
          Serial.print(inChar);
          Serial.print("\n");
          inData[index] = inChar; // Store it
          index++; // Increment where to write next
          inData[index] = '\0'; // Null terminate the string
      }
  }
  // Now do something with the string (but not using ==)
  TV.clear_screen();
  Serial.print("\n**\n");
  Serial.print("Index: ");
  Serial.print(index);
  Serial.print("\n");
  Serial.print("Last Char: ");
  Serial.print(inData[index - 2]);
  Serial.print("\n");
  Serial.print("inData: ");
  Serial.print(inData);
  Serial.print("\n");
  Serial.print("\n**\n");
  char reset[1] = "|";
  if (inData[index - 2] == reset[0]) {
    Serial.print("\n\nRESET\n\n");
    while(index > 0) {
      inData[index] = "\0";
      index --;
    }
    inData[index] = "~";
    TV.delay(2000);
  } else {
    if (index == 0) {
      TV.delay(2000);
    } else {
      TV.println(inData);
      TV.delay(2000);
    }
  }
}

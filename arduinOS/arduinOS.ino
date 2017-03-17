#include <PS2uartKeyboard.h>

#include <TVout.h>
#include <fontALL.h>
//#include <PS2Keyboard.h>


TVout TV;
unsigned char x,y;
int del = 7000;
int cl = 0;

int inputVal = 0;
char onScreen[50];
int charIndex = 0;

const int DataPin = 2;
const int IRQpin =  3;

PS2uartKeyboard keyboard;

void setup()  {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.print("Power On\n");
  x=0;
  y=0;
  TV.begin(NTSC);  //for devices with only 1k sram(m168) use TV.begin(_NTSC,128,56)
  TV.select_font(font8x8ext);
}

void loop() {
  if (charIndex < 0) {
    charIndex = 0;
  }
  if (keyboard.available()) {
    // read the next key
    char c = keyboard.read();
    
    // check for some of the special keys
    if (c == PS2_ENTER) {
      Serial.println();
    } else if (c == PS2_TAB) {
      Serial.print("[Tab]");
    } else if (c == PS2_ESC) {
      Serial.print("[ESC]");
    } else if (c == PS2_PAGEDOWN) {
      Serial.print("[PgDn]");
    } else if (c == PS2_PAGEUP) {
      Serial.print("[PgUp]");
    } else if (c == PS2_LEFTARROW) {
      Serial.print("[Left]");
    } else if (c == PS2_RIGHTARROW) {
      Serial.print("[Right]");
    } else if (c == PS2_UPARROW) {
      Serial.print("[Up]");
    } else if (c == PS2_DOWNARROW) {
      Serial.print("[Down]");
    } else if (c == PS2_DELETE) {
      Serial.print("[Del]");
    } else {
      
      // otherwise, just print all normal characters
      Serial.print(c);
      onScreen[charIndex++] = c;
    }
    TV.clear_screen();
    TV.println(onScreen);
    Serial.println(onScreen);
    delay(200);
  } else {
    TV.println("No Keyboard");
    delay(3000);
  }
}

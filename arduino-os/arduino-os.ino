#include <TVout.h>
#include <fontALL.h>

TVout TV;
unsigned char x,y;
int del = 7000;
int cl = 0;

int bit1Pin = 2;
int bit2Pin = 3;
int bit4Pin = 4;
int bit8Pin = 5;
int bit16Pin = 6;
int sendPin = 8;
int clearPin = 10;

bool bit1Val = 0;
bool bit2Val = 0;
bool bit4Val = 0;
bool bit8Val = 0;
bool bit16Val = 0;
bool sendVal = 0;
bool clearVal = 0;

int inputVal = 0;
char onScreen[50];
int charIndex = 0;

void setup()  {
  Serial.begin(9600);
  Serial.print("Power On\n");
  x=0;
  y=0;
  TV.begin(NTSC);  //for devices with only 1k sram(m168) use TV.begin(_NTSC,128,56)
  TV.select_font(font8x8ext);
  pinMode(bit1Pin, INPUT_PULLUP);  
  pinMode(bit2Pin, INPUT_PULLUP); 
  pinMode(bit4Pin, INPUT_PULLUP);  
  pinMode(bit8Pin, INPUT_PULLUP);
  pinMode(bit16Pin, INPUT_PULLUP);
  pinMode(sendPin, INPUT_PULLUP);  
  pinMode(clearPin, INPUT_PULLUP);
}

void loop() {
  if (charIndex < 0) {
    charIndex = 0;
  }
  sendVal = digitalRead(sendPin);
  clearVal = digitalRead(clearPin);
  if (sendVal == LOW){
  
    bit1Val = digitalRead(bit1Pin);
    bit2Val = digitalRead(bit2Pin);
    bit4Val = digitalRead(bit4Pin);
    bit8Val = digitalRead(bit8Pin);
    bit16Val = !digitalRead(bit16Pin);

    Serial.print("Input: ");
    Serial.print(bit1Val);
    Serial.print(bit2Val);
    Serial.print(bit4Val);
    Serial.print(bit8Val);
    Serial.println(bit16Val);

    inputVal =  64 +
                bit1Val +
                (bit2Val * 2) +
                (bit4Val * 4) +
                (bit8Val * 8) +
                (bit16Val * 16);

    if (inputVal == 64) {
      inputVal -= 32;
    }

    Serial.print("Value: ");
    Serial.println(inputVal);

    char nextChar = inputVal;

    Serial.print("Char: ");
    Serial.println(nextChar);

    onScreen[charIndex++] = nextChar;
    Serial.print("onScreen: ");
    Serial.println(onScreen);
    TV.clear_screen();
    TV.println(onScreen);
    delay(200);
  } else {
    if (clearVal == LOW) {
      bit16Val = digitalRead(bit16Pin);
      if (bit16Val) {
        onScreen[--charIndex] = 32;
      } else {
        while(charIndex >= 0) {
          onScreen[charIndex--] = 32;
        }
      }
    }
    TV.clear_screen();
    TV.println(onScreen);
    delay(200);
  }
}

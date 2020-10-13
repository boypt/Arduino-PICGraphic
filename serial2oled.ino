#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  //  Serial.setTimeout(100);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x64)
  display.display();
}

#define bufSize 1024

void loop()
{
  char cmd = 0;
  Serial.readBytes(&cmd, 1);
  switch (cmd)
  {
    case 'i':
      display.clearDisplay();
      break;
    case 'f':
      if (Serial.readBytes(display.getBuffer(), bufSize) == bufSize) {
        display.display();
      }
      break;
    default:
      return;
  }

  Serial.print('f');
  Serial.print(cmd);
  Serial.flush();
}

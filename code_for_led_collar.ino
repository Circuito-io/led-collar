// Global variables and defines
#define THRESHOLD_ldr   100
int ldrAverageLight;
#define NUMOFPIXEL 27
// object initialization
LDR ldr(LDR_PIN_SIG);
Adafruit_NeoPixel ledStripBattery(LEDSTRIPBATTERY_PIN_DI);

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup()
{
  // Setup Serial which is useful for debugging
  // Use the Serial Monitor to view printed messages
  Serial.begin(9600);
  while (!Serial) ; // wait for serial port to connect. Needed for native USB
  Serial.println("start");

  ldrAverageLight = ldr.readAverage();
  ledStripBattery.begin(); // This initializes the NeoPixel library.
  ledStripBattery.show(); // Initialize all pixels to 'off'

}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop()
{
  // Get current light reading, substract the ambient value to detect light changes
  int ldrSample = ldr.read();
  Serial.print(F("Light Diff: ")); Serial.println(ldrSample);
  if (ldrSample < 500)
  {
    rainbow(20);
    sequenceA();
    rainbowCycle(10);
    sequenceB();
    turnOff();

  }
}


void turnOff()
{
  for (int i = 0 ; i < NUMOFPIXEL ; i++) 
  {
    ledStripBattery.setPixelColor(i, ledStripBattery.Color(0, 0, 0)); // turn off last led
  }
  ledStripBattery.show(); //update pixel color to the hardware.
}


void sequenceA()
{
  for (int j = NUMOFPIXEL ; j > 0 ; j--)
  {
    for (int i = 0 ; i < j ; i++) 
    {
      // set pixels Color to RGB values, from 0,0,0 up to 255,255,255
      ledStripBattery.setPixelColor(i, Wheel(((i * 256 / NUMOFPIXEL) + j) & 255)); // turn on green color on led #i.
      if (i > 0)
        ledStripBattery.setPixelColor(i - 1, ledStripBattery.Color(0, 0, 0)); // turn off last led
      ledStripBattery.show(); //update pixel color to the hardware.
      delay(20);
    }
  }
}

void sequenceB()
{
  {
    for (int j = NUMOFPIXEL ; j > 0 ; j--)
    {
      for (int i = 0 ; i < NUMOFPIXEL ; i++)
      {
        for (int k = 0 ; k < 7 ; k++)
        {
          // set pixels Color to RGB values, from 0,0,0 up to 255,255,255
          ledStripBattery.setPixelColor((i + k) % NUMOFPIXEL , Wheel((((i + k) % NUMOFPIXEL * 256 / NUMOFPIXEL) + j) & 255)); // turn on green color on led #i.
          if (i > 0)
            ledStripBattery.setPixelColor(i - 1, ledStripBattery.Color(0, 0, 0)); // turn off last led
        }
        ledStripBattery.show(); //update pixel color to the hardware.

        delay(20);
      }
    }
  }
}



// =================== NeoPixel functions by Adafruit ====================//
//          https://github.com/adafruit/Adafruit_NeoPixel
// Fill the dots one after the other with a color
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < ledStripBattery.numPixels(); i++) {
      ledStripBattery.setPixelColor(i, Wheel((i + j) & 255));
    }
    ledStripBattery.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < NUMOFPIXEL; i++) {
      ledStripBattery.setPixelColor(i, Wheel(((i * 256 / NUMOFPIXEL) + j) & 255));
    }
    ledStripBattery.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return ledStripBattery.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return ledStripBattery.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return ledStripBattery.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


/***************************************************
  This is an example for the SHT4x Humidity & Temp Sensor
  Using the soil sensor from Adafruit
  ----> https://www.adafruit.com/product/4026
  Connected to a Lilygo T-Display-S3
  What I consider the bare minimum to display readings on the TFT
 ****************************************************/
#define I2C_SDA 43
#define I2C_SCL 44
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite scrn = TFT_eSprite(&tft);   //use a sprite to eliminate filickering

#include "Adafruit_seesaw.h"
Adafruit_seesaw ss;

void setup() {
  tft.init();
  tft.setRotation(3);         //USB on left
  tft.fillScreen(TFT_BLACK);
  scrn.createSprite(320, 170);
  scrn.fillSprite(TFT_BLACK);
  scrn.setTextColor(TFT_CYAN, TFT_BLACK);

  Wire.begin(I2C_SDA, I2C_SCL);
  if (!ss.begin(0x36)) {
    scrn.setTextColor(TFT_ORANGE, TFT_BLACK);
    scrn.drawCentreString("Seesaw not found", 160, 50, 4);
    scrn.pushSprite(0, 0);
    while (1) delay(1);
  }
}

void loop() {
  scrn.fillSprite(TFT_BLACK);
  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);

  scrn.drawCentreString("Soil Sensor", 160, 0, 4);
  scrn.drawString("Temperature:", 0, 40, 4);
  scrn.drawCentreString(String(tempC * 9 / 5 + 32), 220, 40, 4);
  scrn.drawString("Moisture:", 0, 80, 4);
  scrn.drawCentreString(String(capread), 220, 80, 4);
  scrn.pushSprite(0, 0);

  delay(300);
}

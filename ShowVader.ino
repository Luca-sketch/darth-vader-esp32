#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include "Imperial.h"
#include "blue.h"
#include "green.h"
#include "oragne.h"
#include "purple.h"
#include "red.h"

#define TFT_BL 21

TFT_eSPI tft = TFT_eSPI();
SPIClass touchSPI = SPIClass(VSPI);
XPT2046_Touchscreen touch(33, 36);

const uint16_t* frames[] = { blue, green, oragne, purple, red };
const int TOTAL_FRAMES = 5;
int frameAtual = 0;

#define IMG_W 240
#define IMG_H 240
#define IMG_X ((320 - IMG_W) / 2)

unsigned long ultimaTroca = 0;
#define INTERVALO_FRAME 600

void inicializarDisplay() {
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.init();
  tft.setRotation(1);
  tft.writecommand(0x36);
  tft.writedata(0x80);
  tft.writecommand(0x13);
  tft.writecommand(0x20);

  tft.fillScreen(TFT_BLACK);
}

void entradaVader() {
  for (int y = 240; y >= 0; y -= 6) {
    tft.fillScreen(TFT_BLACK);
    tft.pushImage(IMG_X, y, IMG_W, IMG_H, frames[0]);
    imperialTick();
    delay(8);
  }
  tft.fillScreen(TFT_BLACK);
  tft.pushImage(IMG_X, 0, IMG_W, IMG_H, frames[0]);
  delay(800);
}

void setup() {
  Serial.begin(115200);
  imperialSetup();
  inicializarDisplay();

  touchSPI.begin(25, 39, 32, 33);
  touch.begin(touchSPI);

  entradaVader();
  ultimaTroca = millis();
}

void loop() {
  // Music, not the display
  imperialTick();

 // Switches frame every 600ms
  if (millis() - ultimaTroca >= INTERVALO_FRAME) {
    frameAtual = (frameAtual + 1) % TOTAL_FRAMES;
    tft.pushImage(IMG_X, 0, IMG_W, IMG_H, frames[frameAtual]);
    ultimaTroca = millis();
  }
}
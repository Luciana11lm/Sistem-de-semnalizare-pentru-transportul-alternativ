#include "OLEDUtils.h"

void initializeOLED(Adafruit_SSD1306& display) {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Eroare la initializarea OLED!"));
    for (;;);
  }
  display.clearDisplay();
  display.display();
}

void drawArc(int16_t x, int16_t y, int16_t radius, int16_t start_angle, int16_t end_angle, uint16_t color, Adafruit_SSD1306& display) {
  for (int angle = start_angle; angle <= end_angle; angle++) {
    int16_t x_pos = x + cos(angle * DEG_TO_RAD) * radius;
    int16_t y_pos = y - sin(angle * DEG_TO_RAD) * radius;
    display.drawPixel(x_pos, y_pos, color);
  }
}

void drawSignal(int signalLevel, int distance, Adafruit_SSD1306& display) {
  display.clearDisplay();

  // Baza simbolului (cercul)
  display.fillCircle(64, 48, 4, SSD1306_WHITE);

  // Desenează arcele folosind un for
  for (int i = 1; i <= signalLevel; i++) {
    drawArc(64, 48, i * 10, 0, 180, SSD1306_WHITE, display);
  }

  // Afișarea distanței numerice
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 56);
  display.print("Dist: ");
  display.print(distance);
  display.println(" cm");

  display.display();
}

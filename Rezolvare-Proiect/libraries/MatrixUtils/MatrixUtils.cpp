#include "MatrixUtils.h"

// Inițializare matrice LED
void initializeMatrix(LedControl& matrix) {
  matrix.shutdown(0, false); // Activează matricea
  matrix.setIntensity(0, 0); // Setează intensitatea la minim
  matrix.clearDisplay(0);    // Șterge afișajul
}

// Afișează o săgeată pe matrice
void displayArrow(int arrow[], LedControl& matrix) {
  matrix.clearDisplay(0);
  for (int i = 0; i < 8; i++) {
    matrix.setRow(0, i, arrow[i]);
  }
}

// Afișează un cerc pe matrice
void displayCircle(int circle[], LedControl& matrix) {
  matrix.clearDisplay(0);
  for (int i = 0; i < 8; i++) {
    matrix.setRow(0, i, circle[i]);
  }
}

// Șterge matricea
void clearMatrix(LedControl& matrix) {
  matrix.clearDisplay(0);
}

// Funcție pentru clipirea săgeții
void blinkArrow(int arrow[], LedControl& matrix) {
  static unsigned long previousMillis = 0; // Timpul anterior
  static int blinkCount = 0;               // Contor pentru numărul de clipiri
  static bool isOn = false;                // Starea curentă (ON/OFF)
  const unsigned long interval = 150;      // Durata ON/OFF în milisecunde

  unsigned long currentMillis = millis(); // Timpul curent

  if (blinkCount < 3) { // Clipim de 3 ori
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis; // Actualizăm timpul anterior

      if (isOn) {
        clearMatrix(matrix); // Oprim afișarea
        isOn = false;        // Trecem la OFF
        blinkCount++;        // Incrementăm contorul la finalul unui ciclu ON-OFF
      } else {
        displayArrow(arrow, matrix); // Afișăm săgeata
        isOn = true;                 // Trecem la ON
      }
    }
  } else {
    blinkCount = 0; // Resetăm contorul pentru următoarea apelare
  }
}

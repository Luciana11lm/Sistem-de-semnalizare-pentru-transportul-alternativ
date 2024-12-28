/*
Cerinte pentru studenti:
Scopul acestui set de exerciții este să învățați cum să utilizați buclele și matricile pentru a controla afișajul în funcție de mișcarea joystick-ului.

Exercițiul 1: Joystick - Introducere în axele X și Y
Scop: Să înțelegeți cum funcționează un joystick prin citirea valorilor axelor X și Y și afișarea acestora pe monitorul serial.

Cerințe:
  1. Conectați un joystick la pini analogici (A0 pentru axa X și A1 pentru axa Y).
  2. Modificați funcția loop() astfel încât să citească valorile axelor și să le afișeze pe monitorul serial.
  3. Afișați mesajele sub forma:
     X: [valoare], Y: [valoare]
*/

void setup() {
  Serial.begin(9600); // Pornire comunicare serială
}

void loop() {
  int xValue = analogRead(A0); // Citire axa X
  int yValue = analogRead(A1); // Citire axa Y

  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(", Y: ");
  Serial.println(yValue);

  delay(200); // Pauză pentru citire
}

/*
Exercițiul 2: Joystick - Afișare săgeți pe matrice
Scop: Să afișați săgeți direcționale pe matricea MAX7219 utilizând joystick-ul. Completați codul lipsă pentru a citi valorile axei X și a afișa săgețile direct.

Cerințe:
1. Completați spațiile libere din codul de mai jos pentru a:
  - Citi valoarea axei X de la joystick.
  - Afișa săgeata stânga (arrowLeft) sau săgeata dreapta (arrowRight) în funcție de poziția joystick-ului.
  - Șterge afișajul dacă joystick-ul este centrat.

2. Folosiți pragul de 300 pentru a decide mișcările joystick-ului.

Hint-uri:
  - matrix.setRow(0, i, valoare) setează fiecare rând al matricei. Înlocuiți valoare cu elementele din array-ul arrowLeft sau arrowRight (ex: arrowLeft[i]).
  - Pentru ștergerea matricei, folosiți matrix.clearDisplay(0).
*/
#include <LedControl.h>

// Pini pentru joystick
#define JOY_X_PIN                         // Pinul pentru axa X a joystick-ului
const int threshold = _____________;      // Prag pentru mișcările joystick-ului

// Pini pentru matrice
int DIN = 10;                   // Pinul pentru date
int CS = 11;                    // Pinul pentru Chip Select
int CLK = 12;                   // Pinul pentru Clock

// Obiect pentru controlul matricei MAX7219
LedControl matrix = LedControl(DIN, CLK, CS, 1);

// Săgeți pentru afișare
int arrowLeft[8] = {
  B00011100,
  B00011100,
  B00011100,
  B11111111,
  B01111111,
  B00111110,
  B00011100,
  B00001000
};

int arrowRight[8] = {
  B00001000,
  B00011100,
  B00111110,
  B01111111,
  B11111111,
  B00011100,
  B00011100,
  B00011100
};

void setup() {
  // Configurare serială pentru debugging
  Serial.begin(9600);

  // Inițializare matrice
  matrix.shutdown(0, false); // Activează matricea
  matrix.clearDisplay(0);    // Șterge afișajul matricei

  Serial.println("Setup complet!");
}


void loop() {
  // **Citire valoare axa X de la joystick**
  int xValue = ______________ ; // ______________ (completați cu pinul potrivit)

  if (xValue < prag) {
    // **Afișare săgeată stânga**
    matrix.clearDisplay(0); // Șterge afișajul pentru a evita suprapunerea
    for (int i = 0; i < 8; i++) {
      matrix.setRow(0, i, ______________); // Completați cu valoarea corespunzătoare din `arrowLeft`
    }
  } else if (xValue > 1023 - prag) {
    // **Afișare săgeată dreapta**
    matrix.clearDisplay(0); // Șterge afișajul pentru a evita suprapunerea
    for (int i = 0; i < 8; i++) {
      matrix.setRow(0, i, ______________); // Completați cu valoarea corespunzătoare din `arrowRight`
    }
  } else {
    // **Centrare joystick: ștergere matrice**
    ______________; // Completați cu funcția pentru a șterge afișajul matricei
  }

  delay(100); // Pauză pentru stabilitate
}

/*
Rezolvare:
#include <LedControl.h>

// Pini pentru joystick
#define JOY_X_PIN A3            // Pinul pentru axa X a joystick-ului
const int threshold = 300;      // Prag pentru mișcările joystick-ului

// Pini pentru matrice
int DIN = 10;                   // Pinul pentru date
int CS = 11;                    // Pinul pentru Chip Select
int CLK = 12;                   // Pinul pentru Clock

// Obiect pentru controlul matricei MAX7219
LedControl matrix = LedControl(DIN, CLK, CS, 1);

// Săgeți pentru afișare
int arrowLeft[8] = {
  B00011100,
  B00011100,
  B00011100,
  B11111111,
  B01111111,
  B00111110,
  B00011100,
  B00001000
};

int arrowRight[8] = {
  B00001000,
  B00011100,
  B00111110,
  B01111111,
  B11111111,
  B00011100,
  B00011100,
  B00011100
};

void setup() {
  // Configurare serială pentru debugging
  Serial.begin(9600);

  // Inițializare matrice
  matrix.shutdown(0, false); // Activează matricea
  matrix.setIntensity(0, 5); // Setează intensitatea (0 - minim, 15 - maxim)
  matrix.clearDisplay(0);    // Șterge afișajul matricei

  Serial.println("Setup complet!");
}

void loop() {
  // **Citire valoare axa X de la joystick**
  int xValue = analogRead(JOY_X_PIN); // Citire pinul pentru axa X

  if (xValue < threshold) {
    // **Afișare săgeată stânga**
    matrix.clearDisplay(0); // Șterge afișajul pentru a evita suprapunerea
    for (int i = 0; i < 8; i++) {
      matrix.setRow(0, i, arrowLeft[i]); // Setează fiecare rând cu valorile din `arrowLeft`
    }
  } else if (xValue > 1023 - threshold) {
    // **Afișare săgeată dreapta**
    matrix.clearDisplay(0); // Șterge afișajul pentru a evita suprapunerea
    for (int i = 0; i < 8; i++) {
      matrix.setRow(0, i, arrowRight[i]); // Setează fiecare rând cu valorile din `arrowRight`
    }
  } else {
    // **Centrare joystick: ștergere matrice**
    matrix.clearDisplay(0); // Șterge afișajul matricei
  }

  delay(100); // Pauză pentru stabilitate
}

*/





















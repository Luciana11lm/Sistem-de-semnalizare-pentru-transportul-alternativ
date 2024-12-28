/*
Cerinte pentru studenti:
Scopul acestui set de exerciții este să învățați cum să afișați forme pe matricea MAX7219 și să interacționați cu ele prin funcții.
Veți folosi concepte precum matrici, bucle și funcții pentru a controla afișajul.

Cerinte:
  2. Realizați o clipire (blinking) pentru triunghi
    Descriere: Extindeți codul (de la ceritna 1) astfel încât triunghiul să clipească de trei ori înainte de a rămâne aprins.
    
    Cerință completă:
      1. Creați o funcție numită blinkTriangle().
      2. Afișați triunghiul timp de 200ms, apoi ștergeți matricea (matrix.clearDisplay(0)).
      3. Repetați de 3 ori acest proces
*/

//Rezolvare
#include <LedControl.h> // Biblioteca pentru controlul modulului MAX7219

// Definim pinii conectați la modulul MAX7219
#define DATA_PIN 12  // Pinul digital conectat la DIN
#define CLK_PIN 11   // Pinul digital conectat la CLK
#define CS_PIN 10    // Pinul digital conectat la CS

// Inițializăm obiectul LedControl pentru controlul matricei
LedControl matrix = LedControl(DATA_PIN, CLK_PIN, CS_PIN, 1); // Avem doar o matrice

// Definim matricea pentru triunghi
// Fiecare linie reprezintă un rând din matrice, iar fiecare bit controlează un LED (1 = aprins, 0 = stins)
int triangleMatrix[8] = {
  B00011000, // Rând 0: aprinde LED-urile din mijloc
  B00111100, // Rând 1: extinde rândul
  B01111110, // Rând 2: mai multe LED-uri aprinse
  B11111111, // Rând 3: rând complet aprins
  B00000000, // Rând 4: restul rândurilor sunt stinse
  B00000000,
  B00000000,
  B00000000
};

void setup() {
  // Pornim matricea și o configurăm
  matrix.shutdown(0, false);   // Pornim afișajul matricei 0
  matrix.setIntensity(0, 8);   // Setăm luminozitatea la nivel mediu (0-15)
  matrix.clearDisplay(0);      // Curățăm matricea înainte de a afișa ceva
}

void loop() {
  // Clipim triunghiul
  blinkTriangle();

  // Pauză de 1 secundă înainte de următoarea clipire
  delay(1000);
}

// Funcția pentru afișarea triunghiului pe matrice
void displayTriangle() {
  matrix.clearDisplay(0); // Curățăm afișajul pentru a preveni artefacte

  // Iterăm prin fiecare rând al matricei și setăm valorile LED-urilor
  for (int i = 0; i < 8; i++) {
    matrix.setRow(0, i, triangleMatrix[i]); // Afișăm conținutul fiecărui rând
  }
}

// Funcția pentru ștergerea matricei
void clearMatrix() {
  matrix.clearDisplay(0); // Ștergem toate LED-urile de pe matrice
}

// Funcția pentru clipirea triunghiului
void blinkTriangle() {
  for (int i = 0; i < 3; i++) { // Clipim triunghiul de 3 ori
    displayTriangle();   // Afișăm triunghiul
    delay(200);          // Îl lăsăm aprins timp de 200ms
    clearMatrix();       // Ștergem matricea
    delay(200);          // Pauză timp de 200ms cu matricea stinsă
  }
}

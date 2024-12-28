/*
Cerinte pentru studenti:
Scopul acestui set de exerciții este să învățați cum să afișați forme pe matricea MAX7219 și să interacționați cu ele prin funcții.
Veți folosi concepte precum matrici, bucle și funcții pentru a controla afișajul.

Cerinte:
  1. Afișați un triunghi pe matrice
    Descriere: Modificați codul astfel încât să afișeze un triunghi în locul cercului.
    Definiți matricea de date pentru triunghi și creați o funcție numită displayTriangle() care să afișeze această formă.

    Indicații:
    - Fiecare rând al matricei are 8 biți (LED-uri).
    - 1 = LED aprins, 0 = LED stins.

    Exemplu de matrice pentru un triunghi:
    int triangleMatrix[8] = {
      B00011000,
      B00111100,
      B01111110,
      B11111111,
      B00000000,
      B00000000,
      B00000000,
      B00000000
    };

    Cerință completă:
      1. Creați funcția displayTriangle().
      2. Folosiți matrix.setRow(0, i, triangleMatrix[i]) pentru a afișa fiecare rând al triunghiului.
      3. Afișați triunghiul în funcția loop().
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
  // Afișăm triunghiul
  displayTriangle();

  // Pauză de 2 secunde pentru a vedea afișajul
  delay(2000);
}

// Funcția pentru afișarea triunghiului pe matrice
void displayTriangle() {
  matrix.clearDisplay(0); // Curățăm afișajul pentru a preveni artefacte

  // Iterăm prin fiecare rând al matricei și setăm valorile LED-urilor
  for (int i = 0; i < 8; i++) {
    matrix.setRow(0, i, triangleMatrix[i]); // Afișăm conținutul fiecărui rând
  }
}



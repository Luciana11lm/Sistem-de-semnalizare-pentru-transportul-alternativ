/*
Cerinte pentru studenti:
Scopul acestui set de exerciții este să învățați cum să afișați forme pe matricea MAX7219 și să interacționați cu ele prin funcții.
Veți folosi concepte precum matrici, bucle și funcții pentru a controla afișajul.

Cerinte:
  4.Afișați un model care alternează între două forme (triunghi și pătrat)
    Descriere: Alternați între afișarea unui triunghi și a unui pătrat pe matrice. Fiecare formă ar trebui să fie afișată timp de 1 secundă.
    
    Exemplu de matrice pentru un pătrat:
    int squareMatrix[8] = {
      B00111100,
      B01111110,
      B01111110,
      B01111110,
      B01111110,
      B01111110,
      B01111110,
      B00111100
    };


    Cerință completă:
      1. Creați funcțiile displaySquare() și displayTriangle().
      2. În funcția loop(), afișați triunghiul, așteptați 1 secundă, apoi ștergeți matricea.
      3. Afișați pătratul, așteptați 1 secundă, apoi ștergeți matricea.
*/

//Rezolvare
#include <LedControl.h> // Biblioteca pentru controlul modulului MAX7219

// Definim pinii conectați la modulul MAX7219
#define DATA_PIN 12  // Pinul digital conectat la DIN
#define CLK_PIN 11   // Pinul digital conectat la CLK
#define CS_PIN 10    // Pinul digital conectat la CS

// Definim pinul pentru buton
#define BUTTON_PIN 2 // Pinul digital conectat la buton

// Inițializăm obiectul LedControl pentru controlul matricei
LedControl matrix = LedControl(DATA_PIN, CLK_PIN, CS_PIN, 1); // Avem doar o matrice

// Definim două forme: triunghi și pătrat
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

int squareMatrix[8] = {
  B00111100,
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B00111100,
  B00000000
};

// Variabilă pentru a ține evidența formei afișate
bool isTriangleDisplayed = true;

void setup() {
  // Configurăm matricea și butonul
  matrix.shutdown(0, false);    // Pornim afișajul matricei
  matrix.setIntensity(0, 8);    // Setăm luminozitatea la nivel mediu
  matrix.clearDisplay(0);       // Curățăm matricea

  pinMode(BUTTON_PIN, INPUT_PULLUP); // Configurăm pinul butonului ca intrare cu rezistență internă de pull-up
}

void loop() {
  // Verificăm dacă butonul este apăsat
  if (digitalRead(BUTTON_PIN) == LOW) { // LOW indică că butonul este apăsat
    delay(200); // Debouncing (pauză pentru a evita citirile multiple)

    // Alternăm forma afișată
    if (isTriangleDisplayed) {
      displaySquare();          // Afișăm pătratul
      isTriangleDisplayed = false;
    } else {
      displayTriangle();        // Afișăm triunghiul
      isTriangleDisplayed = true;
    }
  }
}

// Funcția pentru afișarea triunghiului
void displayTriangle() {
  matrix.clearDisplay(0); // Curățăm matricea
  for (int i = 0; i < 8; i++) {
    matrix.setRow(0, i, triangleMatrix[i]); // Afișăm fiecare rând al triunghiului
  }
}

// Funcția pentru afișarea pătratului
void displaySquare() {
  matrix.clearDisplay(0); // Curățăm matricea
  for (int i = 0; i < 8; i++) {
    matrix.setRow(0, i, squareMatrix[i]); // Afișăm fiecare rând al pătratului
  }
}

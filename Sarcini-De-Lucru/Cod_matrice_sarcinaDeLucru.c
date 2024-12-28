/*
Cerinte pentru studenti:
Scopul acestui set de exerciții este să învățați cum să afișați forme pe matricea MAX7219 și să interacționați cu ele prin funcții.
Veți folosi concepte precum matrici, bucle și funcții pentru a controla afișajul.

Cerinte:
  2. Săgeți animate care se mișcă spre dreapta
    Descriere: Creați o animație pentru o săgeată care se mișcă spre dreapta.
     Folosiți o matrice pentru săgeată și creați o funcție moveArrowRight() care mută săgeata cu un pas la dreapta până dispare de pe ecran.
    
    Exemplu de matrice pentru o săgeată:
    int arrowMatrix[8] = {
      B00001000,
      B00001100,
      B11111110,
      B11111111,
      B11111110,
      B00001100,
      B00001000,
      B00000000
    };


    Cerință completă:
      1. Definiți o funcție moveArrowRight():
       - Începeți afișând săgeata pe prima poziție.
       - Folosiți un loop pentru a muta săgeata spre dreapta.
       - La fiecare pas, mutați biții săgeții spre dreapta (>> 1) și actualizați matricea.
       - Folosiți delay(200) între pași pentru a face mișcarea vizibilă.
*/

//Rezolvare
#include <LedControl.h> // Biblioteca pentru controlul modulului MAX7219

// Definim pinii conectați la modulul MAX7219
#define DATA_PIN 12  // Pinul digital conectat la DIN
#define CLK_PIN 11   // Pinul digital conectat la CLK
#define CS_PIN 10    // Pinul digital conectat la CS

// Inițializăm obiectul LedControl pentru controlul matricei
LedControl matrix = LedControl(DATA_PIN, CLK_PIN, CS_PIN, 1); // Avem doar o matrice

// Definim matricea pentru săgeată
// Fiecare linie reprezintă un rând din matrice, iar fiecare bit controlează un LED (1 = aprins, 0 = stins)
int arrowMatrix[8] = {
  B00001000, // Rând 0: partea de sus a săgeții
  B00001100, // Rând 1: corpul săgeții
  B11111110, // Rând 2: baza săgeții
  B11111111, // Rând 3: complet aprins
  B11111110, // Rând 4: baza săgeții
  B00001100, // Rând 5: corpul săgeții
  B00001000, // Rând 6: partea de jos a săgeții
  B00000000  // Rând 7: nimic
};

void setup() {
  // Pornim matricea și o configurăm
  matrix.shutdown(0, false);   // Pornim afișajul matricei 0
  matrix.setIntensity(0, 8);   // Setăm luminozitatea la nivel mediu (0-15)
  matrix.clearDisplay(0);      // Curățăm matricea înainte de a afișa ceva
}

void loop() {
  // Animăm săgeata care se deplasează spre dreapta
  moveArrowRight();

  // Pauză de 1 secundă înainte de repetarea animației
  delay(1000);
}

// Funcția pentru afișarea săgeții pe matrice
void displayArrow(int offset) {
  matrix.clearDisplay(0); // Curățăm afișajul

  // Mutăm săgeata spre dreapta cu "offset"
  for (int i = 0; i < 8; i++) {
    matrix.setRow(0, i, arrowMatrix[i] >> offset); // Mutăm biții spre dreapta
  }
}

// Funcția pentru mutarea săgeții spre dreapta
void moveArrowRight() {
  for (int offset = 0; offset < 8; offset++) { // Deplasăm săgeata spre dreapta
    displayArrow(offset); // Afișăm săgeata cu noul offset
    delay(200);           // Pauză între pașii animației
  }
}

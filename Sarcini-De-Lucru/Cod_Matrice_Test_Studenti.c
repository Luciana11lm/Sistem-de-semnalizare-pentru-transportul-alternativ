#include <LedControl.h> // Biblioteca care ajută la controlul modulului MAX7219

// Definim pinii Arduino conectați la modulul MAX7219
#define DATA_PIN 12  // Pinul digital conectat la pinul DIN al modulului
#define CLK_PIN 11   // Pinul digital conectat la pinul CLK al modulului
#define CS_PIN 10    // Pinul digital conectat la pinul CS al modulului

// Creăm un obiect LedControl pentru a controla matricea LED
// Parametrii:
// - DATA_PIN: pin pentru date
// - CLK_PIN: pin pentru ceas (clock)
// - CS_PIN: pin pentru selectarea modulului
// - 1: numărul de matrice LED conectate (în acest caz, doar una)
LedControl matrix = LedControl(DATA_PIN, CLK_PIN, CS_PIN, 1);

void setup() {
  // Pornim matricea LED. Funcția "shutdown()" controlează dacă afișajul este pornit sau oprit.
  // shutdown(0, false): pornim matricea cu indexul 0 (prima matrice).
  matrix.shutdown(0, false);

  // Setăm luminozitatea matricei LED.
  // setIntensity(0, 8): setăm luminozitatea matricei 0 (prima matrice) la nivelul 8 (intervalul este 0-15).
  matrix.setIntensity(0, 8);

  // Ștergem toate LED-urile de pe matrice pentru a începe cu un afișaj curat.
  // clearDisplay(0): ștergem afișajul matricei 0 (prima matrice).
  matrix.clearDisplay(0);
}

void loop() {
  // Acest loop va aprinde un singur LED, care se va mișca de-a lungul matricei
  // LED-ul va parcurge toate rândurile (de sus în jos) și coloanele (de la stânga la dreapta)

  // Iterăm prin fiecare rând al matricei
  for (int row = 0; row < 8; row++) { // rândurile sunt numerotate de la 0 la 7
    // Iterăm prin fiecare coloană a rândului curent
    for (int col = 0; col < 8; col++) { // coloanele sunt numerotate de la 0 la 7
      // Ștergem matricea înainte de a aprinde un nou LED.
      // Acest pas asigură că doar un singur LED este aprins la un moment dat.
      matrix.clearDisplay(0);

      // Aprindem LED-ul de la poziția (row, col).
      // setLed(0, row, col, true):
      // - 0: indică matricea pe care vrem să lucrăm (în cazul nostru, prima matrice).
      // - row: rândul unde se află LED-ul.
      // - col: coloana unde se află LED-ul.
      // - true: aprinde LED-ul (dacă am pune "false", l-ar stinge).
      matrix.setLed(0, row, col, true);

      // Pauză de 200 milisecunde pentru ca mișcarea LED-ului să fie vizibilă.
      delay(200);
    }
  }
}


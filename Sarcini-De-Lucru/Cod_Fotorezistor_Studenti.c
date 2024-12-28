// Definim pinul analogic la care este conectat fotorezistorul
#define PHOTORESISTOR_PIN A0

// Declarăm o variabilă pentru a stoca valoarea citită de la fotorezistor
int lightValue = 0;

void setup() {
  // Configurăm comunicația serială pentru a putea vedea datele pe monitorul serial
  // 9600 este viteza de transmisie a datelor (baud rate)
  Serial.begin(9600);
}

void loop() {
  // Citim valoarea analogică de la fotorezistor (între 0 și 1023)
  lightValue = analogRead(PHOTORESISTOR_PIN);

  // Convertim valoarea într-un procentaj (între 0% și 100%) pentru a o înțelege mai ușor
  int lightPercentage = map(lightValue, 0, 1023, 0, 100);

  // Afișăm pe monitorul serial valoarea brută și valoarea procentuală a luminozității
  Serial.print("Luminozitate (valoare bruta): ");
  Serial.print(lightValue);                       // Afișează valoarea brută
  Serial.print("   Luminozitate (%): ");
  Serial.println(lightPercentage);                // Afișează valoarea în procente

  // Adăugăm o pauză de 500 milisecunde pentru a evita afișarea continuă
  delay(500);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Scopul exercițiului:
Creați un proiect care ajustează luminozitatea unei matrice LED bazată pe valoarea luminozității ambientale
citite de un fotorezistor. Scopul este să înțelegeți cum să folosiți funcții, condiții, și citiri analogice în Arduino.
Pași pentru realizarea proiectului:
  1. Conectarea componentelor hardware:
    a) Conectați fotorezistorul la un pin analogic al Arduino (ex: A0).
    b) Conectați o matrice LED (de exemplu, modulul cu MAX7219) sau un semafor de LED-uri la Arduino.
    c) Asigurați-vă că fotorezistorul este conectat corect (cu un rezistor în divizorul de tensiune daca rezistorul are 2 pini,
      daca folositi un modul nu o sa aveti nevoie).

  2. Scrieți funcția adjustMatrixIntensity:
    a) Citiți valoarea de la fotorezistor folosind analogRead().
    b) Convertiți valoarea citită într-un procentaj folosind funcția map().
    c) Ajustați intensitatea matricei LED:
      - Dacă procentajul este sub 50%, setați intensitatea matricei la un nivel mai mare (mai luminoasă).
      - Dacă procentajul este peste 50%, reduceți intensitatea matricei.

  Indicatii: folositi biblioteca <LedControl.h> in cazul in care lucrati cu modulul MAX7219 (matrice LED).

  Rezolvare:
// Biblioteca pentru controlul matricei LED
#include <LedControl.h>

// Definim pinii pentru matricea LED
#define DATA_PIN 12
#define CLK_PIN 11
#define CS_PIN 10

// Inițializăm obiectul pentru controlul matricei LED
LedControl matrix = LedControl(DATA_PIN, CLK_PIN, CS_PIN, 1); 

// Definim pinul pentru fotorezistor
#define PHOTORESISTOR_PIN A0

// Variabile pentru valori de lumină
int lightValue = 0;
int lightPercentage = 0;

void setup() {
  // Configurăm matricea LED
  matrix.shutdown(0, false);  // Pornim matricea
  matrix.setIntensity(0, 8); // Setăm o intensitate inițială medie
  matrix.clearDisplay(0);    // Ștergem display-ul

  // Pornim comunicația serială
  Serial.begin(9600);
}

void loop() {
  adjustMatrixIntensity(); // Apelăm funcția care ajustează intensitatea matricei
  delay(500); // Pauză pentru stabilitate
}

void adjustMatrixIntensity() {
  // Citim valoarea de la fotorezistor
  lightValue = analogRead(PHOTORESISTOR_PIN);
  lightPercentage = map(lightValue, 0, 1023, 0, 100);

  // Ajustăm intensitatea matricei în funcție de luminozitate
  if (lightPercentage < 50) {
    matrix.setIntensity(0, 15); // Intensitate maximă
  } else {
    matrix.setIntensity(0, 5);  // Intensitate scăzută
  }

  // Afișăm valoarea pe monitorul serial
  Serial.print("Luminozitate (%): ");
  Serial.println(lightPercentage);
}

*/
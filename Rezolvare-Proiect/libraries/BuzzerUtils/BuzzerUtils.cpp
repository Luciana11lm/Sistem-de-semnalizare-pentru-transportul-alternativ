#include "BuzzerUtils.h"
#include <Arduino.h>

void setup_timer(){
  DDRB |= 1<<1; // declar PB1 ca iesire
  TCCR1A = 1 << 6;  // OC1A isi va schimba valoarea cand timer-ul ajunge la valoarea registrului OCR1A
  TCCR1B = 1 << 3;  // se activeaza modul CTC
  TCCR1B |= 1 << 0; // se porneste timer-ul cu prescaler = 1
  OCR1A = 22000;    // o iteratie de numarare va dura 1,66 ms
}

void buzzerSound(int signalLevel) {
  int beepDuration = 0;  // Durata beep-ului
  int pauseDuration = 0; // Durata pauzei

  if (signalLevel == 3) {
    beepDuration = 2000;  // Sunet rapid
    pauseDuration = 0;    // Pauză scurtă
    OCR1A = 26000;        // Frecvență specifică
  } else if (signalLevel == 2) {
    beepDuration = 200;   // Sunet rapid
    pauseDuration = 100;  // Pauză scurtă
    OCR1A = 22000;        // Frecvență specifică
  } else if (signalLevel == 1) {
    beepDuration = 300;   // Sunet mai lent
    pauseDuration = 1000; // Pauză mai lungă
    OCR1A = 18000;        // Frecvență specifică
  }

  // Generăm beep-uri în funcție de durată și pauză
  TCCR1B |= 1 << 0;       // Pornire timer
  delay(beepDuration);    // Durata beep-ului
  TCCR1B &= ~(1 << 0);    // Oprire timer
  delay(pauseDuration);   // Pauză între beep-uri
}

void generateBellSound() {
  // Generăm sunet de sonerie specific
  int frequencies[] = {2000, 2500, 3000}; // Frecvențe pentru sunet
  for (int i = 0; i < 3; i++) {
    OCR1A = frequencies[i];
    TCCR1B |= 1 << 0;  // Pornire timer
    delay(200);        // Fiecare ton durează 200 ms
    TCCR1B &= ~(1 << 0); // Oprire timer
    delay(50);         // Pauză scurtă între tonuri
  }
}
#include <Adafruit_GFX.h>           // Biblioteca pentru funcții grafice (desenare pe display-uri OLED/LCD).
#include <Adafruit_SSD1306.h>       // Biblioteca pentru controlul display-ului OLED SSD1306.
#include <NewPing.h>                // Biblioteca pentru controlul senzorului ultrasonic.
#include <math.h>                   // Biblioteca matematică pentru funcții precum putere, rădăcină pătrată etc.
#include <LedControl.h>             // Biblioteca pentru controlul matricei LED cu MAX7219.
#include <Wire.h>                   // Biblioteca pentru comunicația I2C cu dispozitive conectate.

// Biblioteci personalizate
#include "BuzzerUtils.h"            // Funcții personalizate pentru controlul buzzerului.
#include "OLEDUtils.h"              // Funcții personalizate pentru utilizarea display-ului OLED.
#include "MatrixUtils.h"            // Funcții personalizate pentru controlul matricei LED.

// Dimensiuni ecran OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Obiect pentru OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);   // Inițializează display-ul cu dimensiunile și conexiunea I2C.

// Pini pentru senzorul ultrasonic
#define TRIG_PIN 2                  // Pin digital pentru semnalul de ieșire (TRIG) al senzorului.
#define ECHO_PIN 3                  // Pin digital pentru semnalul de intrare (ECHO) al senzorului.
#define MAX_DISTANCE 100            // Distanța maximă de detecție (în cm).

// Obiect pentru senzorul ultrasonic
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);                   // Inițializează senzorul ultrasonic cu pinii și distanța maximă.

// Gama pentru semnale
#define CLOSE_DISTANCE  10          // Prag pentru distanță apropiată.
#define MEDIUM_DISTANCE 50          // Prag pentru distanță medie.
#define FAR_DISTANCE    80          // Prag pentru distanță mare.

// Joystick
#define JOY_X_PIN A3                // Pin analogic pentru axa X a joystick-ului.
const int threshold = 300;          // Prag pentru detectarea mișcării joystick-ului.
int xValue = 0;                     // Variabilă pentru valoarea citită de la axa X.

bool isJoystickCentered = true;     // Indică dacă joystick-ul este centrat.
bool isCircleDisplayed = false;     // Indică dacă cercul este afișat pe matrice.
 
// Pini pentru MAX7219
int DIN = 10;
int CS = 11;
int CLK = 12;
LedControl matrix = LedControl(DIN, CLK, CS, 1); // Din, CLK, LOAD/CS, nr. de matrice

// Pin pentru sonerie
#define SWITCH_PIN 7

// Fotorezistor
#define PHOTORESISTOR_PIN A0        // Pin analogic pentru citirea luminozității de la fotorezistor.
int lightValue = 0;                 // Variabilă pentru valoarea brută citită de la fotorezistor.
int lightPercentage = 0;            // Variabilă pentru luminozitatea calculată în procente.

// Sageti pe matrice
int arrowLeft[8] = {
    B00011100, B00011100, B00011100, B11111111, 
    B01111111, B00111110, B00011100, B00001000
};

int arrowRight[8] = {
    B00001000, B00011100, B00111110, B01111111, 
    B11111111, B00011100, B00011100, B00011100
};

// Cercul pe matrice pentru distanța 0
int circleMatrix[8] = {
    B00111100, B01111110, B11111111, B11111111,
    B11111111, B11111111, B01111110, B00111100
};


// Funcția de ajustare a intensității matricei
void adjustMatrixIntensity() {
    lightValue = analogRead(PHOTORESISTOR_PIN);                 // Citește luminozitatea ambientală.
    lightPercentage = map(lightValue, 0, 1023, 0, 100);         // Normalizează valoarea în procente.

    if (lightPercentage < 50) {
        matrix.setIntensity(0, 15);                             // Intensitate maximă
    } else {
        matrix.setIntensity(0, 1);                              // Intensitate scăzută
    }
}

// Configurare inițială
void setup() {
    Serial.begin(9600);
    setup_timer();                                              // Inițializează timerul pentru buzzer (din biblioteca personalizată).

    pinMode(SWITCH_PIN, INPUT_PULLUP);                          // Configurează butonul soneriei cu rezistență internă pull-up.

    initializeOLED(display);                                    // Inițializează OLED-ul.
    initializeMatrix(matrix);                                   // Inițializează matricea LED.

    display.clearDisplay();                                     // Șterge conținutul OLED-ului.
    display.display();                                          // Actualizează OLED-ul.
    //delay(200);
}

// Bucla principală
void loop() {
    // 1. Citire date
    unsigned int distance = sonar.ping_cm();                    // Citește distanța în cm de la senzorul ultrasonic.
    distance = (distance == 0) ? MAX_DISTANCE : distance;       // Dacă nu se detectează nimic, setează la distanța maximă.

    xValue = analogRead(JOY_X_PIN);                             // Citește poziția axei X a joystick-ului.
    bool shouldDisplayCircle = (distance < 10);                 // Verifică dacă trebuie afișat cercul pe matrice.

    // 2. Switch pentru sonerie
    if (digitalRead(SWITCH_PIN) == LOW) {                       // Verifică dacă butonul soneriei este apăsat.
        generateBellSound();
        delay(500);
        return;
    }

    // 3. Logica joystick-ului
    if (xValue < threshold) {                                   // Joystick mutat spre stânga.
        handleLeftMovement();
        isJoystickCentered = false;
    } else if (xValue > 1023 - threshold) {                     // Joystick mutat spre dreapta.
        handleRightMovement();
        isJoystickCentered = false;
    } else if (!isJoystickCentered) {                           // Joystick centrat (după mișcare).
        clearMatrix();
        isJoystickCentered = true;
    }

    // 4. Gestionare cerc
    if (shouldDisplayCircle != isCircleDisplayed) {
        if (shouldDisplayCircle) {
            displayCircle();
        } else {
            clearMatrix();
        }
        isCircleDisplayed = shouldDisplayCircle;
    }

    // 5. Semnale bazate pe distanță
    int signalLevel = 0;                                        // Nivelul semnalului bazat pe distanță.
    if (distance > 0 && distance <= CLOSE_DISTANCE) {
        signalLevel = 3;                                        // Distanță apropiată.
    } else if (distance <= MEDIUM_DISTANCE) {
        signalLevel = 2;                                        // Distanță medie.
    } else if (distance <= FAR_DISTANCE) {
        signalLevel = 1;                                        // Distanță mare.
    }

    // 6. Output
    adjustMatrixIntensity();                                    // Ajustează intensitatea matricei în funcție de luminozitate.
    drawSignal(signalLevel, distance, display);                 // Afișează semnalul pe OLED.

    // 7. Sunete pentru buzzer
    buzzerSound(signalLevel);                                   // Emite sunet în funcție de nivelul semnalului.

    // Debugging
    Serial.print("Distanță: ");
    Serial.println(distance == MAX_DISTANCE ? "MAX" : String(distance) + " cm");

    delay(10);
}

// Funcții auxiliare
void handleLeftMovement() {
    blinkArrow(arrowLeft, matrix);                              // Afișează săgeata spre stânga.
}

void handleRightMovement() {
    blinkArrow(arrowRight, matrix);                             // Afișează săgeata spre dreapta.
}

void displayCircle() {
    displayCircle(circleMatrix, matrix);                        // Afișează cercul pe matrice.
}

void clearMatrix() {
    clearMatrix(matrix);                                        // Șterge matricea LED.
}










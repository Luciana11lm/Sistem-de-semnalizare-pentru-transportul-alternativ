/*
Cerinte pentru studenti:
Scopul acestui set de exerciții este să învățați cum să utilizați buclele și matricile pentru a controla afișajul în funcție de mișcarea joystick-ului.

Exercițiul 1: Afișare text pe un display OLED
Scop: Acest set de exerciții are ca scop familiarizarea cu funcțiile de bază ale unui afișaj OLED, utilizând biblioteca Adafruit_SSD1306 pentru a crea afișări text și grafice simple.

Cerințe:
  1. Afișați un mesaj static pe display-ul OLED.
  2. Utilizați funcțiile setCursor, setTextSize, setTextColor, și display pentru a afișa două linii de text.
  3. Mesajul trebuie să fie:
      Hello,
      World!
*/

#include <Adafruit_GFX.h>       // Biblioteca Adafruit_GFX oferă funcții grafice generale pentru desene (linii, cercuri, text) pe ecrane. 
#include <Adafruit_SSD1306.h>   // Biblioteca specifică pentru controlul display-urilor OLED bazate pe controlerul SSD1306. Biblioteca specifică pentru controlul display-urilor OLED bazate pe controlerul SSD1306.
#include <Wire.h>               // Biblioteca Wire este utilizată pentru comunicația I2C, care permite controlul display-ului OLED conectat la Arduino.

// Dimensiuni ecran OLED
#define SCREEN_WIDTH 128        // Definește lățimea display-ului OLED în pixeli. (latimea maxima)
#define SCREEN_HEIGHT 64        // Definește înălțimea display-ului OLED în pixeli. (inaltimea maxima)

// Obiect pentru OLED
// Creează un obiect display de tip Adafruit_SSD1306.
// Parametrii:
// - SCREEN_WIDTH și SCREEN_HEIGHT: Specifică dimensiunile display-ului.
// - &Wire: Specifică utilizarea comunicației I2C.
// - -1: Indică că nu este utilizat un pin pentru reset (opțional).
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  // Parametrii: - SSD1306_SWITCHCAPVCC: Indică utilizarea sursei de tensiune internă pentru OLED.
  //             - 0x3C: Adresa I2C a display-ului OLED (specifică pentru majoritatea SSD1306).
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {       
    Serial.println(F("Eroare la inițializarea OLED!"));
    for (;;);
  }

  display.clearDisplay();             // Șterge orice conținut afișat anterior pe display.
  display.setTextSize(2);             // Setăm dimensiunea textului
  display.setTextColor(SSD1306_WHITE);// Setăm culoarea textului
  display.setCursor(10, 20);          // Setăm poziția textului
  display.print("Hello,");            // Afișăm prima linie
  display.setCursor(10, 40);
  display.print("World!");            // Afișăm a doua linie
  display.display();                  // Actualizăm ecranul
}

void loop() {
  // Nu facem nimic în loop
}



/*
Exercițiul 2: Exercițiul 2: Completarea funcționalității OLED
Scop: Completați spațiile libere în codul de mai jos pentru a realiza o aplicație care afișează un simbol pe baza unui semnal numeric.
*/

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// Dimensiuni ecran OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Eroare la inițializarea OLED!"));
    for (;;);
  }

  // ________________ Completați codul pentru a curăța display-ul ________________

}

void loop() {
  int signalLevel = 2; // Puteți modifica între 1, 2, 3 pentru testare

  display.clearDisplay();
  display.fillCircle(64, 48, 4, SSD1306_WHITE); // Baza simbolului

  // ________________ Completați codul pentru a desena arcele pe baza lui signalLevel ________________

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 56);
  display.print("Signal: ");
  display.print(signalLevel);

  display.display(); // Actualizăm ecranul

  delay(1000);
}

/*Sugestii pentru completare:

În funcția setup(), adăugați liniile pentru a curăța ecranul și a-l inițializa corespunzător.
În funcția loop(), completați logica pentru a desena arcele pe baza nivelului de semnal (signalLevel).


Rezolvare:

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// Dimensiuni ecran OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Eroare la inițializarea OLED!"));
    for (;;);
  }

  // Curățăm display-ul
  display.clearDisplay();
  display.display();
}

void loop() {
  int signalLevel = 2; // Puteți modifica între 1, 2, 3 pentru testare

  display.clearDisplay();
  display.fillCircle(64, 48, 4, SSD1306_WHITE); // Baza simbolului

  // Desenăm arcele pe baza lui signalLevel
  if (signalLevel >= 1) {
    display.drawArc(64, 48, 12, 0, 180, SSD1306_WHITE); // Primul arc
  }
  if (signalLevel >= 2) {
    display.drawArc(64, 48, 20, 0, 180, SSD1306_WHITE); // Al doilea arc
  }
  if (signalLevel >= 3) {
    display.drawArc(64, 48, 28, 0, 180, SSD1306_WHITE); // Al treilea arc
  }

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 56);
  display.print("Signal: ");
  display.print(signalLevel);

  display.display(); // Actualizăm ecranul

  delay(1000);
}

*/








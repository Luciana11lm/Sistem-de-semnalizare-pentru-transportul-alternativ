/*
Cerinte pentru studenti:
De a învața principiile de funcționare ale senzorului (emiterea și recepționarea impulsurilor sonore pentru măsurarea distanței).
Utilizarea funcțiilor digitalWrite, pulseIn, și calcularea distanței pe baza timpului de răspuns.

Exercițiul 1: Introducere în utilizarea senzorului ultrasonic HC-SR04
Scop: De a învața principiile de funcționare ale senzorului (emiterea și recepționarea impulsurilor sonore pentru măsurarea distanței).

Cerințe:
  1. Conectați pinii TRIG și ECHO ai senzorului HC-SR04 la pinii digitali 2 și 3 ai plăcii Arduino.
  2. Scrieți un cod pentru a calcula și afișa distanța măsurată.
*/

#define TRIG_PIN 2  // TRIG_PIN (Pinul 2) este utilizat pentru a genera un semnal ultrasonic.
#define ECHO_PIN 3  // ECHO_PIN (Pinul 3) este utilizat pentru a primi semnalul ultrasonic reflectat.

void setup() {
  Serial.begin(9600);         // Inițializare Serial Monitor
  pinMode(TRIG_PIN, OUTPUT);  // Configurează pinul TRIG ca ieșire digitală, astfel încât Arduino să poată genera impulsuri către senzor.
  pinMode(ECHO_PIN, INPUT);   // Configurează pinul ECHO ca intrare digitală, astfel încât Arduino să poată citi impulsurile reflectate.
}

void loop() {
  // Trimite un impuls de 10µs pe pinul TRIG
  digitalWrite(TRIG_PIN, LOW);  // Asigură că pinul TRIG este setat la LOW pentru a reseta senzorul înainte de a trimite un nou semnal.
  delayMicroseconds(2);         // Creează o pauză scurtă de 2 microsecunde înainte de a genera impulsul.
  digitalWrite(TRIG_PIN, HIGH); // Activează senzorul, trimițând un impuls ultrasonic prin setarea pinului TRIG la HIGH.
  delayMicroseconds(10);        // Durata impulsului emis este de 10 microsecunde.
  digitalWrite(TRIG_PIN, LOW);  // Oprește semnalul ultrasonic, setând pinul TRIG înapoi la LOW.

  // Măsoară durata impulsului returnat
  long duration = pulseIn(ECHO_PIN, HIGH);  // Măsoară timpul (în microsecunde) cât pinul ECHO rămâne HIGH

  // Calculează distanța (durata * viteză sunet / 2)
  // duration: Timpul măsurat (în microsecunde).
  // 0.034: Viteza sunetului în aer (340 m/s sau 0.034 cm/µs).
  // Împărțim la 2 deoarece semnalul ultrasonic parcurge distanța dus-întors.
  float distance = duration * 0.034 / 2;    

  // Afișează distanța în cm
  Serial.print("Distanta: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}

/*
Exercițiul 2: Completare cod pentru afisarea pe OLED a distantei masurate
Scop: Studenții vor completa părțile lipsă dintr-un cod predefinit pentru a afișa distanța măsurată de senzorul ultrasonic pe un ecran OLED.

Cerințe:
  1. Completați codul lipsă pentru afișarea distanței în centimetri pe ecranul OLED.
  2. Rulați codul pe Arduino și verificați afișarea distanței pe OLED.

Sugestii: 
  1. Utilizați funcțiile pinMode, digitalWrite, pulseIn, display.setCursor(), și display.display() în locurile corespunzătoare.
  2. Dacă întâmpinați dificultăți, consultați documentația pentru senzorul HC-SR04 și biblioteca SSD1306.
*/

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define TRIG_PIN 2
#define ECHO_PIN 3

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  // Configurare pinii senzorului ultrasonic
  _____________;  // <- Completați cu configurarea pinului TRIG ca OUTPUT
  _____________;  // <- Completați cu configurarea pinului ECHO ca INPUT

  // Inițializare OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Eroare la initializarea OLED!"));
    for (;;); // Blochează programul
  }

  // Curățăm ecranul OLED
  _____________;  // <- Completați pentru a curăța display-ul
}

void loop() {
  // Trimite un impuls pe pinul TRIG
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  _____________;  // <- Completați pentru a trimite un impuls HIGH de 10 microsecunde
  digitalWrite(TRIG_PIN, LOW);

  // Măsoară durata impulsului returnat
  _____________;  // <- Completați codul pentru a citi impulsul de pe pinul ECHO

  // Calculează distanța (durata * viteză sunet / 2)
  float distance = _____________;  // <- Completați formula de calcul pentru distanță

  // Afișare pe OLED
  display.clearDisplay();

  // Configurare text
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  _____________;  // <- Completați pentru a seta poziția cursorului

  // Afisare distanta pe ecran
  display.print("Dist: ");
  display.print(_____________);  // <- Completați pentru a afișa valoarea distanței
  display.println(" cm");

  // Actualizare ecran OLED
  _____________;  // <- Completați pentru a actualiza ecranul OLED

  delay(500);
}

/*
Rezolvare:

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define TRIG_PIN 2
#define ECHO_PIN 3

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  // Configurare pinii senzorului ultrasonic
  pinMode(TRIG_PIN, OUTPUT);  // <- Configurarea pinului TRIG ca OUTPUT
  pinMode(ECHO_PIN, INPUT);   // <- Configurarea pinului ECHO ca INPUT

  // Inițializare OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Eroare la initializarea OLED!"));
    for (;;); // Blochează programul
  }

  // Curățăm ecranul OLED
  display.clearDisplay();  // <- Curățăm display-ul
}

void loop() {
  // Trimite un impuls pe pinul TRIG
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); // <- Trimite un impuls HIGH de 10 microsecunde
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Măsoară durata impulsului returnat
  long duration = pulseIn(ECHO_PIN, HIGH);  // <- Citește impulsul de pe pinul ECHO

  // Calculează distanța (durata * viteză sunet / 2)
  float distance = duration * 0.034 / 2;  // <- Formula pentru calculul distanței

  // Afișare pe OLED
  display.clearDisplay();

  // Configurare text
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);  // <- Setează poziția cursorului

  // Afisare distanta pe ecran
  display.print("Dist: ");
  display.print(distance);  // <- Afișează valoarea distanței
  display.println(" cm");

  // Actualizare ecran OLED
  display.display();  // <- Actualizează ecranul OLED

  delay(500);
}
*/






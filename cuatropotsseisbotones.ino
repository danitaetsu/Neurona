#include <BLEMIDI_Transport.h>
#include <hardware/BLEMIDI_ESP32.h>

BLEMIDI_CREATE_INSTANCE("NEURONA", MIDI);

// ---- BOTONES ----
const int buttonPin1 = 26;
const int buttonPin2 = 27;
const int buttonPin3 = 25;
const int buttonPin4 = 14;
const int buttonPin5 = 12;
const int buttonPin6 = 13;  // nuevo botón

// ---- POTES ----
const int potPin1 = 36;
const int potPin2 = 35;
const int potPin3 = 34;
const int potPin4 = 32;

int exCC1 = 0;
int exCC2 = 0;
int exCC3 = 0;
int exCC4 = 0;

void setup() {
  Serial.begin(115200);
  MIDI.begin(1);

  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);

  Serial.println("✅ BLE MIDI listo: 4 potes + 6 botones (26,27,25,14,12,13)");
}

void loop() {

  // --------- BOTÓN 1 ----------
  if (digitalRead(buttonPin1) == LOW) {
    MIDI.sendNoteOn(60, 127, 1);
    Serial.println("🎹 Botón 1 (pin 26) → NoteOn 60");
    delay(200);
  }

  // --------- BOTÓN 2 ----------
  if (digitalRead(buttonPin2) == LOW) {
    MIDI.sendNoteOn(61, 127, 1);
    Serial.println("🎹 Botón 2 (pin 27) → NoteOn 61");
    delay(200);
  }

  // --------- BOTÓN 3 ----------
  if (digitalRead(buttonPin3) == LOW) {
    MIDI.sendNoteOn(62, 127, 1);
    Serial.println("🎹 Botón 3 (pin 25) → NoteOn 62");
    delay(200);
  }

  // --------- BOTÓN 4 ----------
  if (digitalRead(buttonPin4) == LOW) {
    MIDI.sendNoteOn(63, 127, 1);
    Serial.println("🎹 Botón 4 (pin 14) → NoteOn 63");
    delay(200);
  }

  // --------- BOTÓN 5 ----------
  if (digitalRead(buttonPin5) == LOW) {
    MIDI.sendNoteOn(64, 127, 1);
    Serial.println("🎹 Botón 5 (pin 12) → NoteOn 64");
    delay(200);
  }

  // --------- BOTÓN 6 ----------
  if (digitalRead(buttonPin6) == LOW) {
    MIDI.sendNoteOn(65, 127, 1);
    Serial.println("🎹 Botón 6 (pin 13) → NoteOn 65");
    delay(200);
  }

  // --------- POT 1 ----------
  leerPot(potPin1, exCC1, 2);
  delay(5);

  // --------- POT 2 ----------
  leerPot(potPin2, exCC2, 3);
  delay(5);

  // --------- POT 3 ----------
  leerPot(potPin3, exCC3, 4);
  delay(5);

  // --------- POT 4 ----------
  leerPot(potPin4, exCC4, 5);
  delay(5);
}

// ---- FUNCIÓN POTES ----
void leerPot(int pin, int &lastCC, int cc) {
  int total = 0;
  for (int i = 0; i < 8; i++) {
    total += analogRead(pin);
    delay(3);
  }

  int val = total / 8;
  int ccVal = map(val, 0, 4095, 0, 127);

  if (abs(ccVal - lastCC) > 1) {
    MIDI.sendControlChange(cc, ccVal, 1);
    lastCC = ccVal;
    Serial.printf("Pot %d -> CC %d = %d (raw=%d)\n", pin, cc, ccVal, val);
  }
}

#include <Arduino.h>

// Mike Maesen 1245

int hoofdRood = 2;
int hoofdOranje = 3;
int hoofdGroen = 4;
int zijRood = 5;
int zijOranje = 6;
int zijGroen = 7;
int busKnop = 8;
int stap = 0;

unsigned long groenTijd = 8000;
unsigned long oranjeTijd = 2000;
unsigned long veiligTijd = 500;
unsigned long vorigeTijd = 0;

bool busVraag = false;
bool vorigeKnopStatus = HIGH;

void allLightsOff() {
  digitalWrite(hoofdRood, 0);
  digitalWrite(hoofdOranje, 0);
  digitalWrite(hoofdGroen, 0);
  digitalWrite(zijRood, 0);
  digitalWrite(zijOranje, 0);
  digitalWrite(zijGroen, 0);
}

void setup() {

  Serial.begin(9600);

  pinMode(hoofdRood, OUTPUT);
  pinMode(hoofdOranje, OUTPUT);
  pinMode(hoofdGroen, OUTPUT);
  pinMode(zijRood, OUTPUT);
  pinMode(zijOranje, OUTPUT);
  pinMode(zijGroen, OUTPUT);
  pinMode(busKnop, INPUT_PULLUP);

  vorigeTijd = millis();
}

void loop() {

  unsigned long huidigeTijd = millis();

  bool knopStatus = digitalRead(busKnop);

  if (knopStatus == LOW && vorigeKnopStatus == HIGH) {

    Serial.println("Bus knop ingedrukt!");

    if (stap == 0 || stap == 1) {
      busVraag = true;
      Serial.println("Bus vraagt voorrang!");
    }
    else {
      Serial.println("Bus kan nu geen voorrang krijgen.");
    }
  }

  vorigeKnopStatus = knopStatus;

  // STAP 0
  if (stap == 0) {

    allLightsOff();
    digitalWrite(hoofdRood, HIGH);
    digitalWrite(zijGroen, HIGH);

    if (huidigeTijd - vorigeTijd >= groenTijd || busVraag) {
      stap = 1;
      vorigeTijd = huidigeTijd;
      Serial.println("Stap 0");
    }
  }

  // STAP 1 
  else if (stap == 1) {

    allLightsOff();
    digitalWrite(hoofdRood, HIGH);
    digitalWrite(zijOranje, HIGH);

    if (huidigeTijd - vorigeTijd >= oranjeTijd) {
      stap = 2;
      vorigeTijd = huidigeTijd;
      Serial.println("Stap 1");
    }
  }

  // STAP 2
  else if (stap == 2) {

    allLightsOff();
    digitalWrite(hoofdRood, HIGH);
    digitalWrite(zijRood, HIGH);

    if (huidigeTijd - vorigeTijd >= veiligTijd) {
      stap = 3;
      vorigeTijd = huidigeTijd;
      busVraag = false;
      Serial.println("Stap 2");
    }
  }

  // STAP 3 
  else if (stap == 3) {

    allLightsOff();
    digitalWrite(hoofdGroen, HIGH);
    digitalWrite(zijRood, HIGH);

    if (huidigeTijd - vorigeTijd >= groenTijd) {
      stap = 4;
      vorigeTijd = huidigeTijd;
      Serial.println("Stap 3");
    }
  }

  // STAP 4 
  else if (stap == 4) {

    allLightsOff();
    digitalWrite(hoofdOranje, HIGH);
    digitalWrite(zijRood, HIGH);

    if (huidigeTijd - vorigeTijd >= oranjeTijd) {
      stap = 0;
      vorigeTijd = huidigeTijd;
      Serial.println("Stap 4");
    }
  }
}

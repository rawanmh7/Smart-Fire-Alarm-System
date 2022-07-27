#include <TimerOne.h>
#include <EEPROM.h>


int buttonPin = 2;
int buzzerPin = 3;
int ledRed = 4;
int tempPin = A0;
int flamePin = 6;
int ledYellow = 5;

bool toneChange = false;
bool Flame_detected = false;

void setup()
{
  Serial.begin(9600);
  //EEPROM.write(0, 1); //to write first time to eeprom

  Serial.print(EEPROM.read(0));

  pinMode(buzzerPin, OUTPUT);

  pinMode(flamePin, INPUT_PULLUP);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  Timer1.initialize(1000000);
  Timer1.attachInterrupt(changeTone);

  attachInterrupt(digitalPinToInterrupt(buttonPin), turnOff, FALLING ); // trigger when button pressed, but not when released.

}
void loop()
{
  float voltage, degreesC;
  voltage = getVoltage(tempPin);
  degreesC = (voltage - 0.5) * 100.0;
  //Serial.println(degreesC);

  if (Flame_detected == false && (digitalRead(flamePin) == 0 || degreesC > 30)) {
    int val = EEPROM.read(0);
    val++;
    Serial.print(val);
    EEPROM.write(0, val);
    Flame_detected = true;
  }

  if (Flame_detected) {
    if (toneChange) {
      tone(buzzerPin, 1000);
      digitalWrite(ledYellow, HIGH);
      digitalWrite(ledRed, LOW);
    } else {
      tone(buzzerPin, 500);
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledRed, HIGH);
    }

  } else {
    noTone(buzzerPin);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, LOW);
  }

  delay(100);

}

float getVoltage(int pin) {
  return (analogRead(pin) * 0.004882814);
}

void changeTone() {
  toneChange = !toneChange;
}

void turnOff() {
  Flame_detected = false;
}

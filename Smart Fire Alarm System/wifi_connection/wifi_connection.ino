#define BLYNK_TEMPLATE_ID "TMPLtss9Oeof"
#define BLYNK_DEVICE_NAME "Fire Alarm"
#define BLYNK_AUTH_TOKEN "-cmNA1tlnuX1xIOEb385kWn0q8nuAWn3"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "network";
char pass[] = "123456789";

BlynkTimer timer;

String prvData;
String data = "-1";

void sendCount()
{
  if (Serial.available()) {
    data = Serial.readString();
  }
  if (prvData != data) {
    Serial.println("in the if statment");
    Blynk.logEvent("fire_warning", "Alert : Fire detected...! take action immediately.");
    prvData = data;
  }
  Blynk.virtualWrite(V0, data);

}

void setup()
{
  Serial.begin(9600);
  delay(1000);
  if (Serial.available()) {
    prvData = Serial.readString();
  }
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080);
  timer.setInterval(1000L, sendCount);

}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}

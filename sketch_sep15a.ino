#define BLYNK_PRINT Serial 

#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>

char auth[] = "Z4Cr2W1zdCWRdGMz9sqUoQqD2JDOfQTf";
char ssid[] = "wifi";
char pass[] = "nurcahyo";

#define pinInput D7
unsigned long pwmPulse = 0;
unsigned long intCh3Rise = 0;
unsigned long PulseLength = 0;

BlynkTimer timer;

void sendSensor(){
  if(isnan(PulseLength)){
    Serial.println("Gagal Recv");
    return;
  }
  Serial.println(PulseLength);
  Blynk.virtualWrite(V5, PulseLength);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pinInput, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinInput), pinChange, CHANGE);
  
  Serial.println("Test");
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);

}

void loop() {
  // put your main code here, to run repeatedly:
 Blynk.run();
 timer.run();

}

ICACHE_RAM_ATTR void pinChange() {
  
  if (digitalRead(pinInput) == HIGH) {
    intCh3Rise = micros();
  }
  else {
    unsigned long testvar = micros() - intCh3Rise;
    if (testvar >= 1000 && testvar <= 2000) {
      PulseLength = testvar;
    }
  }
}

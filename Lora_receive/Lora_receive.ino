#include <SoftwareSerial.h>
#include "EBYTE.h"

int Chan;
struct DATA {
  float Temp;
  float Humi;
};

DATA MyData;
SoftwareSerial ESerial(2, 3);
// M0, M1, and Aux 
EBYTE Transceiver(&ESerial, 4, 5, 6);

void setup() {
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, INPUT);
  Serial.begin(9600);
  ESerial.begin(9600);
  Serial.println("Starting Reader");
  Transceiver.init();
  Transceiver.PrintParameters();
}

void loop() {
  if (ESerial.available()) {
    Transceiver.GetStruct(&MyData, sizeof(MyData));
    Serial.println("------------- ");
    Serial.print("Temp: "); Serial.println(MyData.Temp);
    Serial.print("Humidity: "); Serial.println(MyData.Humi);
  }else {
    delay(1000);
    Serial.println("Searching: ");
  }
}

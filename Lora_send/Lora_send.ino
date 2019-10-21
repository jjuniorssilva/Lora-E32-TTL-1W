#include <SoftwareSerial.h>
#include "EBYTE.h"
#include <DHT.h>

#define pinDHT 8 
#define DHTTYPE DHT11
DHT dht(pinDHT, DHTTYPE);

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
  dht.begin();
  Serial.begin(9600);
  ESerial.begin(9600);
  Serial.println("Starting Sender");
  Transceiver.init();
  Transceiver.PrintParameters();
}

void loop() {
  MyData.Temp = dht.readTemperature();
  MyData.Humi = dht.readHumidity();
  Transceiver.SendStruct(&MyData, sizeof(MyData));
  Serial.print("Sending..."); 
  delay(1000);

  //strcpy(MyData.t15, "Manoel");
  //Para atribuir um valor a uma string é necessário utilizar a função Strcpy (CPY = copiar; STR = string). 

}

#include "DHT.h"
#define DHTTYPE DHT11

DHT dht(5, DHTTYPE);

void setup()
{
    Serial.begin(9600);
    Serial.println("Pengujian DHT11");
    dht.begin();
}

void loop()
{
    float celcius = dht.readTemperature();
    Serial.print("Suhu: ");
    Serial.print(celcius);
    Serial.println(" C");
}
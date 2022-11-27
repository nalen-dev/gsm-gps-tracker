#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <TimeLib.h>
#include "DHT.h"
#define DHTTYPE DHT11

// initialize pin
DHT dht(5, DHTTYPE);
static const int GPSRx = 3, GPSTx = 4;

// setup
SoftwareSerial SerialGPS(GPSRx, GPSTx);
TinyGPSPlus Gps;

void adjustTimeNow(int H, int M);

// declare
char message[50];
float latitude = 0.1;
float longitude = 0.1;
float temp = 0.1;
char Time[6];
char stmp[7];

void setup()
{
    Serial.begin(9600);
    SerialGPS.begin(9600);
    Serial.println(F("Mulai!!"));
    dht.begin();
}

void loop()
{
    temp = dht.readTemperature();
    dtostrf(temp, 5, 2, stmp);
    getDataGps();
    setMessage(latitude, longitude);
    Serial.println(message);
}

void getDataGps()
{
    SerialGPS.listen();
    while (SerialGPS.available() > 0)
    {
        Gps.encode(SerialGPS.read());
        if (Gps.location.isValid())
        {
            latitude = Gps.location.lat();
            longitude = Gps.location.lng();
            adjustTimeNow(Gps.time.hour(), Gps.time.minute());
            break;
        };
    };
}

void adjustTimeNow(int H, int M)
{
    setTime(H, M, 00, 01, 12, 2022);
    int hAdjust = H + 8;
    if (hAdjust > 23)
    {
        hAdjust -= 24;
    }
    sprintf(Time, "%d:%d", hAdjust, M);
    return;
}

void setMessage(float latitude, float longitude)
{
    char slat[15];
    char slng[15];
    dtostrf(latitude, 9, 6, slat);
    dtostrf(longitude, 11, 6, slng);
    sprintf(message, "Time: %s\nTemp: %s C\nLat: %s\nLong: %s", Time, stmp, slat, slng);
    return;
}
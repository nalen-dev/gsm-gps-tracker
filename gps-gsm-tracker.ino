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
float latitude, longitude, temp;
char Time[6];
char stmp[7];

const unsigned long intervalGPSRead = 10000;
const unsigned long intervalGSMSend = 60000;
unsigned long previousTimeGSM = 0;
unsigned long previousTimeGPS = 0;

void setup()
{
    Serial.begin(9600);
    SerialGPS.begin(9600);
    Serial.println(F("Mulai!!"));
    dht.begin();
}

void loop()
{
    unsigned long currentTime = millis();
    getDataGps();
    if (currentTime - previousTimeGSM >= intervalGSMSend)
    {
        temp = dht.readTemperature();
        dtostrf(temp, 5, 2, stmp);
        setMessage(latitude, longitude);
        Serial.println(message);
        previousTimeGSM = currentTime;
    }
}

void getDataGps()
{
    SerialGPS.listen();
    while (SerialGPS.available() > 0)
    {
        Gps.encode(SerialGPS.read());
        if (Gps.location.isValid() && Gps.location.isUpdated())
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
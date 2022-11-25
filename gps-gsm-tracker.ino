#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <TimeLib.h>

struct data_gps
{
    float latitude;
    float longitude;
    float temp;
    char message[256];
    void setMessage()
    {
        char slat[12];
        char slng[12];
        char stmp[5];
        dtostrf(latitude, 9, 6, slat);
        dtostrf(longitude, 10, 6, slng);
        dtostrf(temp, 5, 2, stmp);
        sprintf(message, "Temp: %s C\nLat: %s\nLong: %s", stmp, slat, slng);
    }
};

void setup()
{
    Serial.begin(9600);
    Serial.println(F("Mulai!!"));
}

void loop()
{
}

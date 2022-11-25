#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// initialize pin
static const int GPSRx = 3, GPSTx = 4;
float Lat, Lng;

// setup
SoftwareSerial SerialGPS(GPSRx, GPSTx);
TinyGPSPlus Gps;

struct data_gps
{
    float latitude;
    float longitude;
    float temp;
    char message[100];
    void setMessage()
    {
        char slat[15];
        char slng[15];
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
    SerialGPS.begin(9600);
    Serial.println(F("Mulai!!"));
}

void loop()
{
    struct data_gps newData = getDataGps();
    Serial.println(newData.message);
}

struct data_gps getDataGps()
{
    struct data_gps newGpsData;
    SerialGPS.listen();
    while (SerialGPS.available() > 0)
    {
        Gps.encode(SerialGPS.read());
        if (Gps.location.isValid())
        {
            newGpsData.latitude = Gps.location.lat();
            newGpsData.longitude = Gps.location.lng();
            newGpsData.temp = 30;
        };
        newGpsData.setMessage();
    };
    return newGpsData;
}
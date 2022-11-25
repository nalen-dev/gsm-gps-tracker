#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <TimeLib.h>

// initialize pin
static const int GPSRx = 3, GPSTx = 4;

// setup
SoftwareSerial SerialGPS(GPSRx, GPSTx);
TinyGPSPlus Gps;

String adjustTimeNow(int H, int M);

struct data_gps
{
    float latitude;
    float longitude;
    float temp;
    String nowT;
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
    String a = adjustTimeNow(Gps.time.hour(), Gps.time.minute());
    struct data_gps newData = getDataGps();
    Serial.println(newData.message);
    Serial.println(a);
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
            break;
        };
        newGpsData.setMessage();
    };
    return newGpsData;
}

String adjustTimeNow(int H, int M)
{
    char Time[6];
    setTime(H, M, 00, 01, 12, 2022);
    int hAdjust = H + 8;
    if (hAdjust > 23)
    {
        hAdjust -= 24;
    }
    sprintf(Time, "%d:%d", hAdjust, M);
    return Time;
}
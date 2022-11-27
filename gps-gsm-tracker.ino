#include <SoftwareSerial.h>

// initialize pin
static const int GSMRx = 6, GSMTx = 7; // Rx Arduino --> Tx GSM && Tx Arduino --> Rx GSM

// setup
SoftwareSerial SerialGSM(GSMRx, GSMTx);

void adjustTimeNow(int H, int M);

// declare
char message[] = "Hello world!";

const unsigned long intervalGSMSend = 60000;
unsigned long previousTimeGSM = 0;

bool send = true;

void setup()
{
    Serial.begin(9600);
    SerialGSM.begin(9600);
    Serial.println(F("START GSM SENDING MESSAGE TEST!!"));
}

void loop()
{

    unsigned long currentTime = millis();
    if (currentTime - previousTimeGSM >= intervalGSMSend && send == true)
    {
        sendMessage();
        send = false;
    }
}

void sendMessage()
{
    Serial.println(F("Sending message ..."));
    SerialGSM.listen();
    delay(5000);
    SerialGSM.print("\r");
    delay(1000);
    SerialGSM.print("AT+CMGF=1\r");
    delay(1000);
    SerialGSM.print("AT+CMGS=\"082xxxxxxx\"\r"); // Phone Number
    delay(1000);
    SerialGSM.print(message);
    delay(5000);
    SerialGSM.write(0x1A);
}
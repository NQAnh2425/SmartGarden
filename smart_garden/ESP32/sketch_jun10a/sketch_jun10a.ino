#define BLYNK_TEMPLATE_ID "TMPL6vl6o82jp"
#define BLYNK_TEMPLATE_NAME "WNS"
#define BLYNK_AUTH_TOKEN "LgNo0jOYpRyRn7loh7SeBZ_RzKC6ntQv"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "BKSTAR_T4_01";
char pass[] = "stemstar";

HardwareSerial STM32Serial(2);

bool lastBlynkState = false;
String rxLine = "";

void setup()
{
    Serial.begin(115200);

    pinMode(16, INPUT_PULLUP);

    // UART2
    STM32Serial.begin(115200, SERIAL_8N1, 16, 17);

    Serial.println("\nConnecting WiFi...");

    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(200);
        Serial.print(".");
    }

    Serial.println("\nWiFi Connected!");

    Blynk.config(BLYNK_AUTH_TOKEN);

    if (Blynk.connect(5000))
    {
        Serial.println("Blynk Connected!");
        lastBlynkState = true;
    }
    else
    {
        Serial.println("Blynk Connection Failed!");
    }
}

void loop()
{
    Blynk.run();

    bool currentState = Blynk.connected();

    if (currentState != lastBlynkState)
    {
        if (currentState)
            Serial.println("Blynk Connected!");
        else
            Serial.println("Blynk Disconnected!");

        lastBlynkState = currentState;
    }

    while (STM32Serial.available())
    {
        char c = STM32Serial.read();

        // Hiện dữ liệu nhận được
        Serial.write(c);

        if (c == '\n')
        {
            uint8_t id;
            uint8_t t_int;
            uint8_t t_dec;
            uint8_t hum;
            uint8_t moi;
            uint16_t crc;
            uint8_t num;

            int ret = sscanf(rxLine.c_str(),
                             "ID:%hhu T:%hhu.%hhu H:%hhu M:%hhu CRC:%hu Num:%hhu",
                             &id,
                             &t_int,
                             &t_dec,
                             &hum,
                             &moi,
                             &crc,
                             &num);

            if (ret == 7)
            {
                float temp = t_int + t_dec / 10.0f;

                switch (id)
                {
                    case 1:
                        Blynk.virtualWrite(V0, temp);
                        Blynk.virtualWrite(V3, hum);
                        break;

                    case 2:
                        Blynk.virtualWrite(V1, temp);
                        Blynk.virtualWrite(V4, hum);
                        break;

                    case 3:
                        Blynk.virtualWrite(V2, temp);
                        Blynk.virtualWrite(V5, hum);
                        break;
                }

                Serial.print("Node ");
                Serial.print(id);
                Serial.println(" -> Blynk updated");
            }
            else
            {
                Serial.print("Parse Error: ");
                Serial.println(rxLine);
            }

            rxLine = "";
        }
        else if (c != '\r')
        {
            rxLine += c;
        }
    }
}

BLYNK_CONNECTED()
{
    Serial.println("BLYNK_CONNECTED callback");
}
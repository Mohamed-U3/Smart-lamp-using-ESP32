/**
 * ***********************************************************
 * @file  : Communication.cpp
 * @brief : file contain functionalities of Communications
 * @author: Engineer\ Mohamed Yousry
 * @date  : 20/02/2024
 * ***********************************************************
 */
/*
 * ***********************************************************
 * 						Includes
 * ***********************************************************
 */
#include "Communication.h"

/*
 * ***********************************************************
 * 						Global variables
 * ***********************************************************
 */
// class and global variable definitions
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

/*
 * ***********************************************************
 * 						Functions body
 * ***********************************************************
 */
/**
 * ***********************************************************
 * @name  : messageHandler
 * @brief : handles message from MQTT servers
 * @author: Engineer\ Mohamed yousry
 * @date  : 20/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void messageHandler(char *topic, byte *payload, unsigned int length)
{
    SERIAL_PRINT("incoming: ");
    SERIAL_PRINTLN(topic);

    JSONDOCUMENT doc;
    DESERIALIZEJSON(doc, payload);
    const char *message = doc["message"];
    SERIAL_PRINTLN();

    for (int i = 0; i < length; i++)
    {
        SERIAL_PRINT((char)payload[i]); // Pring payload content
    }
    SERIAL_PRINTLN();

    char led = (char)payload[0]; // Extracting the controlling command from the Payload to Controlling LED from AWS
    SERIAL_PRINT("Command: ");
    SERIAL_PRINTLN(led);

    if (led == '1') // 49 is the ASCI value of 1
    {
        DIGITAL_WRITE(lamp, HIGH);
        COOMUNICATION_WHITE_LAMP_FLAG = true;
        SERIAL_PRINTLN("Lamp_State changed to HIGH");
    }
    else if (led == '0') // 48 is the ASCI value of 0
    {
        DIGITAL_WRITE(lamp, LOW);
        COOMUNICATION_WHITE_LAMP_FLAG = false;
        SERIAL_PRINTLN("Lamp_State changed to LOW");
    }
    SERIAL_PRINTLN();
}

/**
 * ***********************************************************
 * @name  : connectWiFi
 * @brief : Function that connect the ESP32 to WiFi network
 * @author: Engineer\ Mohamed yousry
 * @date  : 20/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void connectWiFi()
{
    again:
    if (WIFI_STATUS() != WL_CONNECTED)
    {
        WIFI_MODE(WIFI_STA);
        WIFI_BEGIN(WIFI_SSID, WIFI_PASSWORD);

        SERIAL_PRINTLN("Connecting to Wi-Fi");
        char Wifi_count = 0;
        while (WIFI_STATUS() != WL_CONNECTED)
        {
            DELAY(500);
            SERIAL_PRINT(".");
            Wifi_count++;
            if (Wifi_count == 10)
                goto again;
        }
    }
}

/**
 * ***********************************************************
 * @name  : connectAWS
 * @brief : Function that connect the ESP32 to MQTT Server of AWS
 * @author: Engineer\ Mohamed yousry
 * @date  : 20/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void connectAWS()
{
    connectWiFi();

    // Configure WiFiClientSecure to use the AWS IoT device credentials
    NET_SET_CA_CERT(AWS_CERT_CA);
    NET_SET_CERTIFICATE(AWS_CERT_CRT);
    NET_SET_PRIVATEKEY(AWS_CERT_PRIVATE);

    // Connect to the MQTT broker on the AWS endpoint we defined earlier
    CLIENT_SET_SERVER(AWS_IOT_ENDPOINT, 8883);

    // Create a message handler
    CLIENT_SET_CALLBACK(messageHandler);

    SERIAL_PRINTLN("Connecting to AWS IOT");

    while (!CLIENT_CONNECT(THINGNAME))
    {
        SERIAL_PRINT(".");
        DELAY(100);
    }

    if (!CLIENT_CONNECTED())
    {
        SERIAL_PRINTLN("AWS IoT Timeout!");
        return;
    }

    // Subscribe to a topic
    CLIENT_SUBSCRIBE(AWS_IOT_SUBSCRIBE_TOPIC);

    SERIAL_PRINTLN("AWS IoT Connected!");
}

/**
 * ***********************************************************
 * @name  : InitBuiltinLED
 * @brief : Initialize the Built in LED
 * @author: Engineer\ Mohamed yousry
 * @date  : 20/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void InitBuiltinLED()
{
    PIN_MODE     (lamp, OUTPUT   );
    DIGITAL_WRITE(lamp, LOW      );
}
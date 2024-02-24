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
WiFiClient netLocal;
PubSubClient client(net);
PubSubClient clientLocal(netLocal);

uint8_t local_AWS_secection = 0;

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
 * @param : char *topic, byte *payload, uint32_t length
 * @return: void
 * ***********************************************************
 */
void messageHandler(char *topic, byte *payload, uint32_t length)
{
    SERIAL_PRINT("incoming: ");
    SERIAL_PRINTLN(topic);

    JSONDOCUMENT filter;
    filter["intensity"]         = true;
    filter["warmness"]          = true;
    filter["color"]["red"]      = true;
    filter["color"]["green"]    = true;
    filter["color"]["blue"]     = true;


    JSONDOCUMENT doc;
    DESERIALIZATIONERROR DE_error = DESERIALIZEJSON(doc, payload, DeserializationOption::Filter(filter));
    if (DE_error)
    {
        Serial.print(F("JSON parsing failed! Error: "));
        Serial.println(DE_error.c_str());
        return;
    }
    SERIAL_PRINTLN();

    COMM_INTENSITY_GLOBAL_VAR   = (uint8_t) doc["intensity"];
    COMM_WARMNESS_GLOBAL_VAR    = (uint8_t) doc["warmness"];
    COMM_RED_GLOBAL_VAR         = (uint8_t) doc["color"]["red"];
    COMM_GREEN_GLOBAL_VAR       = (uint8_t) doc["color"]["green"];
    COMM_BLUE_GLOBAL_VAR        = (uint8_t) doc["color"]["blue"];

    for (int i = 0; i < length; i++)
    {
        SERIAL_PRINT((char)payload[i]); // Printing payload content
    }
    SERIAL_PRINTLN();

    /* 
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
     */
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
        static uint8_t counter = 0;
        SERIAL_PRINT(".");
        DELAY(100);
        counter++;
        if(counter >= 4)
        {
            local_AWS_secection = 1;
            counter = 0;
            break;
        }
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


/**
 * ***********************************************************
 * @name  : localConnect
 * @brief : Function that connect the ESP32 to local MQTT Server
 * @author: Engineer\ Mohamed yousry
 * @date  : 20/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void localConnect()
{
    connectWiFi();
    
    // // Connect to the local MQTT broker
    clientLocal.setServer(Local_Broker, 1883);

    // Create a message handler
    clientLocal.setCallback(messageHandler);

    SERIAL_PRINTLN("Connecting to Local MQTT");
    while (!clientLocal.connect(THINGNAME))
    {
        static uint8_t counter = 0;
        SERIAL_PRINT(".");
        DELAY(100);
        counter++;
        if(counter >= 4)
        {
            local_AWS_secection = 2;
            counter = 0;
            break;
        }
    }

    if (!clientLocal.connected())
    {
        SERIAL_PRINTLN("MQTT local Timeout!");
        return;
    }

    // Subscribe to a topic
    clientLocal.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

    SERIAL_PRINTLN("Local MQTT Connected!");
}

/**
 * ***********************************************************
 * @name  : performPing
 * @brief : test function for ensuring the connection
 * @author: Engineer\ Mohamed yousry
 * @date  : 24/02/2024
 * @param : const char *host, int8_t attempts, int delayBetweenAttempts
 * @return: bool
 * ***********************************************************
 */
bool performPing(const char *host, int8_t attempts, int delayBetweenAttempts)
{
    if(host == AWS_IOT_ENDPOINT)
    {
        for (int8_t i = 0; i < attempts; i++)
        {
            Serial.print("Ping attempt #");
            Serial.println(i + 1);

            WiFiClient netLocal;
            if (netLocal.connect(host, 8883))
            {
                Serial.println("Ping successful!");
                netLocal.stop();
                return true; // Return true if ping is successful
            }
            else
            {
                Serial.println("Ping failed");
            }

            delay(delayBetweenAttempts);
        }
    }
    else if(host == Local_Broker)
    {
        for (int8_t i = 0; i < attempts; i++)
        {
            Serial.print("Ping attempt #");
            Serial.println(i + 1);

            WiFiClient netLocal;
            if (netLocal.connect(host, 1883))
            {
                Serial.println("Ping successful!");
                netLocal.stop();
                return true; // Return true if ping is successful
            }
            else
            {
                Serial.println("Ping failed");
            }

            delay(delayBetweenAttempts);
        }
    }
    else
    {
        for (int8_t i = 0; i < attempts; i++)
        {
            Serial.print("Ping attempt #");
            Serial.println(i + 1);

            WiFiClient netLocal;
            if (netLocal.connect(host, 80))
            {
                Serial.println("Ping successful!");
                netLocal.stop();
                return true; // Return true if ping is successful
            }
            else
            {
                Serial.println("Ping failed");
            }

            delay(delayBetweenAttempts);
        }
    }
    

    // If all ping attempts fail, return false
    return false;
}

void checkConnection()
{
    connectWiFi();

    
    if(performPing(Local_Broker, 4, 1))
    {
        local_AWS_secection = 1;
    }
    else if(performPing(AWS_IOT_ENDPOINT, 4, 1))
    {
        local_AWS_secection = 2;
    }
    else
    {
        local_AWS_secection = 0;
    }
}

/**
 * ***********************************************************
 * @name  : Communication_Task
 * @brief : Task of Communication that connect the ESP32 to servers
 * @author: Engineer\ Mohamed yousry
 * @date  : 24/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void Communication_Task()
{
    if(local_AWS_secection == 0)
    {
        checkConnection();
    }
    else if (local_AWS_secection == 1)
    {
        if (!clientLocal.connected())
        {
            // For Local MQTT server Connection
            localConnect();
        }
        clientLocal.loop();
    }
    else if(local_AWS_secection == 2)
    {
        if (!client.connected())
        {
            // For AWS server Connection
            connectAWS();
        }
        client.loop();
    }
}
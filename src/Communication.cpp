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
WiFiClientSecure net = WiFiClientSecure();  // a wifi client used to handling/establishing Secure wifi communication with AWS broker
WiFiClient netLocal;                        // a wifi client used to handling/establishing wifi communication with local network/broker
PubSubClient client(net);                   // a client used for the AWS broker communication.
PubSubClient clientLocal(netLocal);         // a client used for the local broker communication.

uint8_t local_AWS_secection     = 0;        // a flag used to switch between the local brocker or the AWS broker.
uint8_t timeout                 = 120;      // seconds to run for AP to stop if ESP32 didn't connect to WiFi

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
 * @param : char *topic -> pointer to the topic name.
 * @param : byte *payload -> pointer to the payload of the message received.
 * @param : uint32_t length -> the length of the message received
 * @return: void
 * ***********************************************************
 */
void messageHandler(char *topic, uint8_t *payload, unsigned int length)
{
    SERIAL_PRINT("incoming: ");
    SERIAL_PRINTLN(topic);

    JSONDOCUMENT filter;
    filter["LampType"]          = true;
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

    COMM_LAMP_TYPE_VAR          = doc["LampType"];
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

    COMM_CAHANGED_LAMP_PAR_FLAG = true;

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
    //New algorithm

    again:
    if (WIFI_STATUS() != WL_CONNECTED)
    {
        // WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
        // it is a good practice to make sure your code sets wifi mode how you want it.

        static uint8_t attempts = 0;

        // WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
        WiFiManager wm;

        // reset settings - wipe stored credentials for testing
        // these are stored by the esp library
        // wm.resetSettings();

        // Automatically connect using saved credentials,
        // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
        // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
        // then goes into a blocking loop awaiting configuration and will return success result

        bool res;
        // res = wm.autoConnect(); // auto generated AP name from chipid
        // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
        res = wm.autoConnect("Smart Lamp AP"); // password protected ap

        if (!res)
        {
            attempts++;
            Serial.print("Failed to connect to saved WiFi .. attempt : ");
            Serial.println(attempts);
            if (attempts >= 4)
            {
                wm.resetSettings();
                attempts = 0;
            }
            goto again;
            // ESP.restart();
        }
        else
        {
            // if you get here you have connected to the WiFi
            Serial.println("connected to saved WiFi...yeey :)");
        }
    }

    //old algorithm

    /* again:
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
    } */
}


/**
 * ***********************************************************
 * @name  : connectAWS
 * @brief : Function that connect the ESP32 to AWS MQTT Broker
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
        if(counter >= 2)
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
 * @name  : OnDemandAPCheck
 * @brief : checks of the button is pressed and then launch AP to configure the WiFi SSID and Password
 * @author: Engineer\ Mohamed yousry
 * @date  : 28/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void OnDemandAPCheck()
{
  // is configuration portal requested?
  if (COMM_PRESSED_BUTTON_FLAG == true)
  {
    WiFiManager wm;

    // reset settings - for testing
    // wm.resetSettings();

    // set configportal timeout
    wm.setConfigPortalTimeout(timeout);

    if (!wm.startConfigPortal("Smart Lamp AP"))
    {
      Serial.println("failed to connect and hit timeout");
      delay(3000);
      // reset and try again, or maybe put it to deep sleep
      ESP.restart();
      delay(5000);
    }

    // if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }

  COMM_PRESSED_BUTTON_FLAG == false;
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
 * @brief : Function that connect the ESP32 to local MQTT Broker
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
    CLIENTLOCAL_SET_SERVER(Local_Broker, 1883);

    // Create a message handler
    CLIENTLOCAL_SET_CALLBACK(messageHandler);

    SERIAL_PRINTLN("Connecting to Local MQTT");
    while (!CLIENTLOCAL_CONNECT(THINGNAME))
    {
        static uint8_t counter = 0;
        SERIAL_PRINT(".");
        DELAY(100);
        counter++;
        if(counter >= 2)
        {
            local_AWS_secection = 2;
            counter = 0;
            break;
        }
    }

    if (!CLIENTLOCAL_CONNECTED())
    {
        SERIAL_PRINTLN("MQTT local Timeout!");
        return;
    }

    // Subscribe to a topic
    CLIENTLOCAL_SUBSCRIBE(AWS_IOT_SUBSCRIBE_TOPIC);

    SERIAL_PRINTLN("Local MQTT Connected!");
}


/**
 * ***********************************************************
 * @name  : performPing
 * @brief : function used to test internet for ensuring the connection
 * @author: Engineer\ Mohamed yousry
 * @date  : 24/02/2024
 * @param : const char *host -> host name to test on it (like URL)
 * @param : int8_t attempts -> number of attempts
 * @param : int delayBetweenAttempts -> how long it take to try again between each attempts in ms
 * @return: bool -> Return false if all ping attempts fail, Return true if ping is successful.
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


/**
 * ***********************************************************
 * @name  : checkConnection
 * @brief : check which MQTT will be used Local or AWS
 * @author: Engineer\ Mohamed yousry
 * @date  : 24/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
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
 * @brief : Task of Communication that handle all the Communication functionalities (wifi, AP, Brokers, etc.)
 * @author: Engineer\ Mohamed yousry
 * @date  : 24/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void Communication_Task()
{
    OnDemandAPCheck();

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
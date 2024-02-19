#ifndef Communication_h
#define Communication_h
// Dependancies
#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include "Certs/secrets.h"
#include "Communication_interface.h"

// class declarations and global variable declarations
extern WiFiClientSecure net;
extern PubSubClient client;

// Functions Declearation
void messageHandler(char *topic, byte *payload, unsigned int length);
void connectAWS();
void InitBuiltinLED();

#endif
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

// Dependancies
#include "Certs/secrets.h"
#include "Communication_interface.h"

// class declearations and global variable declearations
extern WiFiClientSecure net;
extern PubSubClient client;

// Functions Declearation
void messageHandler(char *topic, byte *payload, unsigned int length);
void connectAWS();
void InitBuiltinLED();

#endif
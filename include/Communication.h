/**
 * ***********************************************************
 * @file  : Communication.h
 * @brief : file contain macros for functions from others
 * 			modules, external global variables/objects
 *          Prototypes of functions.
 * ***********************************************************
 */
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/*
 * ***********************************************************
 * 						Includes
 * ***********************************************************
 */
// Dependancies
#include "Certs/secrets.h"
#include "Communication_interface.h"

/*
 * ***********************************************************
 * 						Global variables
 * ***********************************************************
 */
// class declearations and global variable declearations
extern WiFiClientSecure     net;
extern PubSubClient         client;

/*
 * ***********************************************************
 * 						Prototypes
 * ***********************************************************
 */
// Functions Declearation
void messageHandler(char *topic, byte *payload, unsigned int length);
void connectAWS();
void InitBuiltinLED();
void localConnect();
void Communication_Task();

#endif
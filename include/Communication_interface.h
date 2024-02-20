/**
 * ***********************************************************
 * @file  : Communication_interface.h
 * @brief : file contain macros for functions from others
 * 			modules
 * ***********************************************************
 */
#ifndef COMMUNICATION_INTERFACE_H
#define COMMUNICATION_INTERFACE_H

/*
 * ***********************************************************
 * 						Includes
 * ***********************************************************
 */
#include "Common_include.h"

/*
 * ***********************************************************
 * 						Defines
 * ***********************************************************
 */
#define AWS_IOT_SUBSCRIBE_TOPIC                             "esp32/sub"
#define lamp                                                2

// Definition of DataTypes
#define JSONDOCUMENT                                        JsonDocument

// Definition of Function for Portability
#define PIN_MODE(               Micro_PIN, Micro_MODE       )           pinMode(            Micro_PIN,  Micro_MODE      )
#define DIGITAL_WRITE(          Micro_PIN, Micro_val        )           digitalWrite(       Micro_PIN,  Micro_val       )
#define SERIAL_PRINT(           Micro_string                )           Serial.print(       Micro_string                )
#define SERIAL_PRINTLN(         Micro_string                )           Serial.println(     Micro_string                )
#define DESERIALIZEJSON(        Micro_doc, Micro_payload    )           deserializeJson(    Micro_doc, Micro_payload    )
#define WIFI_MODE(              Micro_Mode                  )           WiFi.mode(          Micro_Mode                  )
#define WIFI_BEGIN(             Micro_SSID,Micro_PASS       )           WiFi.begin(         Micro_SSID, Micro_PASS      )
#define WIFI_STATUS(                                        )           WiFi.status(                                    )
#define NET_SET_CA_CERT(        Micro_AWS_CERT_CA           )           net.setCACert(      Micro_AWS_CERT_CA           )
#define NET_SET_CERTIFICATE(    Micro_AWS_CERT_CRT          )           net.setCertificate( Micro_AWS_CERT_CRT          )
#define NET_SET_PRIVATEKEY(     Micro_AWS_CERT_PRIVTE       )           net.setPrivateKey(  Micro_AWS_CERT_PRIVTE       )
#define CLIENT_SET_SERVER(      Micro_ENDPOINT, Micro_PORT  )           client.setServer(   Micro_ENDPOINT, Micro_PORT  )
#define CLIENT_SET_CALLBACK(    Micro_messageHandler        )           client.setCallback( Micro_messageHandler        )
#define CLIENT_CONNECT(         Micro_THINGNAME             )           client.connect(     Micro_THINGNAME             )
#define CLIENT_CONNECTED(                                   )           client.connected(                               )
#define CLIENT_SUBSCRIBE(       Micro_SUBSCRIBE_TOPIC       )           client.subscribe(   Micro_SUBSCRIBE_TOPIC       )
#define DELAY(                  Micro_MS                    )           delay(              Micro_MS                    )

#endif
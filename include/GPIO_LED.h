/**
 * ***********************************************************
 * @file  : GPIO_LED.h
 * @brief : file contain Prototypes(Declearation) of functions.
 * ***********************************************************
 */
#ifndef GPIO_LED_H
#define GPIO_LED_H

/*
 * ***********************************************************
 * 						Includes
 * ***********************************************************
 */
#include "GPIO_LED_interface.h"

/*
 * ***********************************************************
 * 						Prototypes
 * ***********************************************************
 */
// Function Declearation
void Init_General_GPIO();
void InitRGBLamp();
void InitWhiteLamp();
void LED_Task();
void GPIO_Task();

#endif
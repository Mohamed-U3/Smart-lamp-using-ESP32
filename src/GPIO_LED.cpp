/**
 * ***********************************************************
 * @file  : GPIO_LED.cpp
 * @brief : file contain functionalities of GPIO
 * @author: Engineer\ Mohamed Yousry
 * @date  : 20/02/2024
 * ***********************************************************
 */
/*
 * ***********************************************************
 * 						Includes
 * ***********************************************************
 */
#include <Arduino.h>
#include "GPIO_LED_interface.h"

/*
 * ***********************************************************
 * 						Functions body
 * ***********************************************************
 */

/**
 * ***********************************************************
 * @name  : Init_General_GPIO
 * @brief : Initializing General Purpose Pins
 * @author: Engineer\ Mohamed Yousry
 * @date  : 28/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void Init_General_GPIO()
{
  PIN_MODE(TRIGGER_PIN, INPUT_PULLUP);
  ANALOG_WRITE(RED_pin,     0       );
  ANALOG_WRITE(GREEN_pin,   0       );
  ANALOG_WRITE(BLUE_pin,    0       );
  ANALOG_WRITE(WHITE_pin,   0       );
}


/**
 * ***********************************************************
 * @name  : CheckOnButton
 * @brief : Checks if the button is pressed and change the flag
 * @author: Engineer\ Mohamed Yousry
 * @date  : 28/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void CheckOnButton()
{
  if (digitalRead(TRIGGER_PIN) == LOW)
  {
    GPIO_PRESSED_BUTTON_FLAG = true;
  }
}

/**
 * ***********************************************************
 * @name  : InitRGBLamp
 * @brief : Initializing RGB lamp
 * @author: Engineer\ Mohamed Yousry
 * @date  : 20/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void InitRGBLamp()
{
  // LED pins configration
  PIN_MODE(RED_pin,   OUTPUT);
  PIN_MODE(GREEN_pin, OUTPUT);
  PIN_MODE(BLUE_pin,  OUTPUT);
  PIN_MODE(WHITE_pin, OUTPUT);
}

/**
 * ***********************************************************
 * @name  : InitWhiteLamp
 * @brief : Initializing White lamp
 * @author: Engineer\ Mohamed Yousry
 * @date  : 20/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void InitWhiteLamp()
{
  // LED pins configration
  PIN_MODE(Worm_pin,  OUTPUT);
  PIN_MODE(WHITE_pin, OUTPUT);
}

/**
 * ***********************************************************
 * @name  : SetRGBLamp
 * @brief : Set RGB Lamp lights and colors
 * @author: Engineer\ Mohamed Yousry
 * @date  : 20/02/2024
 * @param : uint8_t Red -> first pararmeter which indicated RED color level
 * @param : uint8_t Green -> second pararmeter which indicated Green color level
 * @param : uint8_t Blue -> third pararmeter which indicated Blue color level
 * @param : uint8_t Intensity -> forth pararmeter which indicated White color level
 * @return: void
 * ***********************************************************
 */
void SetRGBLamp(uint8_t Red, uint8_t Green, uint8_t Blue, uint8_t Intensity)
{
  ANALOG_WRITE(RED_pin,     Red       );
  ANALOG_WRITE(GREEN_pin,   Green     );
  ANALOG_WRITE(BLUE_pin,    Blue      );
  ANALOG_WRITE(WHITE_pin,   Intensity );
}

/**
 * ***********************************************************
 * @name  : SetWhiteLamp
 * @brief : Set White Lamp lights and tcc
 * @author: Engineer\ Mohamed Yousry
 * @date  : 20/02/2024
 * @param : uint8_t Worm -> first pararmeter which indicated Worm color level
 * @param : uint8_t Intensity -> second pararmeter which indicated White color level
 * @return: void
 * ***********************************************************
 */
void SetWhiteLamp(uint8_t Worm, uint8_t Intensity)
{
  ANALOG_WRITE(Worm_pin,    Worm      );
  ANALOG_WRITE(WHITE_pin,   Intensity );
  ANALOG_WRITE(GREEN_pin,   0         );
  ANALOG_WRITE(BLUE_pin,    0         );
}

/**
 * ***********************************************************
 * @name  : LED_Task
 * @brief : Tasks of LED module
 * @author: Engineer\ Mohamed Yousry
 * @date  : 20/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void LED_Task()
{
  if(GPIO_CAHANGED_LAMP_PAR_FLAG == true)
  {
    if (strcmp(GPIO_LAMP_TYPE_VAR, "WHITE") == 0)
    {
      InitWhiteLamp();
      SERIAL_PRINTLN("WHITE lamp type Initalized");
      SetWhiteLamp(GPIO_WARMNESS_GLOBAL_VAR, GPIO_INTENSITY_GLOBAL_VAR);
    }
    else if (strcmp(GPIO_LAMP_TYPE_VAR, "RGB") == 0)
    {
      InitRGBLamp();
      SERIAL_PRINTLN("RGB lamp type Initalized");
      SetRGBLamp(GPIO_RED_GLOBAL_VAR, GPIO_GREEN_GLOBAL_VAR, GPIO_BLUE_GLOBAL_VAR, GPIO_INTENSITY_GLOBAL_VAR);
    }
    else
    {
      SERIAL_PRINTLN("Error: Wrong lamp type entered.");
    }

    GPIO_CAHANGED_LAMP_PAR_FLAG = false;
  }
}

/**
 * ***********************************************************
 * @name  : GPIO_Task
 * @brief : Function that used to check on any button if it pressed or not.
 * @author: Engineer\ Mohamed Yousry
 * @date  : 20/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void GPIO_Task()
{
  CheckOnButton();
}

/**
 * ***********************************************************
 * @name  : RGBLampTest
 * @brief : Function that tests the RGB Lamp
 * @author: Engineer\ Mohamed Yousry
 * @date  : 20/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void RGBLampTest()
{
  SetRGBLamp(0, 0, 0, 0); // dark black
  SERIAL_PRINTLN("Color Black");
  DELAY(5000);

  SetRGBLamp(64, 224, 208, 0); // Firoze
  SERIAL_PRINTLN("Color Firoze");
  DELAY(5000);

  SetRGBLamp(222, 49, 99, 0); // Light RED
  SERIAL_PRINTLN("Color Light RED");
  DELAY(5000);

  SetRGBLamp(223, 255, 0, 0); // Yallow Lemmon
  SERIAL_PRINTLN("Color Yallow Lemmon");
  DELAY(5000);

  SetRGBLamp(255, 127, 80, 0); // Orange
  SERIAL_PRINTLN("Color Orange");
  DELAY(5000);

  SetRGBLamp(255, 255, 0, 0); // Yellow
  SERIAL_PRINTLN("Color Yellow");
  DELAY(5000);

  SetRGBLamp(255, 0, 255, 0); // Magenta
  SERIAL_PRINTLN("Color Magenta");
  DELAY(5000);

  SetRGBLamp(0, 255, 255, 0); // Cyan
  SERIAL_PRINTLN("Color Cyan");
  DELAY(5000);
}

/**
 * ***********************************************************
 * @name  : whiteLampTest
 * @brief : Function that tests the white Lamp
 * @author: Engineer\ Mohamed yousry
 * @date  : 20/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void whiteLampTest()
{
  SetWhiteLamp(255, 255);
  SERIAL_PRINTLN("Full white and Worm");
  DELAY(5000);

  SetWhiteLamp(128, 128);
  SERIAL_PRINTLN("Half white and Worm");
  DELAY(5000);

  SetWhiteLamp(255, 128);
  SERIAL_PRINTLN("Half white and Full Worm");
  DELAY(5000);

  SetWhiteLamp(255, 0);
  SERIAL_PRINTLN("Zero white and Full Worm");
  DELAY(5000);

  SetWhiteLamp(128, 255);
  SERIAL_PRINTLN("Full white and Half Worm");
  DELAY(5000);

  SetWhiteLamp(0, 255);
  SERIAL_PRINTLN("Full white and Zero Worm");
  DELAY(5000);

  SetWhiteLamp(0, 0);
  SERIAL_PRINTLN("Zero white and Zero Worm");
  DELAY(5000);
}
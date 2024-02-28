/**
 * ***********************************************************
 * @file  : Global.cpp
 * @brief : file contain functionalities of Global module
 * @author: Engineer\ Mohamed Yousry
 * @date  : 20/02/2024
 * ***********************************************************
 */
/*
 * ***********************************************************
 * 						Includes
 * ***********************************************************
 */
#include "Global.h"

/*
 * ***********************************************************
 * 						Global variables
 * ***********************************************************
 */
uint32_t        minutes_counter             = 0;
bool            minutes_counter_Flag        = false;
bool            Changed_Lamp_par_Flag       = false;
bool            global_Pressed_Button_Flag  = false;

uint8_t         global_RED_color            = 0;
uint8_t         global_GREEN_color          = 0;
uint8_t         global_BLUE_color           = 0;
uint8_t         global_INTENSITY            = 0;
uint8_t         global_WARMNESS             = 0;
const char*     global_LAMPTYPE             = "WHITE";
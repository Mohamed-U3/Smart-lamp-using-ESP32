#ifndef MEMORY_INTERFACE_H
#define MEMORY_INTERFACE_H

#include "Common_include.h"

// Definition for Portability
#define MINUTE_COUNTER                              minutes_counter
#define MEM_MIN_COUNT_FLAG                          minutes_counter_Flag

// Definition of Function for Portability
#define EEPROM_BEGIN(   Micro_size                  )       EEPROM.begin(   Micro_size                  )
#define EEPROM_GET(     Micro_position, Micro_value )       EEPROM.get(     Micro_position, Micro_value )
#define EEPROM_PUT(     Micro_position, Micro_value )       EEPROM.put(     Micro_position, Micro_value )
#define EEPROM_COMMIT(                              )       EEPROM.commit(                              )
#define SERIAL_PRINTLN( Micro_string                )       Serial.println( Micro_string                )

#endif

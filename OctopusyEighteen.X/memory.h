/**
 * Copyright (c) 2017-2022 JL1TTD Hidenori Ishii
 *
 * File:   memory.h
 * Author: JL1TTD Hidenori Ishii
 *
 * Created on Nov. 1st, 2021, 22:16
*******************************************************************************/

#ifndef MEMORY_H
#define MEMORY_H

/**
  Section: Included Files
*/

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: Data EEPROM Module APIs
*/

/**
  @Summary
    Writes a data byte to Data EEPROM

  @Description
    This routine writes a data byte to given Data EEPROM location

  @Preconditions
    None

  @Param
    bAdd  - Data EEPROM location to which data to be written
    bData - Data to be written to Data EEPROM location

  @Returns
    None

  @Example
    <code>
    uint16_t dataeeAddr = 0xF010;
    uint8_t dataeeData = 0x55;

    DATAEE_WriteByte(dataeeAddr, dataeeData);
    </code>
*/
void DATAEE_WriteByte(uint16_t bAdd, uint8_t bData);

/**
  @Summary
    Reads a data byte from Data EEPROM

  @Description
    This routine reads a data byte from given Data EEPROM location

  @Preconditions
    None

  @Param
    bAdd  - Data EEPROM location from which data has to be read

  @Returns
    Data byte read from given Data EEPROM location

  @Example
    <code>
    uint16_t dataeeAddr = 0xF010;
    uint8_t readData;

    readData = DATAEE_ReadByte(dataeeAddr);
    </code>
*/
uint8_t DATAEE_ReadByte(uint16_t bAdd);


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif // MEMORY_H
/**
 End of File
*/


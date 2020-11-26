 /******************************************************************************
 *
 * Module: Common - Macros
 *
 * File Name: bit_math.h
 *
 * Description: Commonly used Macros
 *
 * Author: Sayed Mohsen
 *
 *******************************************************************************/

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#include "STD_Types.h"


/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* Read a certain bit in any register */
#define READ_BIT(REG,BIT) ((REG>>BIT) & 0X01)

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

#endif

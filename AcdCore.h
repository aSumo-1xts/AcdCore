/**
 * @file    AcdCore.h
 * @author  aSumo (1x telescope)
 * @brief   a header file for AcdCore_main.c
 * @version 1.0
 * @date    2023-09-14
 */

// CONFIG
#pragma config FOSC     = INTRCIO   // use internal clock
#pragma config WDTE     = OFF       // not use Watch-Dog Timer
#pragma config PWRTE    = ON        // use Power-Up Timer
#pragma config MCLRE    = OFF       // not use a Reset-Pin
#pragma config BOREN    = OFF       // use Brown-Out Detect
#pragma config CP       = ON        // protect this program
#pragma config CPD      = ON        // protect this data
#define _XTAL_FREQ      4000000     //!< clock at 4MHz
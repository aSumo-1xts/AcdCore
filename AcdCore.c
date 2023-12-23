/**
 * @file    AcdCore.c
 * @author  aSumo (1x telescope)
 * @brief   a program for true-bypass pedals
 * @version 1.0
 * @date    2023-09-14
 * @details You should execute with PIC12F675 and MPLABX IDE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <xc.h>
#include "AcdCore.h"


/**
 * @brief            turn the state of the pedal
 * @param (State)    which state ON or OFF in now
 * @return           the new state after "turn"
 * @details          LED, Relay, and Photocoupler are controled.
 * @n                For reduction of pop noise, output is muted with a photocoupler when the pedal is OFF.
 * @n                I use the photocoupler TLP222A.
 */
bool turn(bool State)
{  
    GP2     = true;     // Photocoupler ON
    __delay_ms(25);
    GP0     = !State;   // LED ON
    GP1     = !State;   // Relay ON
    __delay_ms(25);
    GP2     = State ;   // Photocoupler OFF
    State   = !State;   // new State

    return State;
}


/**
 * @brief   execute "turn" according to the input from the footswitch
 * @details Waiting time should be adjusted to suit your needs.
 */
void main(void)
{    
    // Initialization
    ANSEL   = 0;     // no analog GPIOs
    CMCON   = 0x07;  // comparator off
    ADCON0  = 0;     // AD/DA converters off
    TRISIO0 = 0;     // LED+
    TRISIO1 = 0;     // Relay+
    TRISIO2 = 0;     // Photocoupler
    TRISIO3 = 1;     // foot switch
    TRISIO4 = 1;     // USER switch
    TRISIO5 = 1;     // mode switch
    GPIO    = 0;     // set all pins in LOW
   
    // Variable
    // how many times the loop has passed through the if-branch "GP3==false"
    int pressed  = 0;
    // how many times the loop has passed through the if-branch "GP3==true"
    int released = 2;
    // now which state ON(true) or OFF(false)
    bool state  = true;   
   
    // Mugen Loop
    while(true) {
        // Was pressed or released?
        if(GP3 == false) {                          // pressed
            __delay_ms(20);                         // wait for chattering
            if(GP3 == false) {                      // surely pressed
                released = 0;                       // reset "released"
                pressed++;                          // count up
                if(pressed == 1) {                  // first time?
                    state = turn(state);            // Yes: turn it
                } else {                            // no:
                    pressed = 2;                    // MAX "pressed" is 2
                }
            }
        } else {                                    // released
            __delay_ms(20);                         // wait for chattering
            if(GP3 == true) {                       // surely released
                pressed = 0;                        // reset "pressed"
                released++;                         // count up
                if(released == 1 && GP5 == false) { // first time and in MODE?
                    state = turn(state);            // Yes: turn it
                } else {                            // no:
                    released = 2;                   // MAX "released" is 2
                }
            }
        }
    }
}

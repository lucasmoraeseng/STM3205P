/* ###################################################################
**     Filename    : button.c
**     Project     : ProjectName
**     Processor   : Processor
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : May 30, 2026
**     Abstract    :
**     Author      : Lucas Moraes
**
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/

//--------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------
#include "button.h"

//--------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Code
//--------------------------------------------------------------------

/* ###################################################################
 * Function: FunctionName
 * Author: Moraes, L.
 * Date: May 30, 2026
 * Revision: 1.0
 * --------------------
 * Function description
 *
 *  arg1: input arg1
 *
 *  arg2: input arg2
 *
 *  returns: void
 *
 *
###################################################################*/
void Button_Update(Button_t *button, uint8_t state)
{
    button->KeyDown = 0;
    button->KeyUp = 0;

    button->CurrentState = state;

    if((button->CurrentState == 1) &&
       (button->PreviousState == 0))
    {
        button->KeyDown = 1;
        button->PressingTime = 0;
    }

    if((button->CurrentState == 0) &&
       (button->PreviousState == 1))
    {
        button->KeyUp = 1;
    }

    button->PreviousState = button->CurrentState;
}
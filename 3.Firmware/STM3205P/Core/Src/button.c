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
void Button_Init(Button_t *btn_obj)
{
    btn_obj->CurrentState = 0;
    btn_obj->PreviousState = 0;
    btn_obj->KeyDown = 0;
    btn_obj->KeyUp = 0;
    btn_obj->Pressed = 0;
    btn_obj->PressingTime = 0;
}

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
void Button_Update(Button_t *btn_obj, uint8_t state)
{
    btn_obj->CurrentState = state;

    if(btn_obj->KeyDown && !btn_obj->KeyUp)
    {
        btn_obj->PressingTime++;
    }

    if((btn_obj->CurrentState == 1) && (btn_obj->PreviousState == 0))
    {
        btn_obj->KeyDown = 1;
        btn_obj->PressingTime = 0;
        btn_obj->Pressed = 1;
    }

    if((btn_obj->CurrentState == 0) && (btn_obj->PreviousState == 1))
    {
        btn_obj->KeyUp = 1;
        btn_obj->Pressed = 0;
    }

    btn_obj->PreviousState = btn_obj->CurrentState;
}

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
bool Button_KeyDownEvent(Button_t *btn_obj)
{
    if(btn_obj->KeyDown)
    {
        btn_obj->KeyDown = 0;
        return true;
    }

    return false;
}

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
bool Button_KeyUpEvent(Button_t *btn_obj)
{
    if(btn_obj->KeyUp)
    {
        btn_obj->KeyUp = 0;
        return true;
    }

    return false;
}

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
bool Button_KeyPressedTimeEvent(Button_t *btn_obj, uint32_t time_threshold)
{
    if(btn_obj->Pressed && (btn_obj->PressingTime >= time_threshold))
    {
        btn_obj->PressingTime = 0;
        return true;
    }

    return false;
}
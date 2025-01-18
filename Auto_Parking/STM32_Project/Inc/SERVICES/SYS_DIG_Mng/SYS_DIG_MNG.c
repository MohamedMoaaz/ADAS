/**
* @file SYS_DIG_Mng.c
* @author Mohamed Abd El-Naby (mahameda.naby@gmail.com) 
* @brief 
* @version 0.1
* @date 2023-09-20
*
*/


/******************************************************************************
* Includes
*******************************************************************************/
#include "UTILS.h"
#include "STD_TYPES.h"
#include "SYS_DIG_MNG.h"


/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/




/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/




/******************************************************************************
* Typedefs
*******************************************************************************/




/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static u8 Global_Logged_Error_Arr[E_OK];



/******************************************************************************
* Function Prototypes
*******************************************************************************/




/******************************************************************************
* Function Definitions
*******************************************************************************/
void DIGMngr_voidInit(void)
{
    // Init Array of Errors 
}

void DIGMngr_voidLoggError(ERROR_t copy_xLoggErrorID , u8 ClearOldErrors)
{
    if(ClearOldErrors != 1)
    {
        // Increase Logged Error 
        Global_Logged_Error_Arr[copy_xLoggErrorID]++ ; 
    }
    else
    {
        // Clear Errors 
        Global_Logged_Error_Arr[copy_xLoggErrorID] = 0 ; 
    }

    /*     Soft System Reset   */  
    if (Global_Logged_Error_Arr[copy_xLoggErrorID] >= MAX_LOGGED_ERROR_BEFORE_REST)
    {
        __asm("b Reset_Handler");
    }
}

u8 DIGMngr_u8GetNumberofLoggedErrors(ERROR_t copy_xLoggErrorID)
{
    return Global_Logged_Error_Arr[copy_xLoggErrorID]; 
}



/************************************* End of File ******************************************/

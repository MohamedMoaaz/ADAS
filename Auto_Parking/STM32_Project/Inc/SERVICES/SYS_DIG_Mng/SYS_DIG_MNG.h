/**
* @file SYS_DIG_Mng.h
* @author Your Name (email) 
* @brief 
* @version 0.1
* @date 2023-09-20
*
*/
#ifndef SYS_DIG_Mng__H 
#define SYS_DIG_Mng__H 





/******************************************************************************
* Includes
*******************************************************************************/




/******************************************************************************
* User Configuration
*******************************************************************************/




/******************************************************************************
* Preprocessor Constants
 *******************************************************************************/




/******************************************************************************
* Configuration Constants
*******************************************************************************/




/******************************************************************************
* Macros
*******************************************************************************/
#define MAX_LOGGED_ERROR_BEFORE_REST        3



/******************************************************************************
* Typedefs
*******************************************************************************/




/******************************************************************************
* Variables
*******************************************************************************/




/******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
 * @brief This Function is used to initialize System Diagnostic Manager
 * 
 */
void DIGMngr_voidInit(void); 

/**
 * @brief This Function Used to log error
 * @details If the same error logged for @ref MAX_LOGGED_ERROR_BEFORE_REST times the system will reset 
 *          but if happens while counter doesn't reach to @ref MAX_LOGGED_ERROR_BEFORE_REST the old errors will clear
 * @param copy_xLoggErrorID 
 * @param ClearOldErrors write 1 to clear old errors
 */
void DIGMngr_voidLoggError(ERROR_t copy_xLoggErrorID , u8 ClearOldErrors);

/**
 * @brief Get The number of errors of x Error
 * 
 * @param copy_xLoggErrorID  Error ID 
 * @return u8 Number of logged error
 */
u8 DIGMngr_u8GetNumberofLoggedErrors(ERROR_t copy_xLoggErrorID);
#endif
/************************************* End of File ******************************************/

#pragma once

#include <stdarg.h>

/// @brief  {Private} Outputs Messages to Log Output(stream, file)
/// @param  Message of type Char* 
/// @return Status of Function 0 = Successfull, -1 = UnSuccessfule
static int u_write_out(char);

/// @brief  {Private} Default Outputs Messages to Log Output(stream, file)
/// @param  Message of type Char* Formated.
/// @param  Collection of Varables for Message %i, %s
/// @return Status of Function 0 = Successfull, -1 = UnSuccessfull
static int u_Log_Output(char *, va_list);

/// @brief Info Outputs Messages to Log Output(stream, file)
/// @param  Message of type Char* Formated.
/// @param  Collection of Varables for Message %i, %s
/// @return Status of Function 0 = Successfull, -1 = UnSuccessfull
int u_Log_Information(char *, ...);

/// @brief Error Outputs Messages to Log Output(stream, file)
/// @param  Message of type Char* Formated.
/// @param  Error Number for Message %i
/// @param  Collection of Varables for Message %i, %s
/// @return Status of Function 0 = Successfull, -1 = UnSuccessfull
int u_Log_Error(char *, ...);

/// @brief Debug Outputs Messages to Log Output(stream, file)
/// @param  Message of type Char* Formated.
/// @param  Collection of Varables for Message %i, %s
/// @return Status of Function 0 = Successfull, -1 = UnSuccessfull
int u_Log_Debug(char *, ...);

/// @brief Debug Verbos Messages to Log Output(stream, file)
/// @param  Message of type Char* Formated.
/// @param  Collection of Varables for Message %i, %s
/// @return Status of Function 0 = Successfull, -1 = UnSuccessfull
int u_Log_Verbose(char *, ...);

/// @brief write to u_Log_Output convert int to char
/// @param  float inputi
static void u_write_int_str(int );

/// @brief write to u_log_output convert float to char
/// @param  float inputf
static void u_write_float_str(double );

/// @brief 
/// @param  
static void u_write_str(char * );

typedef enum
{
  U_LOG_INFORMATION_E = 0,
  U_LOG_ERROR_E,
  U_LOG_DEBUG_E,
  U_LOG_VERBOSE_E,
} u_log_t;

/// @brief Enables Output 
/// @param message 
void u_enable_log(u_log_t message);

/// @brief Disables Output 
/// @param message
void u_disable_log(u_log_t message);

/// @brief Enables All Output 
/// @param message
void u_enable_log_all(void);

/// @brief Disables All Output 
/// @param message
void u_disable_log_all(void);

void setTag(char * tag);
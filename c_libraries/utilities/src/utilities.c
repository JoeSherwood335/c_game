#include "utilities.h"
#include <stdarg.h>
#include <stdio.h>

#define max_bufferlen 300

#define U_MESSAGE_INFORMATION "\033[32;1;4mInfo\033[0m \t"
#define U_MESSAGE_DEBUG "\033[34;1;4mDebug\033[0m \t"
#define U_MESSAGE_VERBOSE "\033[35;1;4mVerbose\033[0m\t"
#define U_MESSAGE_ERROR "\033[31;1;4mError\033[0m \t"

int u_write_out(char message)
{

  printf("%c", message);

  //static char cbuffer[max_bufferlen];
  //static int bufferlen;

  //if (message =='\n' || bufferlen >= max_bufferlen)
  //{
  //  print(cbuffer);
  //  print('\n');
  // }

  return 0;
}

int u_Log_Output(char * message, va_list args)
{
  
  int i = 0; 

  for (char *p = message; *p != '\0'; ++p)
  {

    switch (*p)
    {
      case '%':
        switch (*++p) // read format symbol
        {
          case 'i':
            i = va_arg(args, int); 
            
            u_write_int_str(i);
          continue;
          case 'f':
            float f = va_arg(args, double); 
            
            u_write_float_str(f);
            continue;
          case 's':
            //u_write_out(va_arg(args, char *));
            u_write_str(va_arg(args, char *));
            continue;
          case 'c':
            // std::cout << static_cast<char>(va_arg(args, int));
            continue;
          case '%':
            // std::cout << '%';
            continue;
        }
        
        break; // format error...
      case '\n':
        u_write_out('\n');
        continue;
      case '\t':
        u_write_out('\t');
        // std::cout << '\t';
        continue;
      
      default: 
        u_write_out(*p);
    }
  }

  return 0;
}

int u_Log_Information(char * message, ...)
{
             
  
  va_list args, args1;

  va_start(args, message);

  u_Log_Output(U_MESSAGE_INFORMATION, NULL);

  u_Log_Output(message, args);

  va_end(args);

  return 0;
}

int u_Log_Error(char * message, ...)
{
  va_list args;

  va_start(args, message);

  u_Log_Output(U_MESSAGE_ERROR, NULL);

  u_Log_Output(message, args);

  va_end(args);

  return 0;
}

int u_Log_Debug(char * message, ...)
{
  va_list args;

  va_start(args, message);

  u_Log_Output(U_MESSAGE_DEBUG, NULL);

  u_Log_Output(message, args);

  va_end(args);

  return 0;
}

int u_Log_Verbose(char * message, ...)
{
  va_list args;

  va_start(args, message);
  
  u_Log_Output(U_MESSAGE_VERBOSE, NULL);

  u_Log_Output(message, args);

  va_end(args);

  return 0;
}

void u_write_int_str(int i)
{
  char p[20];
  unsigned int p_size = 0, r_size = 0; 
  
  r_size = sprintf(p,"%i", i);
   
  char *b = (char *)&p;

  while(*b != '\0')
  {

    u_write_out(*b++);
  }
}

void u_write_float_str(double i)
{
  char p[20];
  unsigned int p_size = 0, r_size = 0; 
  
  r_size = sprintf(p,"%f", i);
   
  char *b = (char *)&p;

  while(*b != '\0')
  {

    u_write_out(*b++);
  }
}

void u_write_str(char * b)
{
  
  while(*b != '\0')
  {

    u_write_out(*b++);
  }
}


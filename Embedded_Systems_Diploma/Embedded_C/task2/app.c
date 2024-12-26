#include "Uart.h"
unsigned char string_buffer[100] = "learn-in-depth: <Omar-Ehab>";
void main (void)
{

  Uart_Send_string(string_buffer);

}
//Learn-in-depth
//Omar Ehab 
//Mastring_Embedded_System_Online

#include<stdint.h>
#define STACK_Start_SP 0x20001000
extern int main(void);
void Rest_Handler (void)
{
	main();
}
void NMI_Handler (void)
{
	Rest_Handler();
}
void H_fault_Handler (void)
{
	Rest_Handler();
}
void MM_fault_Handler (void)
{
	Rest_Handler();
}
void Bus_fault (void)
{
	Rest_Handler();
}
void Usage_fault_Handler (void)
{
	Rest_Handler();
}
uint32_t vectors[] __attribute__((section(".vectors")))  = {
STACK_Start_SP,
(uint32_t) &Rest_Handler,
(uint32_t) &NMI_Handler,
(uint32_t) &H_fault_Handler,
(uint32_t) &MM_fault_Handler,
(uint32_t) &Bus_fault,
(uint32_t) &Usage_fault_Handler,
};
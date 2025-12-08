#include <stdint.h>

// GPIOA boundary start address
#define GPIOA 	 		0x40020000U
// Reset and Clock Control start address
#define RCC				0x40023800U

#define GPIOA_MODER 	  (*(uint32_t volatile *)	(GPIOA + 0x00U))
#define GPIOA_OTYPER 	  (*(uint32_t volatile *)	(GPIOA + 0x04U))
#define GPIOA_PUPDR 	  (*(uint32_t volatile *)	(GPIOA + 0x0CU))
#define GPIOA_BSRR		  (*(uint32_t volatile *)	(GPIOA + 0x18U))
#define RCC_AHB1_GPIOA_EN (*(uint32_t volatile*)(RCC  +  0x30U))

/* Functions Prototypes*/
void delay(uint32_t tick);
void userLedOff(void);
void userLedOn(void);
void gpioInit(void);


void gpioInit(void)
{
	/*GPIOA Clock Enable*/
	RCC_AHB1_GPIOA_EN |= (1U << 0U);

	/* PA5 pin configuration*/
	GPIOA_MODER  &= ~(3U << 10U);
	GPIOA_MODER  |=  (1U << 10U); // Output mode
	GPIOA_OTYPER &= ~(1u << 5U);
	GPIOA_PUPDR  &= ~(3U << 10U); // No pull up/down
}










int main(void)
{
	gpioInit();

	while(1)
	{
		userLedOn();
		delay(500000);
		userLedOff();
		delay(500000);
	}
}











void delay(uint32_t tick)
{
	uint32_t volatile counter= 0;
	while(counter < tick){
		counter++;
	}
}

void userLedOn(void)
{
	GPIOA_BSRR = (1U << 5U); // PA5 SET
}

void userLedOff(void)
{
	GPIOA_BSRR = (1U << (5U+16U)); // PA5 RESET
}




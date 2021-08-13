#include<stm32f1xx.h>
void SystemClockInit()
{
	RCC->CR |= 1<<0;
	while((RCC->CR & (uint32_t)(1<<1)) == 0);
	RCC->APB2ENR |= (1<<3) | (1<<4);
}
void GPIO_Init()
{
	GPIOB->CRH &=~(0x0000ff00);
	GPIOB->CRH |= (1<<11) | (1<<15);
	GPIOB->ODR |= (1<<10) | (1<<11);

	GPIOC->CRL &= ~(0x000000ff);
	GPIOC->CRL |= (1<<0) | (1<<4);

}
void delay(uint32_t time)
{
	while(time--);
}
int main()
{
	SystemClockInit();
	GPIO_Init();
	while(1)
	{
		if((GPIOB->IDR & (1<<10)) == 0)
		{
			GPIOC->BSRR |= 3<<0;

		}
		else
		{
			GPIOC->BSRR |= 3<<16;
		}
		if((GPIOB->IDR & (1<<11)) == 0)
		{
			for(int i=0;i<10;i++)
			{
				GPIOC->BSRR |= 3<<0;
				delay(720000);
				GPIOC->BSRR |= 3<<16;
				delay(720000);
			}
		}
	}
	return 0;
}

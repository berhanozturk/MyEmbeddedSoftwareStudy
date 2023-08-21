#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "delay.h"
void gpioConfig(){
	GPIO_InitTypeDef GPIOSturcture;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIOSturcture.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOSturcture.GPIO_Pin= GPIO_Pin_0;
	GPIOSturcture.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIOSturcture);
}

int main(){
	gpioConfig();
	DelayInit();
	
	while(1){
		GPIO_SetBits(GPIOB,GPIO_Pin_0);
		delay_ms(1000);
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		delay_ms(1000);
	}
}

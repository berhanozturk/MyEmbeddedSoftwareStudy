#include "stm32f10x.h"                  // Device header
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI

uint16_t counter =0;
void gpioConfig(){
	GPIO_InitTypeDef GPIOInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	//LED
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInitStructure);
	
	//BUTTON
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOC, &GPIOInitStructure);
}
	
	
	
void extiConfig(){
	EXTI_InitTypeDef EXTIInitStructure;
	NVIC_InitTypeDef NVICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource6);
	EXTIInitStructure.EXTI_Line=EXTI_Line6;
	EXTIInitStructure.EXTI_LineCmd= ENABLE;
	EXTIInitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTIInitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
	
	EXTI_Init(&EXTIInitStructure);

	NVICInitStructure.NVIC_IRQChannel= EXTI9_5_IRQn;
	NVICInitStructure.NVIC_IRQChannelCmd= ENABLE;
	NVICInitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVICInitStructure.NVIC_IRQChannelSubPriority=1;	
	
	NVIC_Init(&NVICInitStructure);
}

void EXTI9_5_IRQHandler(){
	if(EXTI_GetITStatus(EXTI_Line6)!=RESET){
		counter++;
}
	EXTI_ClearITPendingBit(EXTI_Line6);

}
void delay(uint32_t time){
while(time--);
}

int main(){
gpioConfig();
extiConfig();
//int ledArray[3] ={GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2};
	
	while(1){
			GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);
			delay(360000);
			GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);
			delay(360000);}

}

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
void gpioConfig(){
	GPIO_InitTypeDef GPIOStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIOStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIOStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIOStructure);
}

void timerConfig(){
	TIM_TimeBaseInitTypeDef TIMStructure;
	NVIC_InitTypeDef NVICStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIMStructure.TIM_ClockDivision = 1;
	TIMStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIMStructure.TIM_Period= 5999;
	TIMStructure.TIM_Prescaler=3999;
	TIMStructure.TIM_RepetitionCounter=0;
	
	TIM_TimeBaseInit(TIM3,&TIMStructure);
	TIM_Cmd(TIM3,ENABLE);
	
	NVICStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVICStructure.NVIC_IRQChannelCmd = ENABLE;
	NVICStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVICStructure.NVIC_IRQChannelSubPriority =0;
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	NVIC_Init(&NVICStructure);
}
void toogle_led(){
	uint16_t readled = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);
	if(readled==(uint16_t)Bit_SET){
		GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);
}
	else{
		GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);
	}
}
void TIME3_IRQHandle(){
	toogle_led();
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //timera ne yapacagiz
}
int main(){
	gpioConfig();
	timerConfig();
	while(1){
		/////
}
}

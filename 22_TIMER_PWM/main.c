#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

void gpioConfig(){
	GPIO_InitTypeDef GPIOStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIOStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIOStructure.GPIO_Pin= GPIO_Pin_0;
	GPIOStructure.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIOStructure);
}

void timerConfig(){
	TIM_TimeBaseInitTypeDef TIMStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIMStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIMStructure.TIM_CounterMode= TIM_CounterMode_Up;
	TIMStructure.TIM_Period=2399;
	TIMStructure.TIM_Prescaler=10;
	TIMStructure.TIM_RepetitionCounter=0;
	
	TIM_TimeBaseInit(TIM2,&TIMStructure);
	TIM_Cmd(TIM2,ENABLE);
}

void pwmConfig(uint32_t timPulse){	
	//PWM IÇIN BUNLARI KULLANMAMIZ YETERLI DIGERLERI ADVANCE TIM1 TIM8 IÇIN KULLANILIR
	TIM_OCInitTypeDef TIMER_OCStructure;
	
	TIMER_OCStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIMER_OCStructure.TIM_OutputState= TIM_OutputState_Enable;
	TIMER_OCStructure.TIM_OCPolarity= TIM_OCPolarity_High;
	TIMER_OCStructure.TIM_Pulse=timPulse;
	
	TIM_OC1Init(TIM2,&TIMER_OCStructure);
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);	
}
void delay (uint32_t timer){
	while(timer--);
}
int main(){
	gpioConfig();
	timerConfig();
	
	while(1){
		pwmConfig(599);
		delay(3600000);
		pwmConfig(1199);
		delay(3600000);
		pwmConfig(1799);
		delay(3600000);
		pwmConfig(2399);
		delay(3600000);

	}
	
}

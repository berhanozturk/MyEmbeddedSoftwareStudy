#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

void gpioConfig(){
	GPIO_InitTypeDef GPIOStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIOStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIOStructure.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1 | GPIO_Pin_2;
	GPIOStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOStructure);
	
}
void timerConfig(){
	TIM_TimeBaseInitTypeDef TIMStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIMStructure.TIM_ClockDivision= TIM_CKD_DIV1;
	TIMStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIMStructure.TIM_Period=2399;
	TIMStructure.TIM_Prescaler=10;
	TIMStructure.TIM_RepetitionCounter=0;
	
	TIM_TimeBaseInit(TIM2,&TIMStructure);
	TIM_Cmd(TIM2, ENABLE);
}
void pwmConfig(uint32_t TIMpulse){
	TIM_OCInitTypeDef TIM_OCStructure;
	TIM_OCStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStructure.TIM_Pulse = TIMpulse;
	
	TIM_OC1Init(TIM2,&TIM_OCStructure);
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
}
void pwm1Config(uint32_t TIMpulse){
	TIM_OCInitTypeDef TIM_OCStructure;
	TIM_OCStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStructure.TIM_Pulse = TIMpulse;
	
	TIM_OC2Init(TIM2,&TIM_OCStructure);
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);
}
void pwm2Config(uint32_t TIMpulse){
	TIM_OCInitTypeDef TIM_OCStructure;
	TIM_OCStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStructure.TIM_Pulse = TIMpulse;
	
	TIM_OC3Init(TIM2,&TIM_OCStructure);
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
}
void delay(uint32_t timer){
	while(timer--);
}

int main(){
	gpioConfig();
	timerConfig();
	while(1){
		for(int i=1; i<2399;i++){
			pwmConfig(i);
			delay(3600);
		}
		for(int i=1; i<2399;i++){
			pwm1Config(i);
			delay(3600);
		}
		for(int i=1; i<2399;i++){
			pwm2Config(i);
			delay(3600);
		}

	}
}

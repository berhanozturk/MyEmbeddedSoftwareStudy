#include "stm32f10x.h"       // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
uint16_t adcVal=0;
float mapVal=0;

void gpioConfig(){
	GPIO_InitTypeDef GPIOInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//LED
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIOInitStructure);
	//potansiyemetre
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIOInitStructure);
}
void timerConfig(){
	TIM_TimeBaseInitTypeDef TIMStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIMStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIMStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIMStructure.TIM_Period=4799;
	TIMStructure.TIM_Prescaler=100;
	TIMStructure.TIM_RepetitionCounter=0;
	
	TIM_TimeBaseInit(TIM2,&TIMStructure);
	TIM_Cmd(TIM2,ENABLE);
}

void adcConfig(){
	ADC_InitTypeDef adcStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	adcStructure.ADC_ContinuousConvMode = ENABLE;
	adcStructure.ADC_DataAlign = ADC_DataAlign_Right;
	adcStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	adcStructure.ADC_Mode= ADC_Mode_Independent;
	adcStructure.ADC_NbrOfChannel=1;
	adcStructure.ADC_ScanConvMode= DISABLE;
	
	ADC_Init(ADC1,&adcStructure);
	ADC_Cmd(ADC1,ENABLE);
}

uint16_t readADC(){
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	
	return ADC_GetConversionValue(ADC1);
}

float map(float adcVal, float max, float min, float conMax, float conMin){
return adcVal*((conMax-conMin)/(max-min));
}

void pwmConfig(uint32_t TIMpulse){
	TIM_OCInitTypeDef TIM_OCStructure;
	TIM_OCStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCStructure.TIM_Pulse=TIMpulse;
	
	TIM_OC1Init(TIM2,&TIM_OCStructure);
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
}

void delay(uint32_t time ){

   while(time--);

}


int main(){
	gpioConfig();
	adcConfig();
	timerConfig();
	while(1){
		adcVal=readADC();
		mapVal=map(adcVal,4030,0,180,0);
		pwmConfig(mapVal);
}
}

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
uint16_t adcVal=0;
float mapVal=0;

void gpioConfig(){
	GPIO_InitTypeDef GPIOInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//LED
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIOInitStructure);
	//potansiyemetre
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIOInitStructure);
}

void adcConfig(){
	ADC_InitTypeDef adcStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	adcStructure.ADC_ContinuousConvMode = ENABLE;
	adcStructure.ADC_DataAlign = ADC_DataAlign_Right;
	adcStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	adcStructure.ADC_Mode= ADC_Mode_Independent;
	adcStructure.ADC_NbrOfChannel=0;
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

int main(){
gpioConfig();
adcConfig();
	
	while(1){
	adcVal=readADC();
	mapVal=map(adcVal,4025,0,180,0);
		if(mapVal>=0 && mapVal<60){
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
			GPIO_ResetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_2);
			
		}
			if(mapVal>=60 && mapVal<120){
			GPIO_SetBits(GPIOB,GPIO_Pin_1);
			GPIO_ResetBits(GPIOB,GPIO_Pin_0 | GPIO_Pin_2);
	}
				if(mapVal>=120 && mapVal<180){
			GPIO_SetBits(GPIOB,GPIO_Pin_2);
			GPIO_ResetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_0);
}
}
}
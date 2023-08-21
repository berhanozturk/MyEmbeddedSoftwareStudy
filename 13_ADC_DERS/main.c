#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC

uint16_t adcValue=0;
float adcVolt=0;
float mapVal=0;

void gpioConfig(){
	GPIO_InitTypeDef GPIOInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIOInitStructure.GPIO_Mode= GPIO_Mode_AIN;
	GPIOInitStructure.GPIO_Pin=GPIO_Pin_0;
	
	GPIO_Init(GPIOA,&GPIOInitStructure);
}

void adcConfig(){
	ADC_InitTypeDef ADCStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	ADCStructure.ADC_ContinuousConvMode= ENABLE;
	ADCStructure.ADC_DataAlign= ADC_DataAlign_Right;
	ADCStructure.ADC_ExternalTrigConv= ADC_ExternalTrigConv_None;
	ADCStructure.ADC_Mode= ADC_Mode_Independent;
	ADCStructure.ADC_NbrOfChannel= 1;
	ADCStructure.ADC_ScanConvMode= DISABLE;
	
	ADC_Init(ADC1,&ADCStructure);
	ADC_Cmd(ADC1,ENABLE);
}

uint16_t readADC(){
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	
	return ADC_GetConversionValue(ADC1);
}

float map(float adcValue, float max, float min, float conMax, float conMin){
	return adcValue*((conMax-conMin)/(max-min));
}
int main(){
	gpioConfig();
	adcConfig();
	
	while(1){
		adcValue=readADC();
		adcVolt=adcValue*(2.98/4025);
		mapVal=map(adcValue,4025,0,180,0);
}
}
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stm32f10x_dac.h"              // Keil::Device:StdPeriph Drivers:DAC
 
uint16_t adcVal = 0;

void gpioConfig(){
	GPIO_InitTypeDef GPIOStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIOStructure.GPIO_Mode= GPIO_Mode_AIN;
	GPIOStructure.GPIO_Pin= GPIO_Pin_0 | GPIO_Pin_4;
	GPIO_Init(GPIOA,&GPIOStructure);
}
void adcConfig(){
	ADC_InitTypeDef ADCStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	ADCStructure.ADC_ContinuousConvMode=ENABLE;
	ADCStructure.ADC_DataAlign= ADC_DataAlign_Right;
	ADCStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	ADCStructure.ADC_Mode= ADC_Mode_Independent;
	ADCStructure.ADC_NbrOfChannel=1;
	ADCStructure.ADC_ScanConvMode=DISABLE;
	
	ADC_Init(ADC1,&ADCStructure);
	ADC_Cmd(ADC1,ENABLE);
}
uint16_t readADC(){
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	
	return ADC_GetConversionValue(ADC1);
}
void dacConfig(){
	DAC_InitTypeDef DACStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
	DACStructure.DAC_LFSRUnmask_TriangleAmplitude = DISABLE;
	DACStructure.DAC_OutputBuffer=ENABLE;
	DACStructure.DAC_Trigger= DAC_Trigger_None;
	DACStructure.DAC_WaveGeneration=DAC_WaveGeneration_None;
	
	DAC_Init(DAC_Channel_1,&DACStructure);
	DAC_Cmd(DAC_Channel_1, ENABLE);
}

int main(){
	gpioConfig();
	adcConfig();
	dacConfig();
	
	while(1){
		adcVal=readADC();
		
		DAC_SetChannel1Data(DAC_Channel_1,adcVal);
	}
}

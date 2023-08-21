#include "stm32f10x.h"                  // Device header
#include "stm32f10x_dac.h"              // Keil::Device:StdPeriph Drivers:DAC
float dacVal1;
float dacVal2;
void gpioConfig(){
	GPIO_InitTypeDef GPIOInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //LED
	
	GPIOInitStructure.GPIO_Mode= GPIO_Mode_Out_PP;
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIOInitStructure);
}

void dacConfig(){
	DAC_InitTypeDef DACInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
	
	DACInitStructure.DAC_LFSRUnmask_TriangleAmplitude= DISABLE;
	DACInitStructure.DAC_OutputBuffer=ENABLE;
	DACInitStructure.DAC_Trigger= DAC_Trigger_None;
	DACInitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	
	DAC_Init(DAC_Channel_1,&DACInitStructure);
	DAC_Init(DAC_Channel_2,&DACInitStructure);
	DAC_Cmd(DAC_Channel_1,ENABLE);
	DAC_Cmd(DAC_Channel_2,ENABLE);
}

void delay(uint32_t time){
	while(time--);
}

int main(){
	gpioConfig();
	dacConfig();
	
	while(1){
		for(dacVal1=0;dacVal1<255;dacVal1++){
			DAC_SetChannel1Data(DAC_Align_8b_R,dacVal1);
			delay(36000);
			}
		for(dacVal1=254;dacVal1>0;dacVal1--){
			DAC_SetChannel1Data(DAC_Align_8b_R,dacVal1);
			delay(36000);
			}
		for(dacVal2=0;dacVal2<255;dacVal2++){
			DAC_SetChannel2Data(DAC_Align_8b_R,dacVal2);
			delay(36000);
		}
		for(dacVal2=254;dacVal2>0;dacVal2--){
			DAC_SetChannel2Data(DAC_Align_8b_R,dacVal2);
			delay(36000);
	}
	}
}
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

int counter=0;
void gpioConfig(){
	GPIO_InitTypeDef GPIOInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIOInitStructure.GPIO_Mode= GPIO_Mode_Out_PP;
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2;
	GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIOInitStructure);
}

void timerConfig(){
	TIM_TimeBaseInitTypeDef TIMStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	TIMStructure.TIM_ClockDivision = 1;
	TIMStructure.TIM_CounterMode = TIM_CounterMode_Up; //0DAN 65555E KADADR SAYACAK
	TIMStructure.TIM_Period = 4799; //1 SNDE ISLEM YAPMAK ISTIYORUZ, CLOC/(PRESCLAER+1).(PERIOD+1) = 1 ISTEDIK CLOCK DEGERI 24 MHZ IDI ONA GÖRE DÜSÜNÜNCE PRESICALERA RASTGELE VERDIK TAM 1 ÇIKMASI IÇINDE PERIODA O DENK GELDI FALAN FILAN
	TIMStructure.TIM_Prescaler =9999;
	TIMStructure.TIM_RepetitionCounter=0; //ADVANCE TIMER OLMADIGI ICIN 0
	
	TIM_TimeBaseInit(TIM6,&TIMStructure);
	TIM_Cmd(TIM6,ENABLE);
}

int main(){
	gpioConfig();
	timerConfig();
	while(1){
		counter=TIM_GetCounter(TIM6); //TIMER DEGERIMIZI ALDIK
		
		if(counter==1999){
			GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);
			
		} else if(counter==3999){
		GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);
		}
	}
}

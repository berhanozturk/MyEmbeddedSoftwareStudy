#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "sevenSegment.h"


int main(){
	sevenSegment(portA,PIN0,PIN1,PIN2,PIN3,PIN4,PIN5,PIN6);
	
	while(1){
		countForward(portA,3600000);
		cleanDisplay(portA);
		countBackward(portA,3600000);
	}
}


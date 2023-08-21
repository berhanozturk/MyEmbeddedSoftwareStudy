#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "sevenSegment.h"

//PORT DEFINATION:
#define portA GPIOA
#define portB GPIOB
#define portC GPIOC

//PIN DEFINATION:
#define PIN0 (uint16_t)GPIO_Pin_0
#define PIN1 (uint16_t)GPIO_Pin_1
#define PIN2 (uint16_t)GPIO_Pin_2
#define PIN3 (uint16_t)GPIO_Pin_3
#define PIN4 (uint16_t)GPIO_Pin_4
#define PIN5 (uint16_t)GPIO_Pin_5
#define PIN6 (uint16_t)GPIO_Pin_6
#define PIN7 (uint16_t)GPIO_Pin_7
#define PIN8 (uint16_t)GPIO_Pin_8
#define PIN9 (uint16_t)GPIO_Pin_9
#define PIN10 (uint16_t)GPIO_Pin_10
#define PIN11 (uint16_t)GPIO_Pin_11
#define PIN12 (uint16_t)GPIO_Pin_12
#define PIN13 (uint16_t)GPIO_Pin_13
#define PIN14 (uint16_t)GPIO_Pin_14
#define PIN15 (uint16_t)GPIO_Pin_15

#define NUMBERSIZE 10
#define LETTERSIZE 8
#define CHARSIZE 4
#define CLEAR 6

uint32_t numberArray[]={0x3F,0x6,0x5B,0x4F,0x66,0x6D,0x7C,0x7,0x7F,0x6F};
uint32_t letterArray[]={0x77,0x7F,0x39,0x3F,0x79,0x71,0x7D,0x76};
uint32_t characterArray[] = {0x40,0x49,0x5C,0x52};
uint32_t clearArray[]={0x1,0x2,0x4,0x8,0x10,0x20};

void sevenSegment(GPIO_TypeDef* port, uint16_t pin0,
																			uint16_t pin1,
																			uint16_t pin2,
																			uint16_t pin3,
																			uint16_t pin4,
																			uint16_t pin5,
																			uint16_t pin6)
{
	if(port==portA){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	}
	else if(port==portB){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	}
	else if(port==portC){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	}
	else{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	}
	GPIO_InitTypeDef GPIOStructure;
	
	GPIOStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIOStructure.GPIO_Pin = pin0|pin1|pin2|pin3|pin4|pin5|pin6;
	
	GPIO_Init(port,&GPIOStructure);
}
void delay(uint32_t time){
while(time--);
}
void printNumber(GPIO_TypeDef* port, uint16_t number){
	if(number==0){
		port->ODR = numberArray[0];
	}
	else if(number==1){
		port->ODR = numberArray[1];
	}
	else if(number==2){
		port->ODR = numberArray[2];
	}
	else if(number==3){
		port->ODR = numberArray[3];
	}
	else if(number==4){
		port->ODR = numberArray[4];
	}
	else if(number==5){
		port->ODR = numberArray[5];
	}
	else if(number==6){
		port->ODR = numberArray[6];
	}
	else if(number==7){
		port->ODR = numberArray[7];
	}
	else if(number==8){
		port->ODR = numberArray[8];
	}
	else if(number==9){
		port->ODR = numberArray[9];
	}
	else{
		port->ODR = characterArray[0];
	}
	
}
void printLetters(GPIO_TypeDef* port, char letter){
	if(letter=='a' || letter == 'A'){
		port->ODR = letterArray[0];
	}
	else if(letter=='b'||letter=='B'){
		port->ODR = numberArray[1];
	}
	else if(letter=='c'||letter=='C'){
		port->ODR = numberArray[2];
	}
	else if(letter=='d'||letter=='D'){
		port->ODR = numberArray[3];
	}
	else if(letter=='e'||letter=='E'){
		port->ODR = numberArray[4];
	}
	else if(letter=='f'||letter=='F'){
		port->ODR = numberArray[5];
	}
	else if(letter=='g'||letter=='G'){
		port->ODR = numberArray[6];
	}
	else if(letter=='h'||letter=='H'){
		port->ODR = numberArray[7];
	}
	else{
		port->ODR = characterArray[0];
	}
	
}



void countForward(GPIO_TypeDef* port, uint32_t time){
	for(int i=0; i<NUMBERSIZE; i++){
		port->ODR = numberArray[i];
		delay(time);
	}
}
void countBackward(GPIO_TypeDef* port, uint32_t time){
	for(int i=NUMBERSIZE-1; i>=0; i--){
		port->ODR = numberArray[i];
		delay(time);
	}
}
void cleanDisplay(GPIO_TypeDef* port){
	for(int i=0; i<CLEAR;i++){
		port->ODR = clearArray[i];
		delay(1080000);
	}
}
int main(){
	sevenSegment(portA,PIN0,PIN1,PIN2,PIN3,PIN4,PIN5,PIN6);
	
	while(1){
	countForward(portA,3600000);
	cleanDisplay(portA);
	countBackward(portA,3600000);
	cleanDisplay(portA);
	}
}

#include "stm32f10x.h"                  // Device header

void gpioConfig(){  //Bu fonk. pinlerimizi, hizimizi vb birimleri tanimlamak i�in kullaniriz.

GPIO_InitTypeDef GPIOInitStructure; //Bir sinif ve yapici method ile canlandirmaya baslariz.
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //PORTUMUZU AKTIFLESTIRIYORUZ, ILK PARAMETREYE AKTIFLESTIRECEGIMIZ PINI YAZDIK. HANGI PORTA BAGLI OLDUGUNU �GRENMEK I�IN DATASHEETDEN BLOCK DIAGRAMA BAKABILIRSINIZ

GPIOInitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //KULLANACAGIM MOD PUSH-PULL
GPIOInitStructure.GPIO_Pin=GPIO_Pin_0;        //LEDIMI BAGLAYACAGIM PIN
GPIOInitStructure.GPIO_Speed=GPIO_Speed_50MHz; // HIZI
	
//AYARLAMALARIMI ISLETIM SISTEMINE BILDIRECEGIM
GPIO_Init(GPIOB,&GPIOInitStructure);
}

void delay(uint32_t time){ //ledimizin yanip s�nmesi i�in fonk. olusturduk
	
	while(time--);
}


int main(){
gpioConfig();

while(1){
//GPIO_SetBits(GPIOB,GPIO_Pin_0); //LEDIMIZI YAKMAK I�IN
//delay(360);
//GPIO_ResetBits(GPIOB, GPIO_Pin_0);
//delay(360);
	
	GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
	delay(3600000);
	GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);
	delay(3600000);
}
	

}
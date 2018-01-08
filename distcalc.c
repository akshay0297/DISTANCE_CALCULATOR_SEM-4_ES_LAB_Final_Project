#include<LPC17xx.h>
#include<stdio.h>

#define rs 0x08000000
#define en 0x10000000
#define dt 0x07800000

void lcd_init(void);
void wr_cn(void);
void clr_disp(void);
void delay_lcd(unsigned int);
void lcd_com(void);
void wr_dn(void);
void clr_ports(void);
void lcd_puts(char *);

unsigned long int temp1 =0, temp2 = 0 ;

int main (void)
{
	unsigned int i;
	char msg[16] = {"DISTANCE:"};
	char msg2[16] = {"cm"};
	
	SystemInit();
	SystemCoreClockUpdate();
	
	lcd_init();
	temp1 = 0x80;
	lcd_com();
	delay_lcd(800);
	lcd_puts(&msg[0]);


//ab trigger ke liye delay dalna hai and echo pin ke interrupt set karna hai 
//jo hum external interrupt se kariyange jiske rising edge pe timer start kariyange 
//aur falling edge pe hum timer stop kariyange 
//wo time nikal ke usko speed of sound se multiply karke usko lcd pe dispaly kardeiyange :P

	LPC_PINCON->PINSEL2 = 0x00;
	LPC_PINCON->PINSEL4 = (2<<20); // setting P2.10 and P2.11 as echo pins 

	LPC_GPIO1 -> FIODIR = (0x1<<23); // setting 1.23 as Trigger Input
	
	LPC_SC->EXTINT=0x01;
	LPC_SC->EXTMODE = 0x01;
	LPC_SC->EXTPOLAR = 0x01;
	
	LPC_TIM0->TCR=0x02;
	LPC_TIM0->PR=0x02;
	LPC_TIM0->CTCR=0x02;
	
	LPC_GPIO1->FIOSET &= (1<<23);
	for(i=0 ; i<25 ; i++);
	LPC_GPIO1->FIOCLR &= (1<<23);
	
	LPC_TIM0->TCR = 0x01;
	
	NVIC_EnableIRQ(EINT0_IRQn);
	
	temp1 = 0xC0;
	lcd_com();
	delay_lcd(800);
	lcd_puts(&msg2[0]);

	while(1);
}
void EINT0_IRQHamdler(void)
{
	unsigned int i ;
	 float dist;
	 char str[100];
	LPC_TIM0->TCR = 0x00;
	i = LPC_TIM0->TC;//we get i in micro seconds
	dist = i*345.5*100;//Considering Velocity of sound in air at room temp at 340 m/s
	dist = dist/1000000;
	sprintf(str , "%.1f" , dist);
	
	temp1 = 0x89;
	lcd_com();
	delay_lcd(800);
	lcd_puts(&str[0]);
	
	LPC_SC->EXTINT = 0x01;
}

void lcd_init(void)
{
		LPC_PINCON->PINSEL1 &= 0xFC003FFF;
	LPC_GPIO0->FIODIR |= dt;
	LPC_GPIO0->FIODIR |= rs;
	LPC_GPIO0->FIODIR |= en;
	clr_ports();
	delay_lcd(3200);
	
	temp2 = (0x30<<19);
	wr_cn();
	delay_lcd(30000);
	
	temp2 = (0x30<<19);
	wr_cn();
	delay_lcd(30000);
	
	temp2 = (0x30<<19);
	wr_cn();
	delay_lcd(30000);
	
	temp2 = (0x20<<19);
	wr_cn();
	delay_lcd(30000);
	
	temp1 = 0x28;
	lcd_com();
	delay_lcd(30000);
	
	temp1 = 0x0C;
	lcd_com();
	delay_lcd(800);
	
	temp1 = 0x06;
	lcd_com();
	delay_lcd(800);
	
	temp1 = 0x01;
	lcd_com();
	delay_lcd(10000);
	
	temp1 = 0x80;
	lcd_com();
	delay_lcd(800);
	
	return;
	
}

void lcd_com(void)
{
		temp2 = temp1 & 0xf0;
	temp2 = temp2<<19;
	wr_cn();
	temp2 = temp1 & 0x0f;
	temp2 = temp2<<23;
	wr_cn();
	delay_lcd(1000);
	return;
}

void wr_cn(void)
{
	clr_ports();
	LPC_GPIO0->FIOPIN =  temp2;
	LPC_GPIO0->FIOCLR = rs;
	LPC_GPIO0->FIOSET = en;
	delay_lcd(25);
	LPC_GPIO0->FIOCLR = en;
	
	return;
}

void lcd_data(void)
{
	temp2 = temp1 & 0xf0;
	temp2 <<= 19;
	wr_dn();
	temp2 = temp1 & 0x0f;
	temp2 <<= 23;
	wr_dn();
	delay_lcd(1000);
}

void wr_dn(void)
{
	clr_ports();
	LPC_GPIO0->FIOPIN =  temp2;
	LPC_GPIO0->FIOSET = rs;
	LPC_GPIO0->FIOSET = en;
	delay_lcd(25);
	LPC_GPIO0->FIOCLR = en;
	
	return;
}

void delay_lcd(unsigned int s)
{
	unsigned int t;
	for(t=0 ; t<s ; t++);
	
	return;
}

void clr_disp(void)
{
	temp1 = 0x01;
	lcd_com();
	delay_lcd(10000);
	
	return;
}
void clr_ports(void)
{
		LPC_GPIO0->FIOCLR = dt;
		LPC_GPIO0->FIOCLR = rs;
		LPC_GPIO0->FIOCLR = en;
	
	return;
}

void lcd_puts(char *buff)
{
		unsigned int i=0;
	while(buff[i] != '\0')
	{
			temp1 = buff[i];
		lcd_data();
		i++;
		if(i==16)
		{
			temp1 = 0xC0;
			lcd_com();
		}
	}
	return;
	
}
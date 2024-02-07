/*
 * fan_controller.c
 *
 *      Author: Ayman_Mostafa
 */
#include "adc.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "dc_motor.h"

int main(void)
{
	uint8 temp=0;
	ADC_ConfigType adc_config;
	//making setting for ADC
	adc_config.ref_volt=INTERNAL_2_56_VOLATAGE_REFERENCE;
	adc_config.prescaler=F_CPU_8;
	adc_config.interrupt_option=DISABLE;
	adc_config.auto_tigger_option=DISABLE;


	LCD_init(); /* initialize LCD driver */
	ADC_init(&adc_config); /* initialize ADC driver */
	DcMotor_Init(); /* initialize DcMotor driver */

	LCD_displayString("   FAN is OFF   ");
	LCD_moveCursor(1,0);
	LCD_displayString("   TEMP =    C  ");

	while(1)
	{
		//calculate the current temperature
		temp = LM35_getTemperature();
		LCD_moveCursor(1,10);
		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}

		if(temp<30)
		{
			LCD_moveCursor(0,10);
			LCD_displayString("OFF");
			DcMotor_Rotate(STOP,0);
		}
		else if(temp<60)
		{
			LCD_moveCursor(0,10);
			LCD_displayString("ON ");
			DcMotor_Rotate(CW,25);
		}
		else if(temp<90)
		{
			LCD_moveCursor(0,10);
			LCD_displayString("ON ");
			DcMotor_Rotate(CW,50);
		}
		else if(temp<120)
		{
			LCD_moveCursor(0,10);
			LCD_displayString("ON ");
			DcMotor_Rotate(CW,75);
		}
		else
		{
			LCD_moveCursor(0,10);
			LCD_displayString("ON ");
			DcMotor_Rotate(CW,100);
		}

	}
}


#include "avr/io.h"
#include "adc.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/*Control ADC Voltage Reference Selection*/
	ADMUX= ( (ADMUX & 0x3F) | ((Config_Ptr->ref_volt & 0x03)<<6));
	/*Control ADC Auto Trigger Enable*/
	ADCSRA=(ADCSRA & ~(1<<ADATE)) | ((Config_Ptr->auto_tigger_option)<<ADATE);
	/*Control ADC Interrupt Flag*/
	ADCSRA=(ADCSRA & ~(1<<ADIF)) | ((Config_Ptr->interrupt_option)<<ADIF);
	/*Control ADC Prescaler Select Bits*/
	ADCSRA= ( (ADCSRA & 0xF8) | (Config_Ptr->prescaler & 0x07) );
	/*Enable ADC(ADEN= 1)*/
	ADCSRA |= (1<<ADEN);

}

uint16 ADC_readChannel(Analog_Channel channe_num)
{
	/*Control ADC Analog Channel*/
	ADMUX= ( (ADMUX & 0xE0) | (channe_num & 0x1F ) );
	/* Start conversion write '1' to ADSC */
	SET_BIT(ADCSRA,ADSC);
	/* Wait for conversion to complete, ADIF becomes '1' */
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	 /* Clear ADIF by write '1' to it :) */
	SET_BIT(ADCSRA,ADIF);
	 /* Read the digital value from the data register */
	return ADC;
}

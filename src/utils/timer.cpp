#include "timer.h"
#include <avr/io.h> 

/* Initialize timer 1, you should not turn the timer on here. Use CTC mode  .*/
void initTimer1(){
    TCCR1A &= ~(1 << WGM10);  // Clear bit WGM10 for CTC mode setup on Timer1
    TCCR1A &= ~(1 << WGM11);  // Clear bit WGM11 for CTC mode setup on Timer1
    TCCR1B |= (1 << WGM12);   // Set bit WGM12 to enable CTC mode
    TCCR1B &= ~(1 << WGM13);  // Clear bit WGM13 to complete CTC mode setting

    //prescalar set to 8
    TCCR1B |= (1 << CS01) | (1 << CS00);
    TCCR1B &= ~(1 << CS02);
	
}

/* This delays the program an amount of microseconds specified by unsigned int delay.
*/
void delayUs(unsigned int delay){
    int prescalar = 8;

    OCR1A = ((0.000001 * 16000000) / prescalar) - 1; // calculate the value to be put in the OCRnA register

    for (unsigned int i = 0; i < delay; i++) {
        // set timer to 0
        TCNT1 = 0;

        // if OCF1A in the TIFR1 register is set, it means that the timer has reached the value in OCR1A
        while (!(TIFR1 & (1 << OCF1A)));

        // clear compare match so that the next compare match can be detected
        TIFR1 |= (1 << OCF1A);
    }
}

/* Initialize timer 0, you should not turn the timer on here.
* You will need to use CTC mode */
void initTimer0(){
    TCCR0A &= ~(1 << WGM00); // Ensure that WGM00 is cleared for CTC Mode
    TCCR0A |= (1 << WGM01); //HIGH WGM01 for the CTC mode
    TCCR0B |= ((1 << CS01) | (1 << CS00)); //set prescaler to 64
    TCCR0B &= ~((1 << CS02) | (1 << WGM02)); //Clear WGM02 for CTC Mode


}

/* This delays the program an amount specified by unsigned int delay.
* Use timer 0. Keep in mind that you need to choose your prescalar wisely
* such that your timer is precise to 1 millisecond and can be used for
* 100-2000 milliseconds
*/
void delayMs(unsigned int delay){
    int prescalar = 64;
    OCR0A = ((0.001 * 16000000)/prescalar)-1; //Using the OCR0A formula in the ppt

    for(unsigned int i = 0; i< delay; i++){ //Runs a loop for delay milliseconds, where each iteration waits for the timer to reach the compare match.
        //Reset counter to 0 before it starts
        TCNT0 = 0;

        // wWile loop wait until ocf0a is set
        // To show compare match happen
        while(!(TIFR0 & (1<<OCF0A)));

        //Clear compare match to reset the timer for the next millisecond
        TIFR0 |= (1<<OCF0A);
    }
   
}
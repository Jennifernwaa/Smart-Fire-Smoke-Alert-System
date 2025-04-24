#include "timer.h"

/* Initialize timer 1, you should not turn the timer on here. Use CTC mode  .*/
void initTimer1(){

    //CTC mode

    //prescalar set to smth
	
}

/* This delays the program an amount of microseconds specified by unsigned int delay.
*/
void delayUs(unsigned int delay){
    // int prescalar = smth;
    // OCR1A = ((0.000001 * 16000000) / prescalar) - 1; // calculate the value to be put in the OCR1A register

    // for (unsigned int i = 0; i < delay; i++) {
    //     // set timer to 0
    //     TCNT1 = 0;

    //     // if OCF1A in the TIFR1 register is set, it means that the timer has reached the value in OCR1A
    //     while (!(TIFR1 & (1 << OCF1A)));

    //     // clear compare match so that the next compare match can be detected
    //     TIFR1 |= (1 << OCF1A);
    // }
}

/* Initialize timer 0, you should not turn the timer on here.
* You will need to use CTC mode */
void initTimer0(){
// Ensure that WGM00 is cleared for CTC Mode
//HIGH WGM01 for the CTC mode
//set prescaler to smth
//Clear WGM02 for CTC Mode

}

/* This delays the program an amount specified by unsigned int delay.
* Use timer 0. Keep in mind that you need to choose your prescalar wisely
* such that your timer is precise to 1 millisecond and can be used for
* 100-2000 milliseconds
*/
void delayMs(unsigned int delay){
// idk abt this
    // int prescalar = 64;
    // OCR0A = ((0.001 * 16000000)/prescalar)-1; //Using the OCR0A formula in the ppt

    // for(unsigned int i = 0; i< delay; i++){ //Runs a loop for delay milliseconds, where each iteration waits for the timer to reach the compare match.

    //     //Reset counter to 0 before it starts
    //     TCNT0 = 0;

    //     // wWile loop wait until ocf0a is set
    //     // To show compare match happen
    //     while(!(TIFR0 & (1<<OCF0A)));

    //     //Clear compare match to reset the timer for the next millisecond
    //     TIFR0 |= (1<<OCF0A);
    // } FROM PREVIOUS LAB
   
}
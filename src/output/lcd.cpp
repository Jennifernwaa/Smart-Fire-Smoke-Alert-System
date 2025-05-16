#include "lcd.h"
#include "utils/timer.h"
#include <util/delay.h>

 * Initializes all pins related to the LCD to be outputs
 */
void initLCDPins(){
  DDRA |= (1<<DDA0) | (1<<DDA1) | (1 << DDA2) | (1 << DDA3);

  // Set RS and E pins as output
  DDRB |= (1<<DDB4)| (1<<DDB6);

} 

void fourBitCommandWithDelay(unsigned char data, unsigned int delay){

  //sets the upper 4 bits of PORTA to match the upper 4 bits of data while preserving the lower 4 bits of PORTA
  PORTA = ((PORTA & 0xF0) | (data & 0xF0));

  //RS should be Low
  PORTB &= ~(1<<PORTB6);

  //Set Enable pin high (start signal for LCD that data is ready)
  PORTB |= (1<<PORTB4);
  delayUs(1);

  //Set Enable pin low (falling edge = LCD reads the data)
  PORTB &= ~(1 << PORTB4);
  delayUs(delay);
}

void eightBitCommandWithDelay(unsigned char command, unsigned int delay) {
  //sends the upper 4 bits of the command to the lower 4 bits of PORTA
    PORTA = ((PORTA & 0xF0) | (command & 0xF0)) >> 4;

    // RS should be low for command
    PORTB &= ~(1 << PORTB6);

    // Enable pin high
    PORTB |= (1 << PORTB4);
    delayUs(1);

    // Enable pin low
    PORTB &= ~(1 << PORTB4);

    // Send the lower 4 bits of the command
    PORTA = (PORTA & 0xF0) | (command & 0x0F);

    // Enable pin high
    PORTB |= (1 << PORTB4);
    delayUs(1);

    // Enable pin low
    PORTB &= ~(1 << PORTB4);
    delayUs(delay);
}

void writeCharacter(unsigned char character){
  //delay is always 46 us
  int delay = 46;

  //2. RS High
  PORTB |= (1 << PORTB6);

  PORTA = ((PORTA & 0xF0) | (character & 0xF0)) >> 4;

  //Toggle Enable pin (high then low) to latch the upper bits
  //high
  PORTB |= (1 << PORTB4);
  delayUs(1);

  //low
  PORTB &= ~(1 << PORTB4);

  //Send the lower 4 bits of the character
  PORTA = (PORTA & 0xF0) | (character & 0x0F);

  ////Toggle Enable pin (high then low) to latch the upper bits
  //pin high
  PORTB |= (1 << PORTB4);
  delayUs(1);

  // Enable pin low
  PORTB &= ~(1 << PORTB4);
  delayUs(delay); 
}

void writeString(const char *string){
  while (*string != '\0') {
    writeCharacter(*string);
    string++;
  }

}

void moveCursor(unsigned char x, unsigned char y){
  unsigned char address;

  // Calculate the address based on x and y
  if (y == 0) {
    address = x;
  } else if (y == 1) {
    address = 0x40 + x;
  } else {
    // Invalid y value, do nothing
    return;
  }

  // Set the DDRAM address command (0x80 | address) and tells the LCD where to move the cursor
  eightBitCommandWithDelay(0x80 | address, 53);
}

void clearDisplay(){
  // Clear display command (0x01) and delay 1500 microseconds
  eightBitCommandWithDelay(0x01, 1500);
}

void initLCDProcedure(){
  // Delay 15 milliseconds
  delayMs(15);
  // Write 0b0011 to DB[7:4] and delay 4100 microseconds/ 4.1 millisecond
  fourBitCommandWithDelay(0x3, 4100);

  // Write 0b0011 to DB[7:4] and delay 100 microseconds
  fourBitCommandWithDelay(0x3, 100);

  // write 0b0011 to DB[7:4] and 100us delay
  fourBitCommandWithDelay(0x3, 100);

  // write 0b0010 to DB[7:4] and 100us delay.
  fourBitCommandWithDelay(0x2, 100);

  // Function set in the command table with 53us delay
  eightBitCommandWithDelay(0x2, 53);
  eightBitCommandWithDelay(0x28, 53);

  // Display off in the command table with 53us delay
  eightBitCommandWithDelay(0x08, 53);

  // Clear display in the command table. Remember the delay is longer!!!
  eightBitCommandWithDelay(0x01, 1500);

  // Entry Mode Set in the command table.
  eightBitCommandWithDelay(0x06, 53);

  // Display ON/OFF Control in the command table.
  eightBitCommandWithDelay(0x0C, 53);

}

void initLCD(){
  initLCDPins();
  initLCDProcedure();
}
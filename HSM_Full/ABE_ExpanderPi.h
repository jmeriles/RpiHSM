/*
================================================
ABElectronics UK Expander Pi
Version 1.1 Updated 21/04/2020
================================================

Required package{
apt-get install libi2c-dev
*/

#ifndef EXPANDERPI_ABE_EXPANDERPI_H_
#define EXPANDERPI_ABE_EXPANDERPI_H_

#endif /* EXPANDERPI_ABE_EXPANDERPI_H_ */

namespace ABElectronics_CPP_Libraries
{
class ExpanderPi
{

public:

/**
* Initialise the Expander Pi Object
*/
ExpanderPi();

/*=================== ADC Methods ===================*/

/**
* Open the ADC SPI bus channel
* This needs to be called before using the DAC
*/
int adc_open();

/**
* Close the ADC SPI bus channel
*/
void adc_close();

/**
* Read the voltage from the ADC
* @param channel - 1 or 2
* @param mode - 0 = Single Ended or 1 = Differential
* @returns between 0V and the reference voltage
*/
double adc_read_voltage(int channel, int mode);

/** 
* Read the raw value from the ADC
* @param channel -  1 to 8
* @param mode -  0 = Single Ended or 1 = Differential
* When in differential mode setting channel to 1 will make IN1 = IN+ and IN2 = IN-
* When in differential mode setting channel to 2 will make IN1 = IN- and IN2 = IN+
* @returns 12 bit value between 0 and 4096
*/
int adc_read_raw(int channel, int mode);

/** 
* Set the reference voltage for the adc
* @param ref - Set this value to be the same as the voltage measured on the Vref pin on the Expander Pi
* If using the on board voltage reference then the value will be 4.096
*/
void adc_set_refvoltage(double ref);


/*=================== DAC Methods ===================*/

/** 
* Open the DAC SPI bus channel
* This needs to be called before using the DAC
*/
int dac_open();

/** 
* Close the DAC SPI bus channel
*/
void dac_close();

/** 
* Set the raw value from the selected channel on the DAC
* @param raw - between 0 and 4095
* @param channel - 1 or 2
* @param gain - 1 or 2  - The output voltage will be between 0 and 2.048V when gain is set to 1,  0 and 4.096V when gain is set to 2
*/
void dac_set_raw(uint16_t raw, int channel, int gain);

/** 
* Set the DAC voltage
* @param voltage - between 0 and 2.048 when gain is set to 1,  0 and 4.096 when gain is set to 2
* @param channel - 1 or 2
* @param gain - 1 or 2
*/
void dac_set_voltage(double voltage, int channel, int gain);


/*=================== IO Methods ===================*/

/** 
* set IO direction for an individual pin
* @param pins - 1 to 16
* @param direction - 1 = input, 0 = output
*/
void io_set_pin_direction(unsigned char pin, unsigned char direction);

/** 
* set direction for an IO port
* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
* @param direction - 1 = input, 0 = output
*/
void io_set_port_direction(unsigned char port, unsigned char direction);

/** 
* set the internal 100K pull-up resistors for an individual pin
* @param pin - 1 to 16
* @param value - 1 = enabled, 0 = disabled
*/
void io_set_pin_pullup(unsigned char pin, unsigned char value);

/** 
* set the internal 100K pull-up resistors for the selected IO port
* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
* @param value - number between 0 and 255 or 0x00 and 0xFF
*/
void io_set_port_pullups(unsigned char port, unsigned char value);

/** 
* write to an individual pin 1 - 16
* @param pin - 1 to 16
* @param value - 0 = logic level low, 1 = logic level high
*/
void io_write_pin(unsigned char pin, unsigned char value);

/** 
* write to all pins on the selected port
* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
* @param value - number between 0 and 255 or 0x00 and 0xFF
*/
void io_write_port(unsigned char port, unsigned char value);

/** 
* read the value of an individual pin
* @param pin - 1 to 16
* @returns - 0 = logic level low, 1 = logic level high
*/
int io_read_pin(unsigned char pin);

/** 
* read all pins on the selected port
* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
* @returns - number between 0 and 255 or 0x00 and 0xFF
*/
char io_read_port(unsigned char port);

/** 
* invert the polarity of the pins on a selected port
* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
* @param polarity - 0 = same logic state of the input pin, 1 = inverted logic	state of the input pin
*/
void io_invert_port(unsigned char port, unsigned char polarity);

/** 
* invert the polarity of the selected pin
* @param pin - 1 to 16
* @param polarity - 0 = same logic state of the input pin, 1 = inverted logic	state of the input pin
*/
void io_invert_pin(unsigned char pin, unsigned char polarity);

/** 
* Set the interrupt pins to be mirrored or for separate ports
* @param value - 1 = The char pins are internally connected, 0 = The char pins are not connected. INTA is associated with PortA and INTB is associated with PortB
*/
void io_mirror_interrupts(unsigned char value);

/** 
* This sets the polarity of the char output pins.
* @param value - 1 = Active-high, 0 = Active-low.
*/
void io_set_interrupt_polarity(unsigned char value);

/** 
* Sets the type of interrupt for each pin on the selected port
* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
* @param value - 1 = interrupt is fired when the pin matches the default value, 0 = the interrupt is fired on state change
*/
void io_set_interrupt_type(unsigned char port, unsigned char value);

/** 
* These bits set the compare value for pins configured for interrupt-on-change on the selected port.
* If the associated pin level is the opposite from the register bit, an interrupt occurs.
* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
* @param value - default state for the port
*/
void io_set_interrupt_defaults(unsigned char port, unsigned char value);

/** 
* Enable interrupts for the pins on the selected port
* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
* @param value - number between 0 and 255 or 0x00 and 0xFF
*/
void io_set_interrupt_on_port(unsigned char port, unsigned char value);

/** 
* Enable interrupts for the selected pin
* @param pin - 1 to 16
* @param value - 0 = interrupt disabled, 1 = interrupt enabled
*/
void io_set_interrupt_on_pin(unsigned char pin, unsigned char value);

/** 
* read the interrupt status for the pins on the selected port
* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
*/
char io_read_interrupt_status(unsigned char port);

/** 
* read the value from the selected port at the time of the last
* interrupt trigger
* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
*/
char io_read_interrupt_capture(unsigned char port);

/** 
* set the interrupts A and B to 0
*/
void io_reset_interrupts();


/*=================== RTC Methods ===================*/

/** 
* Set the date on the RTC
* @param date - struct tm formated date and time
*/
void rtc_set_date(struct tm date);

/** 
* Read the date from the RTC.
* @returns - date as a tm struct
*/
struct tm rtc_read_date();

/** 
* Enable the squarewave output pin
*/
void rtc_enable_output();

/** 
* Disable the squarewave output pin
*/
void rtc_disable_output();

/** 
* Set the squarewave output frequency
* @param frequency - 1 = 1Hz, 2 = 4.096KHz, 3 = 8.192KHz, 4 = 32.768KHz
*/
void rtc_set_frequency(unsigned char frequency);

/** 
* write to the memory on the ds1307.  The ds1307 contains 56 - Byte, battery - backed RAM with Unlimited Writes
* @param address - 0x08 to 0x3F
* @param valuearray - byte array containing data to be written to memory
*/
void rtc_write_memory(unsigned char address, unsigned char *valuearray);

/** 
* read from the memory on the ds1307
* the ds1307 contains 56-Byte, battery-backed RAM with Unlimited Writes
* @param address - 0x08 to 0x3F
* @param length - up to 32 bytes.  length can not exceed the avaiable address space.
*/
unsigned char *rtc_read_memory(unsigned char address, int length);


private:

// SPI Bus Variables
uint8_t mode; // SPI_MODE_0
uint32_t speed; // SPI bus speed

// I2C Bus Variables
int i2cbus;
unsigned char buf[10];
unsigned char writebuffer[60];
unsigned char readbuffer[60];

// ADC Variables

uint8_t adctx[3]; // transmit buffer for the ADC
char adcrx[3]; // receive buffer for the adc;
int adc; // adc object
double adcrefvoltage; // reference voltage for the ADC chip.

// DAC Variables

int dac; // dac object
uint8_t dactx[2];

// IO Variables
char config;
char i2caddress; // I2C address
char port_a_dir; // port a direction
char port_b_dir; // port b direction
char portaval; // port a value
char portbval; // port b value
char porta_pullup; // port a pull-up resistors
char portb_pullup; // port a pull-up resistors
char porta_polarity; // input polarity for port a
char portb_polarity; // input polarity for port b
char intA; // interrupt control for port a
char intB; // interrupt control for port a

// RTC Variables
char rtcConfig;
int rtcCentury;

// Private Members

int read_byte_data(unsigned char address, unsigned char reg);
void read_byte_array(unsigned char address, unsigned char reg, unsigned char length);
void write_byte_data(unsigned char address, unsigned char reg, unsigned char value);
void write_byte_array(unsigned char address, unsigned char buffer[], unsigned char length);
unsigned char bcd_to_dec(unsigned char bcd);
unsigned char dec_to_bcd(unsigned char dec);
char updatebyte(unsigned char byte, unsigned char bit, unsigned char value);
char checkbit(unsigned char byte, unsigned char bit);
};
}

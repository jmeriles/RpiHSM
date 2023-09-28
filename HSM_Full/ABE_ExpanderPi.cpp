/*
================================================
ABElectronics UK Expander Pi
Version 1.1 Updated 21/04/2020
================================================


Required package{
apt-get install libi2c-dev
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <errno.h>
#include <fcntl.h>
#include <cstring>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <linux/i2c-dev.h>
#include <time.h>
#include <unistd.h>

#include "ABE_ExpanderPi.h"


// I2C Bus Definitions

#define fileName "/dev/i2c-1" // change to /dev/i2c-0 if you are using a revision 0002 or 0003 model B

// SPI Bus Definitions
#define adcdevice "/dev/spidev0.0"
#define dacdevice "/dev/spidev0.1"

// IO Definitions
#define IOADDRESS 0x20
#define IODIRA 0x00 // IO direction A - 1= input 0 = output
#define IODIRB 0x01 // IO direction B - 1= input 0 = output
#define IPOLA 0x02 // Input polarity A
#define IPOLB 0x03 // Input polarity B
#define GPINTENA 0x04 // The GPINTEN register controls the interrupt-onchange feature for each pin on port A.
#define GPINTENB 0x05 // The GPINTEN register controls the interrupt-onchange feature for each pin on port B.
#define DEFVALA 0x06 // Default value for port A
#define DEFVALB 0x07 // Default value for port B
#define INTCONA 0x08 // Interrupt control register for port A
#define INTCONB 0x09 // Interrupt control register for port B
#define IOCON 0x0A // see datasheet for configuration register
#define GPPUA 0x0C // pull-up resistors for port A
#define GPPUB 0x0D // pull-up resistors for port B
#define INTFA 0x0E // The INTF register reflects the interrupt condition of any pin that is enabled for interrupts.
#define INTFB 0x0F
#define INTCAPA 0x10 // The INTCAP register captures the GPIO port value at the time the interrupt occurred.
#define INTCAPB 0x11
#define GPIOA 0x12 // data port A
#define GPIOB 0x13 // data port B
#define OLATA 0x14 // output latches A
#define OLATB 0x15 // output latches B

// RTC Definitions
#define RTCADDRESS 0x68
#define SECONDS 0x00
#define MINUTES 0x01
#define HOURS 0x02
#define DAYOFWEEK 0x03
#define DAY 0x04
#define MONTH 0x05
#define YEAR 0x06
#define CONTROL 0x07

#define HI_NIBBLE(b) (((b) >> 4) & 0x0F)
#define LO_NIBBLE(b) ((b) & 0x0F)


using namespace ABElectronics_CPP_Libraries;

/*===============================Public Methods===============================*/

ExpanderPi::ExpanderPi(){
	// SPI Bus Variables
	mode = SPI_MODE_0; // SPI_MODE_0
	speed = 200000; // SPI bus speed

	// ADC Variables

	adctx[0] = 0x01; // transmit buffer for the ADC
	adctx[1] = 0x80;
	adctx[2] = 0x00;
	adcrefvoltage = 4.096; // reference voltage for the ADC chip.

	// IO Variables
	config = 0x22;

	// RTC Variables
	rtcConfig = 0x03;
	rtcCentury = 2000;

	//initialise the MCP32017 IO chip with default values: ports are inputs, pull-up resistors are disabled and ports are not inverted
	write_byte_data(IOADDRESS, IOCON, config);
	portaval = read_byte_data(IOADDRESS, GPIOA);
	portbval = read_byte_data(IOADDRESS, GPIOB);
	write_byte_data(IOADDRESS, IODIRA, (unsigned char)0xFF);
	write_byte_data(IOADDRESS, IODIRB, (unsigned char)0xFF);
	io_set_port_pullups(0, 0x00);
	io_set_port_pullups(1, 0x00);
	io_invert_port(0, 0x00);
	io_invert_port(1, 0x00);

}

/*===================ADC Methods Begin ===================*/

int ExpanderPi::adc_open() {
	/**
	* Open the ADC SPI bus channel
	* This needs to be called before using the DAC
	*/

	// Open SPI device
	if ((adc = open(adcdevice, O_RDWR)) < 0)
		return (0);

	if (ioctl(adc, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1)
		return (0);
	// Set SPI mode
	if (ioctl(adc, SPI_IOC_WR_MODE, &mode) == -1)
		return (0);

	return (1);
}

void ExpanderPi::adc_close() {
	/**
	* Close the ADC SPI bus channel
	*/
	close(adc);
}

double ExpanderPi::adc_read_voltage(int channel, int mode) {
	/**
	* Read the voltage from the ADC
	* @param channel - 1 or 2
	* @param mode - 0 = Single Ended or 1 = Differential
	* @returns between 0V and the reference voltage
	*/
	int rawval = adc_read_raw(channel, mode);
	return ((adcrefvoltage / 4096) * (double)rawval);
}

int ExpanderPi::adc_read_raw(int channel, int mode) {
	/**
	* Read the raw value from the ADC
	* @param channel -  1 to 8
	* @param mode -  0 = Single Ended or 1 = Differential
	* When in differential mode setting channel to 1 will make IN1 = IN+ and IN2 = IN-
	* When in differential mode setting channel to 2 will make IN1 = IN- and IN2 = IN+
	* @returns 12 bit value between 0 and 4096
	*/

	channel = channel - 1;
	if (mode == 0) {
		adctx[0] = 6 + (channel >> 2);
		adctx[1] = (channel & 3) << 6;
	}
	else if (mode == 1) {
		adctx[0] = 4 + (channel >> 2);
		adctx[1] = (channel & 3) << 6;
	}
	else {
		return (0);
	}

	struct spi_ioc_transfer spi;
	memset(&spi,0,sizeof(spi));

	spi.tx_buf = (unsigned long)adctx;
	spi.rx_buf = (unsigned long)adcrx;
	spi.len = 3;
	spi.speed_hz = 1800000; // 1.8MHz Clock Speed
	spi.delay_usecs = 0;
	spi.bits_per_word = 8;


	if (ioctl(adc, SPI_IOC_MESSAGE(1), &spi) == -1){
		return(0);
	}
	else{
		return (((adcrx[1] & 0x0F) << 8) + (adcrx[2]));
	}
}

void ExpanderPi::adc_set_refvoltage(double ref) {
	/**
	* Set the reference voltage for the adc
	* @param ref - Set this value to be the same as the voltage measured on the Vref pin on the Expander Pi
	* If using the on board voltage reference then the value will be 4.096
	*/
	adcrefvoltage = ref;
}

/*===================ADC Methods END ===================*/

/*===================DAC Methods Begin ===================*/

int ExpanderPi::dac_open() {
	/**
	* Open the DAC SPI bus channel
	* This needs to be called before using the DAC
	*/

	// Open SPI device
	if ((dac = open(dacdevice, O_RDWR)) < 0)
		return (0);

	if (ioctl(dac, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1)
		return (0);
	// Set SPI mode
	if (ioctl(dac, SPI_IOC_WR_MODE, &mode) == -1)
		return (0);

	return (1);
}

void ExpanderPi::dac_close() {
	/**
	* Close the DAC SPI bus channel
	*/
	close(dac);
}

void ExpanderPi::dac_set_raw(uint16_t raw, int channel, int gain) {
	/**
	* Set the raw value from the selected channel on the DAC
	* @param raw - between 0 and 4095
	* @param channel - 1 or 2
	* @param gain - 1 or 2  - The output voltage will be between 0 and 2.048V when gain is set to 1,  0 and 4.096V when gain is set to 2
	*/

	uint8_t dactx[2];

	dactx[1] = (raw & 0xff);

	if (gain == 1) {
		dactx[0] = (((raw >> 8) & 0xff) | (channel - 1) << 7 | 1 << 5 | 1 << 4);
    }
	else if (gain == 2) {
		dactx[0] = (((raw >> 8) & 0xff) | (channel - 1) << 7 | 1 << 4);
	}
	else {
		throw std::out_of_range("dac_set_raw gain out of range: 1 or 2");
	}

	struct spi_ioc_transfer tr;
    memset(&tr,0,sizeof(tr));

	tr.tx_buf = (unsigned long)&dactx;
	tr.rx_buf = (unsigned long)NULL;
	tr.len = 2;
	tr.speed_hz = 20000000; // 20MHz clock speed
	tr.delay_usecs = 0;
	tr.bits_per_word = 8;
	tr.cs_change = 0;

	// Write data
	if (ioctl(dac, SPI_IOC_MESSAGE(1), &tr) == -1){
		throw std::runtime_error("error setting dac raw value");
	}

	return;
}

void ExpanderPi::dac_set_voltage(double voltage, int channel, int gain) {
	/**
	* Set the DAC voltage
	* @param voltage - between 0 and 2.048 when gain is set to 1,  0 and 4.096 when gain is set to 2
	* @param channel - 1 or 2
	* @param gain - 1 or 2
	*/
	double dacvoltage = 2.048;

	if (gain == 2) {
		dacvoltage = 4.096;
	}

	if ((voltage >= 0.0) && (voltage < dacvoltage)) {
		uint16_t rawval = (voltage / 2.048) * 4096 / gain;
		dac_set_raw(rawval, channel, gain);
	}
	else {
		throw std::out_of_range("dac_set_voltage voltage out of range");
	}
}


/*===================DAC Methods END ===================*/

/*===================IO Methods Begin ===================*/

void ExpanderPi::io_set_pin_direction(unsigned char pin,unsigned char direction) {
	/**
	* set IO direction for an individual pin
	* @param pins - 1 to 16
	* @param direction - 1 = input, 0 = output
	*/
	pin = pin - 1;
	if (pin < 8)
	{
		port_a_dir = updatebyte(port_a_dir, pin, direction);
		write_byte_data(IOADDRESS, IODIRA, port_a_dir);
	}
	else if (pin >= 8 && pin < 16)
	{
		port_b_dir = updatebyte(port_b_dir, pin - 8, direction);
		write_byte_data(IOADDRESS, IODIRB, port_b_dir);
	}
	else{
		throw std::out_of_range("set_pin_direction pin out of range: 1 to 16");
	}
}

void ExpanderPi::io_set_port_direction(unsigned char port, unsigned char direction) {
	/**
	* set direction for an IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param direction - 1 = input, 0 = output
	*/
	if (port == 0)
	{
		write_byte_data(IOADDRESS, IODIRA, direction);
		port_a_dir = direction;
	}
	else if (port == 1)
	{
		write_byte_data(IOADDRESS, IODIRB, direction);
		port_b_dir = direction;
	}
	else{
		throw std::out_of_range("set_port_direction port out of range: 0 or 1");
	}

}

void ExpanderPi::io_set_pin_pullup(unsigned char pin, unsigned char value) {
	/**
	* set the internal 100K pull-up resistors for an individual pin
	* @param pin - 1 to 16
	* @param value - 1 = enabled, 0 = disabled
	*/
	pin = pin - 1;
	if (pin < 8)
	{
		porta_pullup = updatebyte(porta_pullup, pin, value);
		write_byte_data(IOADDRESS, GPPUA, porta_pullup);
	}
	else if (pin >= 8 && pin < 16)
	{
		portb_pullup = updatebyte(portb_pullup, pin - 8, value);
		write_byte_data(IOADDRESS, GPPUB, portb_pullup);
	}
	else{
		throw std::out_of_range("set_pin_pullup pin out of range: 1 to 16");
	}
}

void ExpanderPi::io_set_port_pullups(unsigned char port, unsigned char value) {
	/**
	* set the internal 100K pull-up resistors for the selected IO port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - number between 0 and 255 or 0x00 and 0xFF
	*/
	if (port == 0)
	{
		porta_pullup = value;
		write_byte_data(IOADDRESS, GPPUA, value);
	}
	else if (port == 1)
	{
		portb_pullup = value;
		write_byte_data(IOADDRESS, GPPUB, value);
	}
	else{
		throw std::out_of_range("set_port_pullups port out of range: 0 or 1");
	}
}

void ExpanderPi::io_write_pin(unsigned char pin, unsigned char value) {
	/**
	* write to an individual pin 1 - 16
	* @param pin - 1 to 16
	* @param value - 0 = logic level low, 1 = logic level high
	*/
	pin = pin - 1;
	if (pin < 8)
	{
		portaval = updatebyte(portaval, pin, value);
		write_byte_data(IOADDRESS, GPIOA, portaval);
	}
	else if (pin >= 8 && pin < 16)
	{
		portbval = updatebyte(portbval, pin - 8, value);
		write_byte_data(IOADDRESS, GPIOB, portbval);
	}
	else{
		throw std::out_of_range("write_pin pin out of range: 1 to 16");
	}
}

void ExpanderPi::io_write_port(unsigned char port, unsigned char value) {
	/**
	* write to all pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - number between 0 and 255 or 0x00 and 0xFF
	*/
	if (port == 0)
	{
	write_byte_data(IOADDRESS, GPIOA, value);
	portaval = value;
	}
	else if (port == 1)
	{
	write_byte_data(IOADDRESS, GPIOB, value);
	portbval = value;
	}
	else{
		throw std::out_of_range("write_port port out of range: 0 or 1");
	}
}

int ExpanderPi::io_read_pin(unsigned char pin) {
	/**
	* read the value of an individual pin
	* @param pin - 1 to 16
	* @returns - 0 = logic level low, 1 = logic level high
	*/
	pin = pin - 1;
	if (pin < 8)
	{
		portaval = read_byte_data(IOADDRESS, GPIOA);
		return (checkbit(portaval, pin));
	}
	else if (pin >= 8 && pin < 16)
	{
		pin = pin - 8;
		portbval = read_byte_data(IOADDRESS, GPIOB);
		return (checkbit(portbval, pin));
	}
	else{
		throw std::out_of_range("read_pin pin out of range: 1 to 16");
	}
}

char ExpanderPi::io_read_port(unsigned char port) {
	/**
	* read all pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @returns - number between 0 and 255 or 0x00 and 0xFF
	*/
	if (port == 0)
	{
		portaval = read_byte_data(IOADDRESS, GPIOA);
		return (portaval);
	}
	else if (port == 1)
	{
		portbval = read_byte_data(IOADDRESS, GPIOB);
		return (portbval);
	}
	else{
		throw std::out_of_range("read_port port out of range: 0 or 1");
	}
}

void ExpanderPi::io_invert_port(unsigned char port, unsigned char polarity) {
	/**
	* invert the polarity of the pins on a selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param polarity - 0 = same logic state of the input pin, 1 = inverted logic	state of the input pin
	*/
	if (port == 0)
	{
		write_byte_data(IOADDRESS, IPOLA, polarity);
		porta_polarity = polarity;
	}
	else if (port == 1)
	{
		write_byte_data(IOADDRESS, IPOLB, polarity);
		portb_polarity = polarity;
	}
	else{
		throw std::out_of_range("invert_port port out of range: 0 or 1");
	}
}

void ExpanderPi::io_invert_pin(unsigned char pin, unsigned char polarity) {
	/**
	* invert the polarity of the selected pin
	* @param pin - 1 to 16
	* @param polarity - 0 = same logic state of the input pin, 1 = inverted logic	state of the input pin
	*/
	pin = pin - 1;
	if (pin < 8)
	{

		porta_polarity = updatebyte(porta_polarity, pin, polarity);
		write_byte_data(IOADDRESS, IPOLA, porta_polarity);
	}
	else if (pin >= 8 && pin < 16)
	{
		portb_polarity = updatebyte(portb_polarity, pin - 8, polarity);
		write_byte_data(IOADDRESS, IPOLB, portb_polarity);
	}
	else{
		throw std::out_of_range("invert_pin pin out of range: 1 to 16");
	}
}

void ExpanderPi::io_mirror_interrupts(unsigned char value) {
	/**
	* Set the interrupt pins to be mirrored or for separate ports
	* @param value - 1 = The char pins are internally connected, 0 = The char pins are not connected. INTA is associated with PortA and INTB is associated with PortB
	*/
	if (value == 0)
	{
		config = updatebyte(config, 6, 0);
		write_byte_data(IOADDRESS, IOCON, config);
	}
	else if (value == 1)
	{
		config = updatebyte(config, 6, 1);
		write_byte_data(IOADDRESS, IOCON, config);
	}
	else{
		throw std::out_of_range("mirror_interrupts value out of range: 0 or 1");
	}
}

void ExpanderPi::io_set_interrupt_polarity(unsigned char value) {
	/**
	* This sets the polarity of the char output pins.
	* @param value - 1 = Active-high, 0 = Active-low.
	*/
	if (value == 0)
	{
		config = updatebyte(config, 1, 0);
		write_byte_data(IOADDRESS, IOCON, config);
	}
	else if (value == 1)
	{
		config = updatebyte(config, 1, 1);
		write_byte_data(IOADDRESS, IOCON, config);
	}
	else{
		throw std::out_of_range("set_interrupt_polarity value out of range: 0 or 1");
	}
}

void ExpanderPi::io_set_interrupt_type(unsigned char port, unsigned char value) {
	/**
	* Sets the type of interrupt for each pin on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - 1 = interrupt is fired when the pin matches the default value, 0 = the interrupt is fired on state change
	*/
	if (port == 0)
	{
		write_byte_data(IOADDRESS, INTCONA, value);
	}
	else if (port == 1)
	{
		write_byte_data(IOADDRESS, INTCONB, value);
	}
	else{
		throw std::out_of_range("set_interrupt_type port out of range: 0 or 1");
	}
}

void ExpanderPi::io_set_interrupt_defaults(unsigned char port, unsigned char value) {
	/**
	* These bits set the compare value for pins configured for interrupt-on-change on the selected port.
	* If the associated pin level is the opposite from the register bit, an interrupt occurs.
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - default state for the port
	*/
	if (port == 0)
	{
		write_byte_data(IOADDRESS, DEFVALA, value);
	}
	else if (port == 1)
	{
		write_byte_data(IOADDRESS, DEFVALB, value);
	}
	else{
		throw std::out_of_range("set_interrupt_defaults port out of range: 0 or 1");
	}
}

void ExpanderPi::io_set_interrupt_on_port(unsigned char port, unsigned char value) {
	/**
	* Enable interrupts for the pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	* @param value - number between 0 and 255 or 0x00 and 0xFF
	*/
	if (port == 0)
	{
		write_byte_data(IOADDRESS, GPINTENA, value);
		intA = value;
	}
	else if (port == 1)
	{
		write_byte_data(IOADDRESS, GPINTENB, value);
		intB = value;
	}
	else{
		throw std::out_of_range("set_interrupt_on_port port out of range: 0 or 1");
	}
}

void ExpanderPi::io_set_interrupt_on_pin(unsigned char pin, unsigned char value) {
	/**
	* Enable interrupts for the selected pin
	* @param pin - 1 to 16
	* @param value - 0 = interrupt disabled, 1 = interrupt enabled
	*/
	pin = pin - 1;
	if (pin < 8)
	{
		intA = updatebyte(intA, pin, value);
		write_byte_data(IOADDRESS, GPINTENA, intA);
	}
	else if (pin >= 8 && pin < 16)
	{
		intB = updatebyte(intB, pin - 8, value);
		write_byte_data(IOADDRESS, GPINTENB, intB);
	}
	else{
		throw std::out_of_range("set_interrupt_on_pin pin out of range: 1 to 16");
	}
}

char ExpanderPi::io_read_interrupt_status(unsigned char port) {
	/**
	* read the interrupt status for the pins on the selected port
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
	if (port == 0)
	{
		return (read_byte_data(IOADDRESS, INTFA));
	}
	else if (port == 1)
	{
		return (read_byte_data(IOADDRESS, INTFB));
	}
	else{
		throw std::out_of_range("read_interrupt_status port out of range: 0 or 1");
	}
}

char ExpanderPi::io_read_interrupt_capture(unsigned char port) {
	/**
	* read the value from the selected port at the time of the last interrupt trigger
	* @param port - 0 = pins 1 to 8, port 1 = pins 9 to 16
	*/
	if (port == 0)
	{
		return (read_byte_data(IOADDRESS, INTCAPA));
	}
	else if (port == 1)
	{
		return (read_byte_data(IOADDRESS, INTCAPB));
	}
	else{
		throw std::out_of_range("read_interrupt_capture port out of range: 0 or 1");
	}
}

void ExpanderPi::io_reset_interrupts() {
	/**
	* set the interrupts A and B to 0
	*/
	io_read_interrupt_capture(0);
	io_read_interrupt_capture(1);
}

/*===================IO Methods END ===================*/

/*===================RTC Methods Begin ===================*/


void ExpanderPi::rtc_set_date(struct tm date) {
	/**
	* Set the date on the RTC
	* @param date - struct tm formated date and time
	*/
	writebuffer[0] = SECONDS; // register address for seconds
	writebuffer[1] = dec_to_bcd(date.tm_sec); // seconds
	writebuffer[2] = dec_to_bcd(date.tm_min); // minutes
	writebuffer[3] = dec_to_bcd(date.tm_hour);// hours
	writebuffer[4] = dec_to_bcd(date.tm_wday);// dayofweek
	writebuffer[5] = dec_to_bcd(date.tm_mday);// day
	writebuffer[6] = dec_to_bcd(date.tm_mon) + 1;// month
	writebuffer[7] = dec_to_bcd(date.tm_year % 100); // strip the century from the date

	write_byte_array(RTCADDRESS, writebuffer, 8);
}

struct tm ExpanderPi::rtc_read_date() {
	/**
	* Read the date from the RTC.
	* @returns - date as a tm struct
	*/

	read_byte_array(RTCADDRESS, 0, 7);
	struct tm date;
	date.tm_sec = bcd_to_dec(readbuffer[0]); // seconds
	date.tm_min = bcd_to_dec(readbuffer[1]); // minutes
	date.tm_hour = bcd_to_dec(readbuffer[2]);// hours
	date.tm_wday = bcd_to_dec(readbuffer[3]);// dayofweek
	date.tm_mday = bcd_to_dec(readbuffer[4]);// day
	date.tm_mon = bcd_to_dec(readbuffer[5]) - 1;// month
	date.tm_year = bcd_to_dec(readbuffer[6]) + (rtcCentury - 1900);// year

	return date;
}

void ExpanderPi::rtc_enable_output() {
	/**
	* Enable the squarewave output pin
	*/
	rtcConfig = updatebyte(rtcConfig, 7, 1);
	rtcConfig = updatebyte(rtcConfig, 4, 1);
	write_byte_data(RTCADDRESS, CONTROL, rtcConfig);
}

void ExpanderPi::rtc_disable_output() {
	/**
	* Disable the squarewave output pin
	*/
	rtcConfig = updatebyte(rtcConfig, 7, 0);
	rtcConfig = updatebyte(rtcConfig, 4, 0);
	write_byte_data(RTCADDRESS, CONTROL, rtcConfig);
}

void ExpanderPi::rtc_set_frequency(unsigned char frequency) {
	/**
	* Set the squarewave output frequency
	* @param frequency - 1 = 1Hz, 2 = 4.096KHz, 3 = 8.192KHz, 4 = 32.768KHz
	*/
	switch (frequency) {
	case 1:
		rtcConfig = updatebyte(rtcConfig, 0, 0);
		rtcConfig = updatebyte(rtcConfig, 1, 0);
		write_byte_data(RTCADDRESS, CONTROL, rtcConfig);
		break;
	case 2:
		rtcConfig = updatebyte(rtcConfig, 0, 1);
		rtcConfig = updatebyte(rtcConfig, 1, 0);
		write_byte_data(RTCADDRESS, CONTROL, rtcConfig);
		break;
	case 3:
		rtcConfig = updatebyte(rtcConfig, 0, 0);
		rtcConfig = updatebyte(rtcConfig, 1, 1);
		write_byte_data(RTCADDRESS, CONTROL, rtcConfig);
		break;
	case 4:
		rtcConfig = updatebyte(rtcConfig, 0, 1);
		rtcConfig = updatebyte(rtcConfig, 1, 1);
		write_byte_data(RTCADDRESS, CONTROL, rtcConfig);
		break;
	default:
		throw std::out_of_range("Error: set_frequency() - value must be between 1 and 4");

	}
}

void ExpanderPi::rtc_write_memory(unsigned char address, unsigned char *valuearray) {
	/**
	* write to the memory on the ds1307
	* the ds1307 contains 56 - Byte, battery - backed RAM with Unlimited Writes
	* @param address - 0x08 to 0x3F
	* @param valuearray - byte array containing data to be written to memory
	*/

	if (address >= 0x08 && address <= 0x3F) {
		if (address + sizeof(valuearray) <= 0x3F) {

			int length = sizeof(valuearray);

			unsigned char *writearray = (unsigned char*)malloc(length + 1);

			if (errno == ENOMEM) { // Fail!!!!
				free(writearray);
				throw std::runtime_error("memory allocation error: not enough system memory to allocate array");
			}
			else {

				writearray[0] = address;

				int a;
				for (a = 0; a < length; a++) {
					writearray[a + 1] = valuearray[a];
				}

				write_byte_array(RTCADDRESS, writearray, (unsigned char)length + 1);

				free(writearray);
			}

		}
		else {
			throw std::runtime_error("memory overflow error: address + length exceeds 0x3F");
		}
	}
	else{
		throw std::out_of_range("address out of range");
	}
}

unsigned char *ExpanderPi::rtc_read_memory(unsigned char address, int length) {
	/**
	* read from the memory on the ds1307
	* the ds1307 contains 56-Byte, battery-backed RAM with Unlimited Writes
	* @param address - 0x08 to 0x3F
	* @param length - up to 32 bytes.  length can not exceed the avaiable address space.
	* @returns - pointer to a byte array where the data will be saved
	*/

	if (address >= 0x08 && address <= 0x3F) {
		if (address <= (0x3F - length)) {

			unsigned char *writearray = (unsigned char*)malloc(length);

			if (errno == ENOMEM) { // Fail!!!!
				free(writearray);
				throw std::runtime_error("memory allocation error: not enough system memory to allocate array");
				return NULL;
			}
			else {
				read_byte_array(RTCADDRESS, address, length); // read the values from the SRAM into the read buffer

				// copy the read buffer into the writearray
				int i = 0;
				for (i = 0; i < length; i++) {
					writearray[i] = readbuffer[i];
				}

				return writearray;
			}

		}
		else {
			throw std::runtime_error("memory overflow error: address + length exceeds 0x3F");
			return NULL;
		}
	}
	else {
		throw std::out_of_range("address out of range");
		return NULL;
	}
}

/*===================RTC Methods End ===================*/


/*===================Local Methods===================*/

// stops file handle leakage on exceptions
class ScopedFileHandle{
public:
    ScopedFileHandle(int fd) :_fd(fd){}
    ~ScopedFileHandle(){ if(_fd >= 0) close(_fd); }
    operator int() const { return _fd; }
private:
    int _fd;
};

int ExpanderPi::read_byte_data(unsigned char address, unsigned char reg) {
	/*
	internal method for reading data from the i2c bus
	*/
	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
    if (i2cbus < 0)
	{
		throw std::runtime_error("read_byte_data: Failed to open i2c port for read");
	}

	if (ioctl(i2cbus, I2C_SLAVE, address) < 0)
	{
		throw std::runtime_error("read_byte_data: Failed to write to i2c port for read");
	}

	buf[0] = reg;

	if ((write(i2cbus, buf, 1)) != 1)
	{
		throw std::runtime_error("read_byte_data: Failed to write to i2c device for read");
	}

	if (read(i2cbus, buf, 1) != 1)
	{ // Read back data into buf[]
		throw std::runtime_error("read_byte_data: Failed to read from slave");
	}

	close(i2cbus);

	return (buf[0]);
}

void ExpanderPi::read_byte_array(unsigned char address, unsigned char reg, unsigned char length) {
	/*
	internal method for reading data from the i2c bus
	*/
	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
    if (i2cbus < 0)
	{
		throw std::runtime_error("read_byte_array: Failed to open i2c port for read");
	}

	if (ioctl(i2cbus, I2C_SLAVE, address) < 0)
	{
		throw std::runtime_error("read_byte_array: Failed to write to i2c port for read");
	}

	buf[0] = reg;

	if ((write(i2cbus, buf, 1)) != 1)
	{
		throw std::runtime_error("read_byte_array: Failed to write to i2c device for read");
	}

	read(i2cbus, readbuffer, length);

	close(i2cbus);
}

void ExpanderPi::write_byte_data(unsigned char address, unsigned char reg, unsigned char value) {
	/**
	* private method for writing a byte to the I2C port
	*/
    ScopedFileHandle i2cbus(open(fileName, O_RDWR));
    if (i2cbus < 0)
	{
		throw std::runtime_error("write_byte_data: Failed to open i2c port for write");
	}

	if (ioctl(i2cbus, I2C_SLAVE, address) < 0)
	{
		throw std::runtime_error("write_byte_data: Failed to write to i2c port for write");
	}

	buf[0] = reg;
	buf[1] = value;

	if ((write(i2cbus, buf, 2)) != 2)
	{
		throw std::runtime_error("write_byte_data: Failed to write to i2c device for write");
	}

	close(i2cbus);
}

void ExpanderPi::write_byte_array(unsigned char address, unsigned char buffer[], unsigned char length) {
	/*
	internal method for writing data to the i2c bus
	*/

	ScopedFileHandle i2cbus(open(fileName, O_RDWR));
    if (i2cbus < 0)
	{
		throw std::runtime_error("write_byte_array: Failed to open i2c port for write");
	}

	if (ioctl(i2cbus, I2C_SLAVE, address) < 0)
	{
		throw std::runtime_error("write_byte_array: Failed to write to i2c port for write");
	}

	if ((write(i2cbus, buffer, length)) != length) {
		throw std::runtime_error("write_byte_array: Failed to write to i2c device for write");
		exit(1);
	}

	close(i2cbus);
}

unsigned char ExpanderPi::bcd_to_dec(unsigned char bcd) {
	// internal method for converting a bcd formatted number to decimal
	return (unsigned char)((HI_NIBBLE(bcd) * 10) + (LO_NIBBLE(bcd)));
}

unsigned char ExpanderPi::dec_to_bcd(unsigned char dec) {
	// internal method for converting a decimal formatted number to bcd
	return (unsigned char)((dec / 10) * 16) + (dec % 10);
}

char ExpanderPi::updatebyte(unsigned char byte, unsigned char bit, unsigned char value) {
	// internal method for setting the value of a single bit within a byte
	if (value == 0) {
		return (byte &= ~(1 << bit));

	}
	else {
		return (byte |= 1 << bit);
	}

}

char ExpanderPi::checkbit(unsigned char byte, unsigned char bit) {
	// internal method for reading the value of a single bit within a byte
	if (byte & (1 << bit)) {
		return (1);
	}
	else {
		return (0);
	}
}
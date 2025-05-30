
#include "stm32f4xx.h"

#ifndef I2C_LCD_H_
#define I2C_LCD_H_

void lcd_init(void);				// initialize lcd
void lcd_send_cmd(char cmd);		// send command to the lcd
void lcd_send_data(char data);		// send data to the lcd
void lcd_send_string(char *str);	// send string to the lcd

#endif

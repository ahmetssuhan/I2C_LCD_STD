# STM32F407G-DISC1 I2C LCD Example

This project demonstrates how to use the I2C peripheral of the STM32F407G-DISC1 board to communicate with a 16x2 character LCD display via an I2C backpack module (like PCF8574).

## Features

- Initializes I2C1 on PB6 (SCL) and PB7 (SDA)
- Sends data to the LCD using a custom I2C LCD driver (`i2c-lcd.h`)
- Displays the word "MERHABA" character by character on both lines of the LCD
- Uses manual delay loops between characters for timing

## Hardware

- STM32F407G-DISC1 board
- I2C 16x2 LCD display with I2C backpack (e.g., PCF8574)
- USB connection for power and programming

## Project Structure

- `main.c`: Main application file containing GPIO/I2C initialization and LCD control logic
- `i2c-lcd.h`: LCD control header (assumed to be present)
- `LICENSE`: License file
- `README.md`: This file

## How It Works

1. `GPIO_Config()` sets PB6 and PB7 to alternate function mode for I2C1.
2. `I2C_Config()` initializes I2C1 with 400kHz clock speed and 7-bit addressing.
3. `lcd_init()` initializes the LCD module (must be defined in `i2c-lcd.h`).
4. Inside the main loop, characters are sent to specific positions on the LCD with delay.
5. The screen is cleared after displaying both lines.

## Dependencies

- STM32F4 Standard Peripheral Library
- STM32F4 Discovery Board support headers
- Custom LCD driver (`i2c-lcd.h` and `i2c-lcd.c` if needed)

## License

This project is licensed under the terms of the included `LICENSE` file.(MIT License if you want to use you can use whenever you want)

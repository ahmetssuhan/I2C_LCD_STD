#include "i2c-lcd.h"

extern I2C_InitTypeDef I2C_InitStruct;  // I2C yapılandırma değişkeni (başka yerde tanımlı)

// LCD'nin I2C adresi (8-bit format, son biti R/W = 0 yani yazma)
uint8_t myDeviceAddress = 0x4E;

// Özel Türkçe karakter ve sembol tanımları (8x8 piksel)
unsigned char karakter_[8][8]=
{
	/* Türkçe karakterler */
	{0,14,16,16,17,14, 4, 0}, // Ç
	{0, 0,12, 4, 4, 4,14, 0}, // I
	{10, 0,14,17,17,17,14, 0}, // Ö
	{0,15,16,14, 1,30, 4, 0},  // Ş
	{10, 0,17,17,17,17,14, 0}, // Ü

	/* Özel semboller */
	{2, 6,14,30,14, 6, 2, 0},  // ok (↑ veya benzeri)
	{0, 4, 4, 4, 4, 4, 4, 0},  // dik çizgi (|)
	{0,16, 8, 4, 2, 1, 0, 0}   // ters eğik çizgi (\)
};

// LCD başlatma fonksiyonu
void lcd_init(void)
{
	lcd_send_cmd(0x02); // LCD imleci başlangıç pozisyonuna getir (home)
	lcd_send_cmd(0x28); // 4-bit mod, 2 satır, 5x8 nokta formatı
	lcd_send_cmd(0x0D); // Ekranı aç, imleç kapalı, imleç yanıp sönüyor
	lcd_send_cmd(0x80); // 1. satırın başına git
}

// LCD'ye komut gönderen fonksiyon
void lcd_send_cmd(char cmd)
{
	char data_u, data_l;
	uint8_t data_t[4];

	/*
	Komut gönderimi 4-bit modda iki aşamalıdır:
	1. Yüksek 4 bit (MSB) gönderilir.
	2. Düşük 4 bit (LSB) gönderilir.
	RS = 0 (komut), EN sinyali ile tetikleme yapılır.
	*/

	data_u = (cmd & 0xF0);         // Yüksek 4 bit
	data_l = ((cmd << 4) & 0xF0);  // Düşük 4 bit

	// Yüksek 4 bit gönderimi
	data_t[0] = data_u | 0x0C;     // EN=1, RS=0
	I2C_Write(myDeviceAddress, data_t[0]);
	data_t[1] = data_u | 0x08;     // EN=0, RS=0
	I2C_Write(myDeviceAddress, data_t[1]);

	// Düşük 4 bit gönderimi
	data_t[2] = data_l | 0x0C;     // EN=1, RS=0
	I2C_Write(myDeviceAddress, data_t[2]);
	data_t[3] = data_l | 0x08;     // EN=0, RS=0
	I2C_Write(myDeviceAddress, data_t[3]);
}

// LCD'ye veri (karakter) gönderen fonksiyon
void lcd_send_data(char data)
{
	char data_u, data_l;
	uint8_t data_t[4];

	/*
	Veri gönderimi de komut gibi 4-bit modda yapılır.
	Bu kez RS = 1 (veri modu), yine EN sinyali ile tetikleme yapılır.
	*/

	data_u = (data & 0xF0);         // Yüksek 4 bit
	data_l = ((data << 4) & 0xF0);  // Düşük 4 bit

	// Yüksek 4 bit gönderimi
	data_t[0] = data_u | 0x0D;      // EN=1, RS=1
	I2C_Write(myDeviceAddress, data_t[0]);
	data_t[1] = data_u | 0x09;      // EN=0, RS=1
	I2C_Write(myDeviceAddress, data_t[1]);

	// Düşük 4 bit gönderimi
	data_t[2] = data_l | 0x0D;      // EN=1, RS=1
	I2C_Write(myDeviceAddress, data_t[2]);
	data_t[3] = data_l | 0x09;      // EN=0, RS=1
	I2C_Write(myDeviceAddress, data_t[3]);
}

// LCD'ye string (metin) gönderme fonksiyonu
void lcd_send_string(char *str)
{
	while(*str)
		lcd_send_data(*str++);
}

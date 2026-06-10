
#ifndef SRC_DS3231_H_
#define SRC_DS3231_H_
#include "main.h"

#define DS3231_ADDR 0x68

typedef struct {
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}Date;


uint8_t BCD2dec(uint8_t BCD);

uint8_t dec2BCD(uint8_t dec);

void RTC_init(Date *date,uint8_t sec,uint8_t min,uint8_t hour,uint8_t day,uint8_t date_,uint8_t month,uint8_t year);

void RTC_write_data(I2C_HandleTypeDef *hi2c, Date *date, uint16_t RTC_ADDR);

uint8_t RTC_read_data(I2C_HandleTypeDef *hi2c, Date *date, uint16_t RTC_ADDR);


#endif /* SRC_DS3231_H_ */

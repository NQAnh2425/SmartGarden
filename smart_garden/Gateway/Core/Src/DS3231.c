#include "DS3231.h"


uint8_t BCD2dec(uint8_t BCD){
	return (BCD&0x0F)+((BCD>>4)&0x0F)*10;
}

uint8_t dec2BCD(uint8_t dec){
	return ((dec/10)<<4)|(dec%10);
}

void RTC_init(Date *date,uint8_t sec,uint8_t min,uint8_t hour,uint8_t day,uint8_t date_,uint8_t month,uint8_t year)
{
    date->sec   = sec;
    date->min   = min;
    date->hour  = hour;
    date->day   = day;
    date->date  = date_;
    date->month = month;
    date->year  = year;
}

void RTC_write_data(I2C_HandleTypeDef *hi2c, Date *date, uint16_t RTC_ADDR)
{
    uint8_t data[7];

    data[0] = dec2BCD(date->sec);
    data[1] = dec2BCD(date->min);
    data[2] = dec2BCD(date->hour);
    data[3] = dec2BCD(date->day);
    data[4] = dec2BCD(date->date);
    data[5] = dec2BCD(date->month);
    data[6] = dec2BCD(date->year);

    HAL_I2C_Mem_Write(hi2c, (RTC_ADDR<<1)|0x01,0x00,I2C_MEMADD_SIZE_8BIT,data,7,100);
}

uint8_t RTC_read_data(I2C_HandleTypeDef *hi2c, Date *date, uint16_t RTC_ADDR)
{
    uint8_t data_rx[7];
    if(HAL_I2C_IsDeviceReady(hi2c, RTC_ADDR<<1, 3, 1000)==HAL_OK){
    HAL_I2C_Mem_Read(hi2c, (RTC_ADDR<<1)&0xFE,0x00,I2C_MEMADD_SIZE_8BIT,data_rx,7,100);

    date->sec   = BCD2dec(data_rx[0]);
    date->min   = BCD2dec(data_rx[1]);
    date->hour  = BCD2dec(data_rx[2]);
    date->day   = BCD2dec(data_rx[3]);
    date->date  = BCD2dec(data_rx[4]);
    date->month = BCD2dec(data_rx[5]);
    date->year  = BCD2dec(data_rx[6]);
    return 1;
    }
    return 0;
}

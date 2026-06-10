#include "main.h"
#include "SHT30.h"

uint8_t SHT30_cmd_buf[2]={0x24,0x00};
uint8_t data[6]={0};



HAL_StatusTypeDef SHT30_read_data(I2C_HandleTypeDef *hi2c,uint32_t timeout)
{
	HAL_StatusTypeDef stt;

    if ((stt=HAL_I2C_IsDeviceReady(hi2c, SHT30_ADDR << 1, 3, timeout) )!= HAL_OK)
    {
        return stt; // device not ready
    }

    // Send measurement command

    if ((stt=HAL_I2C_Master_Transmit(hi2c,SHT30_ADDR << 1,SHT30_cmd_buf,2,timeout)) != HAL_OK)
    {
        return stt;
    }

    HAL_Delay(100); // wait measurement

    // Read data
    if ((stt=HAL_I2C_Master_Receive(hi2c,SHT30_ADDR << 1,data,6, timeout)) != HAL_OK)
    {
        return stt;
    }
    return stt;
}



void SHT30_read_data_raw(uint32_t *temp,uint32_t *humi)
{
    uint16_t raw;

    raw = (data[0] << 8) | data[1];

    *temp = -4500 + ((17500 * (int32_t)raw) / 65535);

    raw = (data[3] << 8) | data[4];

    *humi = (10000 * (uint32_t)raw) / 65535;
}

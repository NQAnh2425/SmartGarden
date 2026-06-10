
#ifndef SRC_SHT30_H_
#define SRC_SHT30_H_

#define SHT30_ADDR 0x44



HAL_StatusTypeDef SHT30_read_data(I2C_HandleTypeDef *hi2c,uint32_t timeout);
void SHT30_read_data_raw(uint32_t *temp,uint32_t *humi);



#endif /* SRC_SHT30_H_ */

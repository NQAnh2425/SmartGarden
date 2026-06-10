#ifndef __LORA_NETWORK__H__
#define __LORA_NETWORK__H__

#include <stdio.h>
#include <stdint.h>
#include "LoRa.h" 
#include "DS3231.h"

#include "main.h"

#define SOF_BYTE 0xAA
#define EOF_BYTE 0x55


#define FRAME_TYPE_BEACON 0x01
#define FRAME_TYPE_JOIN_REQUEST 0X02
#define FRAME_TYPE_JOIN_RESPONSE 0X03
#define FRAME_TYPE_DATA 0x04
#define FRAME_TYPE_ACK 0X05


#define FRAME_TYPE_DATA_LENGTH 0x0A
#define FRAME_TYPE_JOIN_REQUEST_LENGTH 0x05
#define FRAME_TYPE_BEACON_LENGTH 0x09
#define FRAME_TYPE_JOIN_RESPONSE_MAX_LENGTH 255-9
#define FRAME_TYPE_ACK_LENGTH 0x05


#define gateway_id 0x20
#define Node_ID 0x01
#define NODE_ID_ADDR  0x0800FC00

/*absolute value*/
#define MAX_PAYLOAD_SIZE 255 - 7
#define MAX_NODE 16
#define timeout_sec 5
#define MAX_JOIN_FAILURES 3




typedef enum frame_type{
    beacon_frame,
    join_request_frame,
    join_accept_frame,
    data_frame,
    ACK_frame,
} frame_type_t;

typedef enum
{
    NACK = 0x00,
    ACK  = 0x01
} ack_t;





typedef enum {
    PAYLOAD_CREATE,
    PAYLOAD_TRANSMIT,
} transmit_state_t;

typedef enum{
    IDLE =0,
    SEARCHING_FOR_SOF,
    RECEIVING_DEV_ID,
    RECEIVING_FRAME_TYPE,
    RECEIVING_LENGTH,
    RECEIVING_PAYLOAD_DATA,
    RECEIVING_CHECKSUM,
    RECEIVING_EOF,
} receive_state_t;

typedef struct {
    uint16_t temperature_raw;
    uint16_t moisture_raw;
    uint8_t humidity_raw;
} sensor_data_raw_t;

typedef struct {
    uint8_t type;
    uint8_t dev_id;
    uint8_t length;
    uint8_t crc;
    receive_state_t rx_state;
    uint8_t FiFoAddPtr;
    uint8_t number_of_bytes;
    uint8_t _ACK;
    union
    {
        struct {
            uint8_t temp_int;
            uint8_t temp_frac;
            uint8_t humi;
            uint8_t mois;
        } data;

        struct 
        {
            uint8_t hour;
            uint8_t minute;
            uint8_t second;
        }data_beacon;
        
        uint8_t response_data[4];
        
    }payload;
    
} frame_data_t;

//extern uint8_t nodeid;
//extern uint16_t bitmap;
//extern uint8_t node_unjoined_num;


uint16_t flash_read_node_id(void);
void store_nodeid(uint8_t node_id);
HAL_StatusTypeDef flash_write_node_id(uint16_t node_id);



uint8_t rtc_calibrate(void);
uint8_t RTC_SetTime(RTC_HandleTypeDef *rtc,Date *date,uint32_t format);
uint8_t RTC_SetTime_Calib(RTC_HandleTypeDef *rtc,I2C_HandleTypeDef *hi2c,Date *date, uint32_t format);
uint8_t RTC_SetAlarm_NextPeriod(RTC_HandleTypeDef *rtc,uint32_t period_sec,uint32_t format);
void RTC_SetWakeupTime_NextPeriod(RTC_HandleTypeDef *rtc,uint32_t period_sec,uint32_t format);
uint8_t RTC_SetAlarm(uint32_t wakeup_time_s,RTC_HandleTypeDef *rtc,uint32_t format);
void RTC_SetAlarm_Timeslot(uint8_t nodeid,RTC_HandleTypeDef *rtc,uint16_t tdma_wakeup_delay,uint32_t format);
uint32_t RTC_ReadCounter(RTC_HandleTypeDef *hrtc);

void Clear_Frame(frame_data_t *frame);
uint8_t find_first_empty_TimeSlot(uint16_t bitmap);
uint16_t set_first_empty_TimeSlot(uint16_t bitmap);

uint8_t calculate_crc(uint8_t *payload_data, uint8_t length);

uint8_t Node_Joined_Num(uint16_t bitmap);
uint8_t Node_Unjoined_Num(void);


#endif

#ifndef __GATEWAY_H__
#define __GATEWAY_H__
#include "LoRa_network.h"



typedef enum {
    UNJOINED=0,
	INIT_FAIL,
	INIT_SUCCESS,
    WAIT_TO_NEXT_PERIOD,
    TX_BEACON,
    RX_JOIN_REQUEST_INIT,
    RX_JOIN_REQUEST,
    TX_REQUEST_RESPONSE_INIT,
    TX_REQUEST_RESPONSE,
    WAIT_TO_RX_DATA,
    RX_DATA,
    HANDLE_DATA,
    NETWORK_MAINTAIN
} gateway_state_t;

typedef struct
{
    uint8_t node_id;
    uint8_t join_fail_count;
} node_info_t;

gateway_state_t Gateway_setup(gateway_state_t *state,LoRa* _LoRa, uint8_t trial_time);

void data_buffer_update(uint8_t *data, RTC_TimeTypeDef *current_time,uint8_t time_driff);

void Gateway_Lora_Init(LoRa *myLoRa,SPI_HandleTypeDef *hspi);

void Create_Beacon_Frame(frame_data_t *frame,uint8_t *data);

void Create_ACK_Frame(frame_data_t *frame,uint8_t *data);

uint8_t Create_JoinAccept_Frame(frame_data_t *frame,uint8_t node_unjoined_num, uint16_t bitmap);

void Create_Frame(frame_data_t *frame,frame_type_t frame_type,uint8_t *data);

uint8_t create_payload_gateway(frame_data_t *frame,uint8_t frame_type,uint8_t Node_joined_num);

uint8_t Gateway_Tx_Beacon(LoRa* _LoRa, uint16_t timeout);
// @brief: Gateway transmit join response
uint8_t Gateway_Tx_JoinResponse(LoRa* _LoRa,uint8_t Node_unjoined_num, uint16_t timeout);
// @brief: Gateway transmit ACK
uint8_t Gateway_Tx_ACK(LoRa* _LoRa, uint16_t timeout);

//static inline uint8_t fifo_read(LoRa *_LoRa)
//{
//    return LoRa_read(_LoRa, RegFiFo);
//};
//static void lora_rx_reset(LoRa *_LoRa,frame_data_t *frame)
//{
//    LoRa_gotoMode(_LoRa, RXCONTIN_MODE);
//    frame->rx_state = IDLE;
//};

uint32_t RTC_ReadCounter(RTC_HandleTypeDef *hrtc);

uint8_t Gateway_GetTime_Sync(RTC_HandleTypeDef *rtc, RTC_TimeTypeDef *current_time, uint32_t format);

uint8_t Gateway_Rx_JoinReq(LoRa* _LoRa,frame_data_t *frame_data_rx);
// @brief: receive data frame from node
uint8_t Gateway_Rx_Data(LoRa* _LoRa,frame_data_t *frame_data_rx, uint16_t bitmap);
// @brief: get data to buffer
uint8_t Gateway_Get_Data(frame_data_t *frame_data_rx, uint8_t (*data)[7]);
// @brief: get unjoined node UID to buffer
uint8_t Gateway_Get_UID(frame_data_t *frame_data_rx);


#endif

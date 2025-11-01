#include "dfplayer.h"
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(dfplayer, LOG_LEVEL_DBG);

#define RECEIVE_BUFF_SIZE 10
#define RECEIVE_TIMEOUT 100

const struct device *uart = DEVICE_DT_GET(DT_NODELABEL(uart1));

uint8_t send_buffer[DFPLAYER_SEND_LENGTH];

static const uint8_t DFPLAYER_START_BYTE     = 0x7E;
static const uint8_t DFPLAYER_VERSION        = 0xFF;
static const uint8_t DFPLAYER_COMMAND_LENGTH = 0x06;
static const uint8_t DFPLAYER_END_BYTE       = 0xEF;

struct __packed dfplayer_raw_message_t {
    uint8_t start_byte;
    uint8_t version;
    uint8_t length;
    uint8_t command_code;
    uint8_t feedback;
    uint8_t param_high;
    uint8_t param_low;
    uint8_t checksum_high;
    uint8_t checksum_low;
    uint8_t end_byte;
};

static uint8_t rx_buf[RECEIVE_BUFF_SIZE] = {0};

static void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data)
{
  LOG_DBG("Something coming in on the UART receiver");
  LOG_HEXDUMP_DBG(evt->data.rx.buf + evt->data.rx.offset, evt->data.rx.len, "UART RX Data");
	switch (evt->type) {

	case UART_RX_RDY:
    LOG_DBG("Something coming in on the UART receiver");
		if ((evt->data.rx.len) == 1) {
			if (evt->data.rx.buf[evt->data.rx.offset] == '1') {
				LOG_DBG("Received, 1");
			} else if (evt->data.rx.buf[evt->data.rx.offset] == '2') {
				LOG_DBG("Received, 1");
			} else if (evt->data.rx.buf[evt->data.rx.offset] == '3') {
				LOG_DBG("Received, 1");
			}
		}
		break;
	case UART_RX_DISABLED:
		uart_rx_enable(dev, rx_buf, sizeof rx_buf, RECEIVE_TIMEOUT);
		break;

	default:
		break;
	}
}

int dfplayer_init(void)
{
  LOG_DBG("Inside dfplayer init");
  int err;
  static uint8_t tx_buf[] = {"Initialize the player \n\r"};
  if (!device_is_ready(uart))
  {
    LOG_ERR("UART device not ready\r\n");
    return -1;
	}
  // err = uart_callback_set(uart, uart_cb, NULL);
  // if (err)
  // {
  //   LOG_ERR("Failure when setting callback");
  //   return err;
  // }
  LOG_INF("DFPlayer UART initialized");
  // LOG_DBG("Sending string");
  
  // err = uart_tx(uart, tx_buf, sizeof(tx_buf), SYS_FOREVER_US);
  // if (err)
  // {
  //   LOG_DBG("Failed when sending string");
  //   return err;
  // }
  k_msleep(1000);
  return 0;
}

static uint16_t calculateCheckSum(uint8_t *buffer){
  uint16_t sum = 0;
  for (int i=Stack_Version; i<Stack_CheckSum; i++) {
    sum += buffer[i];
  }
  return -sum;
}

static void uint16ToArray(uint16_t value, uint8_t *array){
  *array = (uint8_t)(value>>8);
  *(array+1) = (uint8_t)(value);
}

static int sendStack(uint8_t command, uint16_t argument){
  int err;
  send_buffer[Stack_Command] = command;
  uint16ToArray(argument, send_buffer+Stack_Parameter);
  uint16ToArray(calculateCheckSum(send_buffer), send_buffer+Stack_CheckSum);
  LOG_DBG("Track sent");
  err = uart_tx(uart, send_buffer, sizeof(send_buffer), SYS_FOREVER_US);
  if (err)
  {
    LOG_DBG("Failed when calling uart_tx. Err = %d", err);
    return err;
  }
  return 0;
}

void dfplayer_play(int fileNumber){
  sendStack(0x03, fileNumber);
}

int df_play_track_depr(uint16_t track)
{
  int err;
  static uint8_t tx_buf[] = {"nRF Connect SDK Fundamentals \n\r"};
  LOG_DBG("Selected track: %d", track);
  dfplayer_raw_message_t msg = {
    .start_byte    = 0x7E,  // Example values
    .version       = 0xFF,
    .length        = 0x06,
    .command_code  = 0x03,
    .feedback      = 0x01,
    .param_high    = 0x00,
    .param_low     = 0x01,
    .checksum_high = 0xFE,
    .checksum_low  = 0xF7,
    .end_byte      = 0xEF,
  };
  err = uart_tx(uart, (uint8_t *)&msg, sizeof(msg), SYS_FOREVER_US);
  if (err)
  {
    LOG_DBG("Failed when calling uart_tx. Err = %d", err);
    return err;
  }
  k_msleep(1000);
  // LOG_DBG("Sending string");
  // err = uart_tx(uart, tx_buf, sizeof(tx_buf), SYS_FOREVER_US);
  // if (err)
  // {
  //   LOG_DBG("Failed when sending string");
  //   return err;
  // }

  return 0;
}
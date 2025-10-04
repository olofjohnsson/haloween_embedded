#include "dfplayer.h"
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(dfplayer, LOG_LEVEL_DBG);

#define RECEIVE_BUFF_SIZE 10
#define RECEIVE_TIMEOUT 100

const struct device *uart= DEVICE_DT_GET(DT_NODELABEL(uart1));

static const uint8_t DFPLAYER_START_BYTE     = 0x7E;
static const uint8_t DFPLAYER_VERSION        = 0xFF;
static const uint8_t DFPLAYER_COMMAND_LENGTH = 0x06;
static const uint8_t DFPLAYER_END_BYTE       = 0xEF;

static uint8_t rx_buf[RECEIVE_BUFF_SIZE] = {0};

static void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data)
{
  
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
  int err;
  if (!device_is_ready(uart))
  {
    printk("UART device not ready\r\n");
    return -1;
	}
  err = uart_callback_set(uart, uart_cb, NULL);
  if (err)
  {
    return err;
  }
  LOG_INF("DFPlayer UART initialized");
  return 0;
}

int df_play_track(uint16_t track)
{
  int err;
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
  err = uart_tx(uart, (uint8_t *)&msg, sizeof(msg), SYS_FOREVER_MS);
  if (err)
  {
    LOG_DBG("Failed when calling uart_tx");
    return err;
  }
  return 0;
}
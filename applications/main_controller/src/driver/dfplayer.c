#include "dfplayer.h"
#include <zephyr/drivers/uart.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(dfplayer, LOG_LEVEL_INF);

#define UART_LABEL DT_LABEL(DT_NODELABEL(uart1))

static const struct device *uart_dev;

static const uint8_t DFPLAYER_START_BYTE     = 0x7E;
static const uint8_t DFPLAYER_VERSION        = 0xFF;
static const uint8_t DFPLAYER_COMMAND_LENGTH = 0x06;
static const uint8_t DFPLAYER_END_BYTE       = 0xEF;

static void dfplayer_send_raw(dfplayer_message_t *msg)
{
    if (!msg) {
        LOG_ERR("Invalid DFPlayer message");
        return;
    }

    dfplayer_raw_message_t raw_msg;
    raw_msg.start_byte    = DFPLAYER_START_BYTE;
    raw_msg.version       = DFPLAYER_VERSION;
    raw_msg.length        = DFPLAYER_COMMAND_LENGTH;
    raw_msg.command_code  = msg->command_code;
    raw_msg.feedback      = 0x00;
    raw_msg.param_high    = (msg->parameter >> 8) & 0xFF;
    raw_msg.param_low     = msg->parameter & 0xFF;

    uint16_t checksum = -(DFPLAYER_VERSION + DFPLAYER_COMMAND_LENGTH +
                          raw_msg.command_code + raw_msg.feedback +
                          raw_msg.param_high + raw_msg.param_low);

    raw_msg.checksum_high = (checksum >> 8) & 0xFF;
    raw_msg.checksum_low  = checksum & 0xFF;
    raw_msg.end_byte      = DFPLAYER_END_BYTE;

    uint8_t *bytes = (uint8_t *)&raw_msg;
    for (int i = 0; i < sizeof(dfplayer_raw_message_t); i++) {
        uart_poll_out(uart_dev, bytes[i]);
    }

    LOG_INF("DFPlayer command sent: code=0x%02X param=%u",
            raw_msg.command_code, msg->parameter);
}

int dfplayer_init(void)
{
    uart_dev = device_get_binding(UART_LABEL);
    if (!uart_dev) {
        LOG_ERR("UART device %s not found", UART_LABEL);
        return -ENODEV;
    }
    LOG_INF("DFPlayer UART initialized");
    return 0;
}

int dfplayer_send_message(dfplayer_message_t *msg)
{
    if (!msg) {
        return -EINVAL;
    }
    dfplayer_send_raw(msg);
    return 0;
}

int df_play_track(uint16_t track)
{
    dfplayer_message_t msg = {
        .command_code = 0x03,
        .parameter    = track
    };
    return dfplayer_send_message(&msg);
}
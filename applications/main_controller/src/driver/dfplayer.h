#ifndef DFPLAYER_H
#define DFPLAYER_H

#include <zephyr/kernel.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
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
} dfplayer_raw_message_t;

typedef struct {
    uint8_t command_code;
    uint16_t parameter;
} dfplayer_message_t;

int dfplayer_init(void);
int df_play_track(uint16_t track);

#ifdef __cplusplus
}
#endif

#endif /* DFPLAYER_H */
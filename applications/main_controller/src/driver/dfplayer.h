#ifndef DFPLAYER_H
#define DFPLAYER_H

#include <zephyr/kernel.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define Stack_Header 0
#define Stack_Version 1
#define Stack_Length 2
#define Stack_Command 3
#define Stack_ACK 4
#define Stack_Parameter 5
#define Stack_CheckSum 7
#define Stack_End 9

#define DFPLAYER_SEND_LENGTH 10

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
/**
 * @brief Plays a specific audio file on the DFPlayer Mini.
 *
 * This function sends a command to the DFPlayer Mini module to play
 * the specified file number from the current storage device (e.g., SD card).
 *
 * @param fileNumber The number of the file to play (starting from 1).
 *
 * @note The file must be properly named and located according to the DFPlayer Mini
 *       file naming conventions (e.g., "0001.mp3" for file number 1).
 */
void dfplayer_play(int fileNumber);


#ifdef __cplusplus
}
#endif

#endif /* DFPLAYER_H */
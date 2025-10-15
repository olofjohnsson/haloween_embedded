#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
//#include "driver/dfplayer.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

int main(void)
{
  int err;
  LOG_DBG("Starting application in main controller");
  LOG_DBG("Init dfplayer");
  //err = dfplayer_init();
  if (err)
  {
    LOG_ERR("Failure during init if dfplayer");
  }
  while (1)
  {
    LOG_DBG("Inside main loop...");
    LOG_DBG("Play track");
    //df_play_track(1);
    k_msleep(1000);

  }
  return 0;
}

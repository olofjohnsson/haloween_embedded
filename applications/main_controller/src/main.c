#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include "hardware/vdd_level.h"
#include "driver/dfplayer.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

#define GPIO_NODE DT_ALIAS(redled)

static const struct gpio_dt_spec pin = GPIO_DT_SPEC_GET(GPIO_NODE, gpios);

int main(void)
{
  int err;
  err = set_vdd_level();
  if (err)
  {
    LOG_ERR("Failed when setting the vdd level to 3.3 V");
  }
  if (!gpio_is_ready_dt(&pin)) {
		err = -1;
    return err;
	}

	err = gpio_pin_configure_dt(&pin, GPIO_OUTPUT_ACTIVE);
	if (err < 0) {
		return err;
	}
  LOG_DBG("Starting application in main controller");
  LOG_DBG("Init dfplayer");
  err = dfplayer_init();
  if (err)
  {
    LOG_ERR("Failure during initialization of dfplayer");
  }
  LOG_DBG("Play track 1");
  dfplayer_play(1);
  while (1)
  {
    err = gpio_pin_toggle_dt(&pin);
		if (err < 0) {
			return err;
		}
    //dfplayer_play(1);
    k_msleep(2000);

  }
  return 0;
}

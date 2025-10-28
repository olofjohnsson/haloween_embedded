#include <zephyr/kernel.h>
#include <zephyr/gpio.h>

#define NODE_MP3_SW DT_NODELABEL(sw_mp3)
static const struct gpio_dt_spec mp3 = GPIO_DT_SPEC_GET(NODE_MP3_SW, gpios);

int init_pins(void)
{
  int ret = gpio_pin_configure_dt(&mp3, GPIO_OUTPUT_ACTIVE);
}

int main(void)
{
  if (!gpio_is_ready_dt(&mp3)) {
    return;
  }
  return 0;
}

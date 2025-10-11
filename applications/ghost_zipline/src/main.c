#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "application/application.h"
#include <zephyr/logging/log.h>
#include "hardware/vdd_level.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

int main(void)
{
	set_vdd_level();
	LOG_DBG("Main");
	run_application();
}

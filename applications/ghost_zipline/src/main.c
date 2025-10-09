#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "application/application.h"
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

int main(void)
{
	LOG_DBG("Main");
	run_application();
}

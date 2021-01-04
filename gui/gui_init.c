#include "../utils/lv_drv_conf.h"
#include "../utils/lvgl/lvgl.h"
#include <abm_device.h>

#include "../utils/lv_drivers/display/fbdev.h"

#include "../utils/lv_drivers/indev/keyboard.h"
#include "../utils/lv_drivers/indev/libinput_drv.h"
#include "../utils/lv_drivers/indev/evdev.h"

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <threads.h>
#include <unistd.h>

void tick_thrd() {
	for(;;) {
		usleep(5); // Sleep for 5 milliseconds
		lv_tick_inc(5); // Tell LVGL that 5 milliseconds have passed
		lv_task_handler(); // Tell LVGL to do its stuff
	}
}

void gui_init(struct abm_device device) {
	thrd_t tick_thrd_t;

	// Initialize LVGL
	lv_init();

	fbdev_init();

	evdev_init();

	// Set up buffer
	static lv_disp_buf_t disp_buf;
	static lv_color_t buf[LV_HOR_RES_MAX * LV_VER_RES_MAX];
	lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX);

	// Set up display
	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	disp_drv.buffer = &disp_buf;
	disp_drv.flush_cb = fbdev_flush;
    
    // Get resolution
    uint32_t width,height=0;
    fbdev_get_sizes(&width, &height);
    
    printf("Framebuffer resolution: %d x %d\n", width, height);
    
    
    // Set resolution
    disp_drv.hor_res = width;
    disp_drv.ver_res = height;
    disp_drv.dpi = device.dpi;
    // Register disp drv
	lv_disp_drv_register(&disp_drv);
    
    // Create LVGL thread
    thrd_create(&tick_thrd_t, (thrd_start_t)tick_thrd, NULL);
}

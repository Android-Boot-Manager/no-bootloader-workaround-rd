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
#include "gui_init.h"

void tick_thrd(void) {
	for(;;) {
		usleep(5); // Sleep for 5 milliseconds
		lv_tick_inc(5); // Tell LVGL that 5 milliseconds have passed
		lv_task_handler(); // Tell LVGL to do its stuff
	}
}

void gui_init(struct abm_device *device) {
	thrd_t tick_thrd_t;

	// Initialize LVGL
	lv_init();

	fbdev_init();

	evdev_init();

	// Set up buffer
	static lv_disp_draw_buf_t disp_buf;
	static lv_color_t buf[LV_HOR_RES_MAX * LV_VER_RES_MAX];
	 lv_disp_draw_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX);

	// Set up display
	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	disp_drv.draw_buf = &disp_buf;
	disp_drv.flush_cb = fbdev_flush;
    
    // Get resolution
    uint32_t width,height=0;
    fbdev_get_sizes(&width, &height);
    
    printf("Framebuffer resolution: %d x %d\n", width, height);
    
    
    // Set resolution
    device->x_res=width;
    device->y_res=height;
    disp_drv.hor_res = width;
    disp_drv.ver_res = height;
    disp_drv.dpi = device->dpi;
    // Register disp drv
	lv_disp_drv_register(&disp_drv);
    
    // enable event input
	evdev_init();

	evdev_set_file(device->touchscreen_dev_path);
	// get mouse as an input
	lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.read_cb = evdev_read;
	
	lv_indev_t * mouse_indev = lv_indev_drv_register(&indev_drv);

	lv_obj_t * cursor_obj = lv_img_create(lv_scr_act(), NULL); //Create an image for the cursor
	lv_img_set_src(cursor_obj, LV_SYMBOL_FILE); //For simlicity add a built in symbol not an image
	lv_indev_set_cursor(mouse_indev, cursor_obj); // connect the object to the driver

    thrd_create(&tick_thrd_t, (thrd_start_t)tick_thrd, NULL);

}

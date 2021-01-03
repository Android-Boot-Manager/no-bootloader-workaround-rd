#include "../utils/lv_drv_conf.h"
#include "../utils/lvgl/lvgl.h"

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

void gui_init() {
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
    
    uint32_t width=0;
    uint32_t height=0;
    fbdev_get_sizes(&width, &height);
    
    printf("Framebuffer resolution: %d x %d\n", width, height);
    
    disp_drv.hor_res = width;
    disp_drv.ver_res = height;
    
	lv_disp_drv_register(&disp_drv);
    
    //LV_THEME_DEFAULT_INIT(LV_COLOR_GRAY, LV_COLOR_GRAY,
    //                      LV_THEME_MATERIAL_FLAG_DARK,
    //                      lv_theme_get_font_small(), lv_theme_get_font_normal(), lv_theme_get_font_subtitle(), lv_theme_get_font_title());
    
    lv_obj_t * win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, "Boot menu"); 

    thrd_create(&tick_thrd_t, (thrd_start_t)tick_thrd, NULL);
}

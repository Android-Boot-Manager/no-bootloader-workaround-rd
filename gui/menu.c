#include "../utils/lvgl/lvgl.h"

#include "../utils/lv_drivers/indev/keyboard.h"
#include "../utils/lv_drivers/indev/libinput_drv.h"
#include "../utils/lv_drivers/indev/evdev.h"

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <threads.h>
#include <unistd.h> 

lv_obj_t create_window(char * name){
    lv_obj_t * win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, name); 
    lv_win_set_scrollbar_mode(win, LV_SCRLBAR_MODE_OFF);
    
}

#include "../utils/lvgl/lvgl.h"

#include "../utils/lv_drivers/indev/keyboard.h"
#include "../utils/lv_drivers/indev/libinput_drv.h"
#include "../utils/lv_drivers/indev/evdev.h"

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <threads.h>
#include <unistd.h> 

void show_error(char * message){
    usleep(50000);
    lv_obj_t * label1 = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_align(label1, LV_LABEL_ALIGN_CENTER);       /*Center aligned lines*/
    lv_obj_align(label1, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);
    lv_label_set_text_fmt(label1, "#ff0000 Error: %s.", message);
}

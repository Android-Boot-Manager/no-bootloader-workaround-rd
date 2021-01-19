#include "../utils/lvgl/lvgl.h"

#include "../utils/lv_drivers/indev/keyboard.h"
#include "../utils/lv_drivers/indev/libinput_drv.h"
#include "../utils/lv_drivers/indev/evdev.h"

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <threads.h>
#include <unistd.h> 

#include <config.h>

lv_obj_t * win;
lv_obj_t * list1;

void create_window(char * name){
    win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, name); 
    lv_win_set_scrollbar_mode(win, LV_SCRLBAR_MODE_OFF);
    return win;
    
}

void create_menu(){
    list1 = lv_list_create(win, NULL);
    lv_obj_set_size(list1, 1000, 1000);
    lv_obj_align(list1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    lv_list_set_anim_time(list1, 0);
}

void add_button_to_menu(lv_event_cb_t event_cb, char * text){
    lv_obj_t * list_btn = lv_list_add_btn(list1,  LV_SYMBOL_FILE, text);
    lv_obj_set_event_cb(list_btn, event_cb);
    
}

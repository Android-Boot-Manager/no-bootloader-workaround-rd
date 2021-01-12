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

lv_obj_t * create_window(char * name){
    lv_obj_t * win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, name); 
    lv_win_set_scrollbar_mode(win, LV_SCRLBAR_MODE_OFF);
    return win;
    
}

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
    
}

lv_obj_t create_menu_from_entry_list(struct boot_entry *entry_list, int num_of_boot_entries){
    lv_obj_t * win = lv_win_create(lv_scr_act(), NULL);
    lv_obj_t * list1 = lv_list_create(win, NULL);
    lv_obj_set_size(list1, 1000, 1000);
    lv_obj_align(list1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    lv_list_set_anim_time(list1, 0);
    
    lv_obj_t * list_btn;
    lv_obj_set_state(list1, LV_STATE_DEFAULT);
    list_btn = lv_list_add_btn(list1,  LV_SYMBOL_FILE, entry_list->title);
    lv_obj_set_event_cb(list_btn, event_handler);
    for (int i = 1; i < num_of_boot_entries; i++) {
        printf("Adding entry: %s\n", (entry_list + i)->title);
        list_btn = lv_list_add_btn(list1,  LV_SYMBOL_FILE, (entry_list + i)->title);
        lv_obj_set_event_cb(list_btn, event_handler);
    }
    list_btn = lv_list_add_btn(list1,  LV_SYMBOL_FILE, "Extras");
    lv_obj_set_event_cb(list_btn, event_handler);
}

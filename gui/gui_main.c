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
lv_obj_t *tabview;
lv_obj_t *tab_boot_menu;
lv_obj_t *tab_extras;
lv_obj_t *tab_development;
lv_obj_t * gui_boot_menu;

void create_window(char * name){
    win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, name); 
    lv_win_set_scrollbar_mode(win, LV_SCRLBAR_MODE_OFF);
    return win;
    
}

void create_main_tabview(){
     /*Create a Tab view object*/
    tabview = lv_tabview_create(win, NULL);

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    tab_boot_menu = lv_tabview_add_tab(tabview, "Boot Menu");
    tab_extras = lv_tabview_add_tab(tabview, "Extras");
    tab_development = lv_tabview_add_tab(tabview, "Development");
}

void create_menu(){
    gui_boot_menu = lv_list_create(tab_boot_menu, NULL);
    lv_obj_set_size(gui_boot_menu, lv_obj_get_width(tab_boot_menu), lv_obj_get_height(tab_boot_menu));
    lv_obj_align(gui_boot_menu, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
}

void add_button_to_menu(lv_event_cb_t event_cb, char * text){
    lv_obj_t * list_btn = lv_list_add_btn(gui_boot_menu,  LV_SYMBOL_FILE, text);
    lv_obj_set_event_cb(list_btn, event_cb);
    
}

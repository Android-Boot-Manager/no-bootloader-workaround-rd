#include "../utils/lvgl/lvgl.h"

#include <gui_init.h>
#include <gui_main.h>

#include <abm_device.h>
#include <partition.h>

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <threads.h>
#include <unistd.h>
#include <stdlib.h>
#include <config.h>
#include <boot.h>

struct abm_device device;
struct boot_entry *entry_list;

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
    boot_android_from_system();
    add_button_to_menu(event_handler, "Click");
}

int main(int argc, char *argv[]) {
    printf("Abm start\n");

    if(argc<5)
    {
        printf("ERROR: Not enough arguments\n");
        exit(1);
    }
    
    device.dpi= atoi(argv[1]);
    device.codname = argv[2];
    device.sd_card_meta_path = argv[3];
    device.touchscreen_dev_path = argv[4];
    
    printf("Running on: %s, dpi: %d\n", device.codname, device.dpi);
    
    gui_init(&device);
    
    mount_sdcard_meta(device);
    
    
    
    parse_boot_entries(&entry_list);
     
    create_window("ABM");
    create_main_tabview();
    create_menu();
    
    for(int i=0; i<get_entry_count(); i++){
        add_button_to_menu(event_handler, (entry_list+i)->title);
    }
    
	for(;;)
		usleep(5000);
}


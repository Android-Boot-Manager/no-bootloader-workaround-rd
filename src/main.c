#include "../utils/lvgl/lvgl.h"

#include <gui_init.h>
#include <menu.h>

#include <abm_device.h>
#include <partition.h>

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <threads.h>
#include <unistd.h>
#include <stdlib.h>
#include <config.h>

struct abm_device device;
struct boot_entry entry_list;

int main(int argc, char *argv[]) {
    printf("Abm start\n");

    if(argc<4)
    {
        printf("ERROR: Not enough arguments\n");
        exit(1);
    }
    
    device.dpi= atoi(argv[1]);
    device.codname = argv[2];
    device.sd_card_meta_path = argv[3];
    
    printf("Running on: %s, dpi: %d\n", device.codname, device.dpi);
    
    gui_init(device);
    
    mount_sdcard_meta(device);
    
     parse_boot_entries(&entry_list);
     
    int size = sizeof(entry_list) / sizeof(struct boot_entry);

    printf("Boot_entry len: %u", size); 
    printf("First entry is: %s\n", entry_list.dtb);
    fflush(stdout);
    create_menu_from_entry_list(&entry_list, get_entry_count());
	// Sleep forever
	for(;;)
		usleep(5000);
}


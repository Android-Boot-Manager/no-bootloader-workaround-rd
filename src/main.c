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

struct abm_device device;

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
    
    mount_sdcard_meta(device);
     
	gui_init(device);
    
    create_window("Boot menu");
	// Sleep forever
	for(;;)
		usleep(5000);
}


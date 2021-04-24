#include <sys/mount.h> 
#include <sys/stat.h>
#include <device_config.h>
#include <stdio.h>
#include <unistd.h>
#include <gui_error.h>

#include "partition.h"

void mount_sdcard_meta() {
    mkdir("/meta", 0700);
    if (0 != mount(SD_META_PATH, "/meta", "ext2", 0, "")) {
        show_error("unable to mount meta\n");
        for(;;){
         usleep(5000);   
        }
    }
}


#include <sys/mount.h> 
#include <sys/stat.h>
#include <abm_device.h>
#include <stdio.h>
#include <gui_error.h>

void mount_sdcard_meta(struct abm_device device) {
    mkdir("/meta", 0700);
    if (0 != mount(device.sd_card_meta_path, "/meta", "ext2", 0, "")) {
        show_error("unable to mount meta\n");
        //for(;;){
         //usleep(5000);   
        //}
    }
}


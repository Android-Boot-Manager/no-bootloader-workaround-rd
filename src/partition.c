#include <sys/mount.h> 
#include <sys/stat.h>
#include <abm_device.h>
#include <stdio.h>

void mount_sdcard_meta(struct abm_device device) {
    mkdir("/meta", 0700);
    if (0 != mount(device.sd_card_meta_path, "/meta", "ext2", 0, "")) {
        printf("ERROR mounting meta\n");
    }
}


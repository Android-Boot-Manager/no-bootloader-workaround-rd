#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include "boot.h"

void boot_android_from_system(void)
{
    execl("/bin/sh", "/bin/boot-android-sar.sh", (char *)0);
    printf("Return not expected. Must be an execve error.n");
 }

 

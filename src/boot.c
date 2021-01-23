#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

void boot_android_from_system()
{
    char *const parmList[] = {"/bin/boot-android-sar.sh", NULL};
    execl("/bin/sh", "/bin/boot-android-sar.sh", (char *)0);
    printf("Return not expected. Must be an execve error.n");
 }

 

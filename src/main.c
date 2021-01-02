#include "../utils/lvgl/lvgl.h"

#include "../gui/gui_init.h"
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <threads.h>
#include <unistd.h>

int main() {
	gui_init()
    
	// Sleep forever
	for(;;)
		usleep(5000);
}


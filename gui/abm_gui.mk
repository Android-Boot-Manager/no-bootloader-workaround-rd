CSRCS += gui_init.c
CSRCS += gui_main.c
CSRCS += gui_error.c

DEPPATH += --dep-path gui
VPATH += :gui

CFLAGS += "-Igui"
 

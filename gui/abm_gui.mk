CSRCS += gui_init.c
CSRCS += menu.c
CSRCS += gui_error.c

DEPPATH += --dep-path gui
VPATH += :gui

CFLAGS += "-Igui"
 

CSRCS += partition.c
CSRCS += fs_utils.c
CSRCS += config.c

DEPPATH += --dep-path src
VPATH += :src

CFLAGS += "-Isrc"
 

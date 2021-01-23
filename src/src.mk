CSRCS += partition.c
CSRCS += fs_utils.c
CSRCS += config.c
CSRCS += boot.c

DEPPATH += --dep-path src
VPATH += :src

CFLAGS += "-Isrc"
 

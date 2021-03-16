#
# Makefile
#
CC ?= $(CROSS_COMPILE)gcc
LVGL_DIR_NAME ?= lvgl
LVGL_DIR ?= utils

WARNINGS ?= -Wall -Wextra \
						-Wshadow -Wundef -Wmaybe-uninitialized -Wmissing-prototypes -Wno-discarded-qualifiers \
						-Wno-unused-function -Wno-error=strict-prototypes -Wpointer-arith -fno-strict-aliasing -Wno-error=cpp -Wuninitialized \
						-Wno-unused-parameter -Wno-missing-field-initializers -Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default  \
					  -Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-error=pedantic -Wno-sign-compare -Wno-error=missing-prototypes -Wdouble-promotion -Wclobbered -Wdeprecated  \
						-Wempty-body  -Wstack-usage=2048 \
            -Wtype-limits -Wsizeof-pointer-memaccess -Wpointer-arith
            
CFLAGS ?= -O3 -g0 -I$(LVGL_DIR)/ $(WARNINGS) -static
LDFLAGS ?= -lm -lpthread -static
OUT ?= out
BIN = $(OUT)/abm

#Collect the files to compile
MAINSRC = ./src/main.c

include gui/abm_gui.mk
include src/src.mk
include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk

OBJEXT ?= .o

AOBJS = $(addprefix $(OUT)/, $(ASRCS:.a=.o))
COBJS = $(addprefix $(OUT)/, $(CSRCS:.c=.o))

MAINOBJ = $(addprefix $(OUT)/, $(MAINSRC:.c=$(OBJEXT)))

SRCS = $(ASRCS) $(CSRCS) $(MAINSRC)
OBJS = $(AOBJS) $(COBJS)

DEVICE ?= generic
DEBUG ?= false

CFLAGS += -DDEBUG=$(DEBUG)

## MAINOBJ -> OBJFILES

default: clean out/rd.cpio.gz

out/:
	@mkdir -p out/src out/utils/lv_drivers/indev out/utils/lv_drivers/gtkdrv out/utils/lv_drivers/display

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "CC $<"

out/%.o: %.c out/
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "CC $<"

rd-generic: $(BIN)
	@echo "Building ramdisk"
	@mkdir -p out/rd/bin
	@cp -P prebuilts/* out/rd/bin/
	@cp scripts/* out/rd/
	@cp $(BIN) out/rd/bin/

# if needed, you can simply override this target to add per-device steps
ifneq ($(DEVICE),generic)
rd-$(DEVICE): rd-generic
	@cp devices/$(DEVICE)/env.sh out/rd/env.sh
endif

out/rd.cpio: rd-$(DEVICE)
	@echo "CPIO out/rd"
	@(cd out/rd/ && find . | cpio -o -H newc > ../rd.cpio)

out/rd.cpio.gz: out/rd.cpio
	@echo "GZIP out/rd.cpio"
	@gzip -k out/rd.cpio

$(BIN): $(AOBJS) $(COBJS) $(MAINOBJ)
	@echo "LD $(BIN)"
	@$(CC) -o $(BIN) $(MAINOBJ) $(AOBJS) $(COBJS) $(LDFLAGS)

clean:
	@echo "CLEAN"
	@rm -rf $(BIN) $(AOBJS) $(COBJS) $(MAINOBJ) 

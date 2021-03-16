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

CFLAGS += -DDEBUG=$(DEBUG) -Iout/generated/

## MAINOBJ -> OBJFILES

default: clean out/rd.cpio.gz

out/:
	@mkdir -p out/src out/rd/bin out/generated out/utils/lv_drivers/indev out/utils/lv_drivers/gtkdrv out/utils/lv_drivers/display

%.o: %.c out/generated/device_config.h
	@echo "CC $<"
	@$(CC) $(CFLAGS) -c $< -o $@

out/%.o: %.c out/generated/device_config.h
	@echo "CC $<"
	@$(CC) $(CFLAGS) -c $< -o $@

out/generated/device_config.h: rd-$(DEVICE) out/
	@echo "GEN $@"
	@sh utils/gen_config_h.sh out/rd/env.sh $@

rd-base: $(BIN)
	@echo "BUILDRD base"
	@cp -P prebuilts/* out/rd/bin/
	@cp scripts/* out/rd/
	@cp $(BIN) out/rd/bin/
	@echo "DEBUG=$(DEBUG)" >> out/rd/env.sh

rd-device: out/
	@echo "BUILDRD $(DEVICE)"

rd-default: rd-device
	@cat devices/$(DEVICE)/env.sh >> out/rd/env.sh
	
include devices.mk

# Test if there is an device rule present. If not, use the default.
ifneq ($(shell make -qf utils/dummy.mk rd-$(DEVICE) 2>/dev/null; test $$? -le 1 && echo ok),ok)
rd-$(DEVICE): rd-default
endif

out/rd.cpio: rd-base
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
	@rm -rf $(BIN) $(AOBJS) $(COBJS) $(MAINOBJ) $(OUT) 

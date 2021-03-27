#
# Makefile
#
CC ?= $(CROSS_COMPILE)gcc
CXX ?= $(CROSS_COMPILE)g++
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
CXXFLAGS ?= $(CFLAGS)
LDFLAGS ?= -lm -lpthread -static
OUT ?= out
BIN = $(OUT)/abm

#Collect the files to compile
MAINSRC = ./src/main.c

include gui/abm_gui.mk
include src/src.mk
include boot/android/SAR/sar.mk
include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk

OBJEXT ?= .o

AOBJS = $(addprefix $(OUT)/, $(ASRCS:.a=.o))
COBJS = $(addprefix $(OUT)/, $(CSRCS:.c=.o))
CXXOBJS = $(addprefix $(OUT)/, $(CXXSRCS:.cpp=.o))
MAINOBJ = $(addprefix $(OUT)/, $(MAINSRC:.c=$(OBJEXT)))

SRCS = $(ASRCS) $(CSRCS) $(CXXSRCS) $(MAINSRC)
OBJS = $(AOBJS) $(COBJS) $(CXXOBJS)

DEVICE ?= generic
DEBUG ?= false
UNIVERSAL ?= $(DEBUG)

CFLAGS += -DDEBUG=$(DEBUG) -Iout/generated/
CXXFLAGS += -DDEBUG=$(DEBUG) -Iout/generated/

## MAINOBJ -> OBJFILES

default: clean
	+@make out/rd.cpio.gz

out:
	@mkdir -p out/src out/rd/bin out/generated out/utils/lv_drivers/indev out/utils/lv_drivers/gtkdrv out/utils/lv_drivers/display out/utils/lvgl/examples/widgets/table out/utils/lvgl/examples/widgets/list/ out/utils/lvgl/examples/widgets/spinbox/  out/utils/lvgl/examples/widgets/colorwheel/  out/utils/lvgl/examples/widgets/obj/ out/utils/lvgl/examples/widgets/line/ out/utils/lvgl/examples/widgets/msgbox/ out/utils/lvgl/examples/widgets/spinner/ out/utils/lvgl/examples/widgets/tabview/ out/utils/lvgl/examples/widgets/tileview/ out/utils/lvgl/examples/widgets/canvas/ out/utils/lvgl/examples/widgets/img/ out/utils/lvgl/examples/widgets/btnmatrix/ out/utils/lvgl/examples/widgets/keyboard/ out/utils/lvgl/examples/widgets/calendar/ out/utils/lvgl/examples/widgets/switch/ out/utils/lvgl/examples/widgets/btn/ out/utils/lvgl/examples/widgets/checkbox/ out/utils/lvgl/examples/widgets/slider/ out/utils/lvgl/examples/widgets/meter/ out/utils/lvgl/examples/widgets/label/ out/utils/lvgl/examples/widgets/win/ out/utils/lvgl/examples/widgets/imgbtn/ out/utils/lvgl/examples/widgets/arc/ out/utils/lvgl/examples/widgets/textarea/ out/utils/lvgl/examples/widgets/dropdown/ out/utils/lvgl/examples/widgets/bar/
	@mkdir -p out/utils/lvgl/examples/widgets/chart/ out/utils/lvgl/examples/widgets/led/ out/utils/lvgl/examples/widgets/roller/ out/utils/lvgl/examples/scroll/ out/utils/lvgl/examples/porting/ out/utils/lvgl/examples/get_started/ out/utils/lvgl/examples/layouts/flex/ out/utils/lvgl/examples/layouts/grid/ out/utils/lvgl/examples/assets/ out/utils/lvgl/examples/styles/ out/utils/lvgl/src/extra/widgets/table out/utils/lvgl/src/extra/widgets/list/ out/utils/lvgl/src/extra/widgets/spinbox/  out/utils/lvgl/src/extra/widgets/colorwheel/  out/utils/lvgl/src/extra/widgets/obj/ out/utils/lvgl/src/extra/widgets/line/ out/utils/lvgl/src/extra/widgets/msgbox/ out/utils/lvgl/src/extra/widgets/spinner/ out/utils/lvgl/src/extra/widgets/tabview/ out/utils/lvgl/src/extra/widgets/tileview/ out/utils/lvgl/src/extra/widgets/canvas/ out/utils/lvgl/src/extra/widgets/img/ out/utils/lvgl/src/extra/widgets/btnmatrix/ out/utils/lvgl/src/extra/widgets/keyboard/ out/utils/lvgl/src/extra/widgets/calendar/ out/utils/lvgl/src/extra/widgets/switch/ out/utils/lvgl/src/extra/widgets/btn/ out/utils/lvgl/src/extra/widgets/checkbox/ out/utils/lvgl/src/extra/widgets/slider/ out/utils/lvgl/src/extra/widgets/meter/ out/utils/lvgl/src/extra/widgets/label/ out/utils/lvgl/src/extra/widgets/win/ out/utils/lvgl/src/extra/widgets/imgbtn/ out/utils/lvgl/src/extra/widgets/arc/ out/utils/lvgl/src/extra/widgets/textarea/ out/utils/lvgl/src/extra/widgets/dropdown/ out/utils/lvgl/src/extra/widgets/bar/ out/utils/lvgl/src/extra/widgets/chart/ out/utils/lvgl/src/extra/widgets/led/ out/utils/lvgl/src/extra/widgets/roller/ out/utils/lvgl/src/extra/layouts/flex/  out/utils/lvgl/src/extra/layouts/grid/ out/utils/lvgl/src/extra/themes/default/ out/utils/lvgl/src/extra/themes/basic/ out/utils/lv_drivers/wayland/

%.o: %.c out/generated/device_config.h
	@echo "CC $<"
	@$(CC) $(CFLAGS) -c $< -o $@

out/%.o: %.c out/generated/device_config.h
	@echo "CC $<"
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp out/generated/device_config.h
	@echo "CXX $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

out/%.o: %.cpp out/generated/device_config.h
	@echo "CXX $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

out/generated/device_config.h: out rd-$(DEVICE)
	@echo "GEN $@"
	@sh tools/gen_config_h.sh out/rd/env.sh $@

rd-base: $(BIN)
	@echo "BUILDRD base"
	@cp -P prebuilts/* out/rd/bin/
	@cp scripts/* out/rd/
	@cp $(BIN) out/rd/bin/

rd-device: out
	@echo "BUILDRD $(DEVICE)"
	@echo "DEBUG=$(DEBUG)" >> out/rd/env.sh
ifeq ($(UNIVERSAL),true)
	@echo "GEN_HEADER=false" >> out/rd/env.sh
endif

rd-default: rd-device
	@cat devices/$(DEVICE)/env.sh >> out/rd/env.sh

include devices.mk

# Test if there is an device rule present. If not, use the default.
ifneq ($(shell make -qf tools/dummy.mk rd-$(DEVICE) 2>/dev/null; test $$? -le 1 && echo ok),ok)
rd-$(DEVICE): rd-default
endif

out/rd.cpio: rd-base
	@echo "CPIO out/rd"
	@(cd out/rd/ && find . | cpio -o -H newc > ../rd.cpio)

out/rd.cpio.gz: out/rd.cpio
	@echo "GZIP out/rd.cpio"
	@gzip -k out/rd.cpio

$(BIN): $(OBJS) $(MAINOBJ)
	@echo "LD $(BIN)"
	@$(CC) -o $(BIN) $(MAINOBJ) $(AOBJS) $(COBJS) $(LDFLAGS)

clean:
	@echo "CLEAN"
	@rm -rf $(BIN) $(OBJS) $(MAINOBJ) $(OUT)

CXXSRCS += first_stage_init.cpp

DEPPATH += --dep-path boot/android/SAR
VPATH += :boot/android/SAR

CFLAGS += "-Iboot/android/SAR"

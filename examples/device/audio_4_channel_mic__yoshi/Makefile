include ../../build_system/make/make.mk

INC += \
  src \
  $(TOP)/hw \
  drivers \


# Example source
EXAMPLE_SOURCE += \
  src/main.c \
  src/usb_descriptors.c \
  src/adxl355.c \
  src/app_pin_mux.c \
  drivers/fsl_edma.c \
  drivers/fsl_lpspi.c \
  drivers/fsl_lpspi_edma.c \

SRC_C += $(addprefix $(CURRENT_PATH)/, $(EXAMPLE_SOURCE))

include ../../build_system/make/rules.mk

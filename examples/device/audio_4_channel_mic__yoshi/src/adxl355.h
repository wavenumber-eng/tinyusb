#ifndef ADXL355_H
#define ADXL355_H

#include "stdint.h"
#include "fsl_gpio.h"


#define ADXL33X_DEVID_AD                       0x00 
#define ADXL33X_DEVID_MST                      0x01 
#define ADXL33X_PARTID                         0x02 
#define ADXL33X_REVID                          0x03 
#define ADXL33X_STATUS                         0x04 
#define ADXL33X_FIFO_ENTRIES                   0x05 
#define ADXL33X_TEMP2 		                   0x06 
#define ADXL33X_TEMP1                          0x07 
#define ADXL33X_XDATA3                         0x08 
#define ADXL33X_XDATA2                         0x09 
#define ADXL33X_XDATA1                         0x0A 
#define ADXL33X_YDATA3                         0x0B 
#define ADXL33X_YDATA2                         0x0C 
#define ADXL33X_YDATA1                         0x0D 
#define ADXL33X_ZDATA3                         0x0E 
#define ADXL33X_ZDATA2                         0x0F 
#define ADXL33X_ZDATA1                         0x10 
#define ADXL33X_FIFO_DATA                      0x11 
#define ADXL33X_OFFSET_X_H                     0x1E 
#define ADXL33X_OFFSET_X_L                     0x1F 
#define ADXL33X_OFFSET_Y_H                     0x20 
#define ADXL33X_OFFSET_Y_L                     0x21 
#define ADXL33X_OFFSET_Z_H                     0x22 
#define ADXL33X_OFFSET_Z_L                     0x23 
#define ADXL33X_ACT_EN                         0x24 
#define ADXL33X_ACT_THRESH_H 			       0x25 
#define ADXL33X_ACT_THRESH_L 			       0x26 
#define ADXL33X_ACT_COUNT 		               0x27 
#define ADXL33X_FILTER                         0x28 
#define ADXL33X_FIFO_SAMPLES                   0x29 
#define ADXL33X_INT_MAP                        0x2A 
#define ADXL33X_SYNC                           0x2B 
#define ADXL33X_RANGE                          0x2C 
#define ADXL33X_POWER_CTL                      0x2D 
#define ADXL33X_SELF_TEST                      0x2E 
#define ADXL33X_RESET                          0x2F 


void ADXL355__init(void);
void ADXL355__crunch(void);


#endif /* ADXL355_H */
#ifndef BMMA7455L_H
#define BMMA7455L_H


#include <stdio.h>
#include <stdlib.h>

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <stdint.h>


#define MMA7455L 0x1D //Endereço I2C do Ci MMA7455L (I2C adress of MMA7455lL)

// Sensibilidade
// Sensitivity

#define S_2g 0x04
#define S_4g 0x08 
#define S_8g 0x00

// MODES

#define STAND_BY 0x00
#define MENSUREMENT 0x01
#define LEVEL_DETECTION 0x02
#define PULSE_DETECTION 0x03

int startI2C(int *file, char bus);
int finishI2C(int *file);
int configureMMA7455L(int *file, char MODE, char SENSITIVITY);
int reciveXYZ(int *file, char *xyz);
int reciveTemperature(int *file, char *temp);
int getXYZ(int *file, int16_t *x, int16_t *y, int16_t *z);
int getTemp(int *file, int8_t *temp);
int startMMA7455L(int *file, char MODE, char SENSITIVITY, char bus);


#endif
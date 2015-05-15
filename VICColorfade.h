#ifndef VICCOLORFADE_H_INCLUDED
#define VICCOLORFADE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct VICColorfade_tag  VICColorfade_t;
typedef enum VICColorfadeMode_tag VICColorfadeMode_t;
typedef enum VICColorfadeErrorno_tag VICColorfadeErrorno_t;

VICColorfade_t *VICColorfadeNew(uint8_t startcolor, uint8_t endcolor, VICColorfadeMode_t mode, uint8_t speed);
VICColorfade_t *VICColorfadeObjAlloc(void);
VICColorfadeErrorno_t VICColorfadeSetLimits(uint8_t startcolor, uint8_t endcolor);
VICColorfadeErrorno_t VICColorfadeSetSpeed(uint8_t speed);
VICColorfadeErrorno_t VICColorfadeSetMode(uint8_t mode);

#endif // VICCOLORFADE_H_INCLUDED

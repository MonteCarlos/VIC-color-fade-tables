#ifndef VICCOLORFADE_H_INCLUDED
#define VICCOLORFADE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

enum VICColorfadeErrorNo_tag{
	VICCOLORFADEERR_OK = 0,
	VICCOLORFADEERR_CHARMODEANDCOLORGT7;
};

typedef struct VICColorfade_tag  VICColorfade_t;
typedef enum VICColorfadeMode_tag VICColorfadeMode_t;
//typedef enum VICColorfadeErrorno_tag VICColorfadeErrorno_t;
typedef int8_t VICColorfadeErrorNo_t;

VICColorfade_t *VICColorfadeNew(uint8_t startcolor, uint8_t endcolor, VICColorfadeMode_t mode, uint8_t speed);
VICColorfade_t *VICColorfadeObjAlloc(void);
VICColorfadeErrorNo_t VICColorfadeSetLimits(VICColorfade_t *vcf, uint8_t startcolor, uint8_t endcolor);
VICColorfadeErrorNo_t VICColorfadeSetSpeed(VICColorfade_t *vcf, uint8_t speed);
VICColorfadeErrorNo_t VICColorfadeSetMode(VICColorfade_t *vcf, uint8_t mode);

#endif // VICCOLORFADE_H_INCLUDED

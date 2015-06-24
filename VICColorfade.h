#ifndef VICCOLORFADE_H_INCLUDED
#define VICCOLORFADE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t VICColorfadeTableElement_t;

enum VICColorfadeErrorNo_tag{
	VICCOLORFADEERR_OK = 0,
	VICCOLORFADEERR_CHARMODEANDCOLORGT7, //charmode only allows colors from 0..7
	VICCOLORFADEERR_CVALUE //common error on color value (>15 or >7 dependent on mode)
};

enum VICColorfadeState_tag{
    VICCOLORFADE_NOTSTARTED,
    VICCOLORFADE_INCOMPLETE,
    VICCOLORFADE_COMPLETE
};


typedef struct VICColorfade_tag  VICColorfade_t;
typedef enum VICColorfadeMode_tag VICColorfadeMode_t;
//typedef enum VICColorfadeErrorno_tag VICColorfadeErrorno_t;
typedef int8_t VICColorfadeErrorNo_t;
typedef char[] VICColorfadeErrorMsg_t;

VICColorfade_t *VICColorfadeNew(uint8_t startcolor, uint8_t endcolor, VICColorfadeMode_t mode, uint8_t speed);
VICColorfade_t *VICColorfadeObjAlloc(void);
VICColorfadeErrorNo_t VICColorfadeSetLimits(VICColorfade_t *vcf, uint8_t startcolor, uint8_t endcolor);
VICColorfadeErrorNo_t VICColorfadeSetSpeed(VICColorfade_t *vcf, uint8_t speed);
VICColorfadeErrorNo_t VICColorfadeSetMode(VICColorfade_t *vcf, uint8_t mode);
VICColorfadeTableElement_t VICColorfadeGetNextColor(VICColorfade_t *vcf);
VICColorfadeErrorNo_t VICColorfadeSetNewEndcolor(VICColorfade_t *vcf, uint8_t endcolor);
VICColorfadeErrorNo_t VICColorfadeToggleColors(VICColorfade_t *vcf);

#endif // VICCOLORFADE_H_INCLUDED

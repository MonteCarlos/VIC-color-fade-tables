#include "VICColorfade_internal.h"

VICColorfade_t *VICColorfadeNew(uint8_t startcolor, uint8_t endcolor, VICColorfadeMode_t mode, uint8_t speed){
	VICColorfade_t *vcf = VICColorfadeObjAlloc();
	VICColorfadeSetLimits(startcolor, endcolor);
	VICColorfadeSetSpeed(speed);
	VICColorfadeSetMode(mode);
}

#include "VICColorfade_internal.h"

VICColorfade_t *VICColorfadeNew(uint8_t startcolor, uint8_t endcolor, VICColorfadeMode_t mode, uint8_t speed){


	VICColorfade_t *vcf = VICColorfadeObjAlloc();
	VICColorfadeSetMode(vcf, mode);
	VICColorfadeSetLimits(vcf, startcolor, endcolor);
	VICColorfadeSetSpeed(vcf, speed);
	vcf->delay = 0;
	vcf->counter = 127;
	return vcf;
}

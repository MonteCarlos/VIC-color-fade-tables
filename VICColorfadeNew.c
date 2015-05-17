#include "VICColorfade_internal.h"

VICColorfade_t *VICColorfadeNew(uint8_t startcolor, uint8_t endcolor, VICColorfadeMode_t mode, uint8_t speed){
	uint16_t tableOffset;

	VICColorfade_t *vcf = VICColorfadeObjAlloc();
	VICColorfadeSetMode(vcf, mode);
	VICColorfadeSetLimits(vcf, startcolor, endcolor);
	VICColorfadeSetSpeed(vcf, speed);

	if (endcolor < 8){
		tableOffset = (16*16+16*16+8*8)*endcolor;
		switch(mode){
		case VICCOLORFADE_CHARMODE:
			tableOffset += 512+8*startcolor;
			break;
		case VICCOLORFADE_OLDVIC:
			tableOffset += 256+16*startcolor;
			break;
		case VICCOLORFADE_NEWVIC:
			tableOffset += 16*startcolor;
			break;
		}
	}else{
		tableOffset = (16*16+16*16+8*8)*8+512*endcolor+16*startcolor;
		switch(mode){
		case VICCOLORFADE_OLDVIC:
			tableOffset += 256;
			break;
		}
	}
	VICColorfadeSetReadPtr(vcf, tableOffset+VICColorfadeTables);
	return vcf;
}

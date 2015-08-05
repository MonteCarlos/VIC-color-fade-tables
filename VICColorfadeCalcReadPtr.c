#include "VICColorfade_internal.h"

VICColorfadeErrorNo_t VICColorfadeCalcReadPtr(VICColorfade_t *vcf){
	uint16_t tableOffset = 8*vcf->startcolor;

	if (vcf->endcolor < 8){
		tableOffset += (16*8+16*8+8*8)*vcf->endcolor;
		switch(vcf->mode){
		case VICCOLORFADE_CHARMODE:
			tableOffset += 256;
			break;
		case VICCOLORFADE_OLDVIC:
			tableOffset += 128;
			break;
        default: break;
		}
	}else{
		tableOffset += (16*8+16*8+8*8)*8+256*(vcf->endcolor-8);
		switch(vcf->mode){
		case VICCOLORFADE_OLDVIC:
			tableOffset += 128;
			break;
        default: break;
		}
	}
	VICColorfadeSetReadPtr(vcf, tableOffset+VICColorfadeTables);
	vcf->state = VICCOLORFADE_NOTSTARTED;
	return VICCOLORFADEERR_OK;
}

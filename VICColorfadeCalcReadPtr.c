#include "VICColorfade_internal.h"

VICColorfadeErrorNo_t VICColorfadeCalcReadPtr(VICColorfade_t *vcf){
	uint16_t tableOffset;

	if (vcf->endcolor < 8){
		tableOffset = (16*8+16*8+8*8)*vcf->endcolor+8*vcf->startcolor;
		switch(vcf->mode){
		case VICCOLORFADE_CHARMODE:
			tableOffset += 256;
			break;
		case VICCOLORFADE_OLDVIC:
			tableOffset += 128;
			break;
		case VICCOLORFADE_NEWVIC:
			//tableOffset += 8*vcf->startcolor;
			break;
		}
	}else{
		tableOffset = (16*8+16*8+8*8)*8+256*(vcf->endcolor-8)+8*vcf->startcolor;
		switch(vcf->mode){
		case VICCOLORFADE_OLDVIC:
			tableOffset += 128;
			break;
		}
	}
	VICColorfadeSetReadPtr(vcf, tableOffset+VICColorfadeTables);
	return VICCOLORFADEERR_OK;
}

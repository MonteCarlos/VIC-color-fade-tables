#include "VICColorfade_internal.h"

VICColorfadeErrorNo_t VICColorfadeSetNewEndcolor(VICColorfade_t *vcf, uint8_t endcolor){
	if (endcolor<16){
		vcf->startcolor = vcf->endcolor;
		vcf->endcolor = endcolor;
	}
	else return VICCOLORFADEERR_CHARMODEANDCOLORGT7;

	VICColorfadeCalcReadPtr(vcf);
	return VICCOLORFADEERR_OK;
}


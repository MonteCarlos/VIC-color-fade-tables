#include "VICColorfade_internal.h"

VICColorfadeErrorNo_t VICColorfadeSetNewEndcolor(VICColorfade_t *vcf, uint8_t endcolor){
	if (VICColorfadeCheckColorValue(endcolor)){
		vcf->startcolor = vcf->endcolor;
		vcf->endcolor = endcolor;
	}
	else return VICCOLORFADEERR_CVALUE;

	VICColorfadeCalcReadPtr(vcf);
	return VICCOLORFADEERR_OK;
}


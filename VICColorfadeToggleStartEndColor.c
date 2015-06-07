#include "VICColorfade_internal.h"

VICColorfadeErrorNo_t VICColorfadeToggleColors(VICColorfade_t *vcf){
	VICColorfadeTableElement_t tempColor = vcf->startcolor;
	vcf->startcolor = vcf->endcolor;
	vcf->endcolor = tempColor;

	VICColorfadeCalcReadPtr(vcf);
	return VICCOLORFADEERR_OK;
}


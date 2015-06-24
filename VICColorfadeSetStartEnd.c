#include "VICColorfade_internal.h"

VICColorfadeErrorNo_t VICColorfadeSetLimits(VICColorfade_t *vcf, uint8_t startcolor, uint8_t endcolor){
	if (VICColorfadeCheckColorValue(vcf->mode, startcolor)) vcf->startcolor = startcolor;
	else return VICCOLORFADEERR_CVALUE;

	if (VICColorfadeCheckColorValue(vcf->mode, endcolor)) vcf->endcolor = endcolor;
	else return VICCOLORFADEERR_CVALUE;

	VICColorfadeCalcReadPtr(vcf);
	return VICCOLORFADEERR_OK;
}

#include "VICColorfade_internal.h"

VICColorfadeErrorNo_t VICColorfadeSetLimits(VICColorfade_t *vcf, uint8_t startcolor, uint8_t endcolor){
	if (startcolor<16) vcf->startcolor = startcolor;
	if (endcolor<16) vcf->endcolor = endcolor;
	return VICCOLORFADEERR_OK;
}

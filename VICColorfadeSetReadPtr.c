
#include "VICColorfade_internal.h"

VICColorfadeErrorNo_t VICColorfadeSetReadPtr(VICColorfade_t *vcf, VICColorfadeTableElement_t *addr){
	vcf->elementPtr = addr;
	return VICCOLORFADEERR_OK;
}



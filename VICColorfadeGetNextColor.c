
#include "VICColorfade_internal.h"

VICColorfadeTableElement_t VICColorfadeGetNextColor(VICColorfade_t *vcf){
	//static uint16_t delay = 0;

	if ( (vcf->counter -= vcf->speed) <= 0){
		vcf->counter += 128;

		if (*vcf->elementPtr != vcf->endcolor){
				vcf->state = VICCOLORFADE_INCOMPLETE;
			return *vcf->elementPtr++;
		}
		vcf->state = VICCOLORFADE_COMPLETE;
		return vcf->endcolor;
	}else{
		return *vcf->elementPtr;
	}

}

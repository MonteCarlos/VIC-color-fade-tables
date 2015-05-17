
#include "VICColorfade_internal.h"

VICColorfadeTableElement_t VICColorfadeGetNextColor(VICColorfade_t *vcf){
	static uint16_t delay = 0;

	if ( (delay+=vcf->speed) >= 256){
		delay -= 256;

		if (*vcf->elementPtr != vcf->endcolor){
			return *vcf->elementPtr++;
		}
		return vcf->endcolor;
	}else{
		return *vcf->elementPtr;
	}

}

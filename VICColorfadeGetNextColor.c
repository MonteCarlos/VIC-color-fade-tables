
#include "VICColorfade_internal.h"

VICColorfadeTableElement_t VICColorfadeGetNextColor(VICColorfade_t *vcf){
	if (*vcf->elementPtr != vcf->endcolor){
		return (*vcf->elementPtr)++;
	}
	return vcf->endcolor;
}

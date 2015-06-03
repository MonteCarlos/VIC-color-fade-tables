#include "VICColorfade_internal.h"

VICColorfade_t *VICColorfadeObjAlloc(void){
	return ccAlloc(sizeof(VICColorfade_t));
}

void VICColorfadeObjDelete(VICColorfade_t *vcf){
	ccFree(vcf);
}

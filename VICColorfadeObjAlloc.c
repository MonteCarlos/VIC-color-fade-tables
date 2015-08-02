#include "VICColorfade_internal.h"

VICColorfade_t *VICColorfadeObjAlloc(void){
	return ccAlloc(sizeof(VICColorfade_t));
}

ccFree_t VICColorfadeObjDelete(VICColorfade_t *vcf){
	return ccFree(vcf);
}

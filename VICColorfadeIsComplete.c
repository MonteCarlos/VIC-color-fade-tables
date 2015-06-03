#include "VICColorfade_internal.h"

bool VICColorfadeIsComplete(VICColorfade_t *vcf){
	return vcf->state == VICCOLORFADE_COMPLETE;
}

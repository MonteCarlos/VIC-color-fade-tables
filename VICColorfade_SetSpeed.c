
#include "VICColorfade_internal.h"

VICColorfadeErrorNo_t VICColorfadeSetSpeed(VICColorfade_t *vcf, uint8_t speed){
	vcf->speed = speed;
	return VICCOLORFADEERR_OK;
}

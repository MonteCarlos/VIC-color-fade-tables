
#include "VICColorfade_internal.h"

VICColorfadeErrorNo_t VICColorfadeSetMode(VICColorfade_t *vcf, uint8_t mode){
	if(VICColorfadeCheckMode(mode)){
        vcf->mode = mode;
        return VICCOLORFADEERR_OK;
	}
    return VICCOLORFADEERR_ILLMODE;
}


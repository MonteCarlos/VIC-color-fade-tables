#include "VICColorfade_internal.h"

bool VICColorfadeCheckMode(VICColorfadeMode_t mode){
    return MCLib_chkIntRng(mode, VICCOLORFADE_MODE_MIN, VICCOLORFADE_MODE_MAX);
}


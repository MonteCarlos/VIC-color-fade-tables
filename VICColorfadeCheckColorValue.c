bool VICColorfadeCheckColorValue(VICColorfadeMode_t mode, VICColorfadeTableElement_t color){
    VICColorfadeTableElement_t maxColorValue = VICCOLORFADE_CHARMODE==mode?7:15;

    return color <= maxColorValue;
}


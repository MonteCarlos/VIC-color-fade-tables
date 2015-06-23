bool VICColorfadeCheckColorValue(VICColorfadeMode_t mode, VICColorfadeTableElement_t color){
if (endcolor<16){
		vcf->startcolor = vcf->endcolor;
		vcf->endcolor = endcolor;
	}
	else return VICCOLORFADEERR_CHARMODEANDCOLORGT7;

}


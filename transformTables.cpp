#include <iostream>
extern "C"{
 #include "coltab.c"//include complete source with color tables
}

using namespace std;

int main(void){
    VICColorfade_t *vcf = VICColorfadeNew(0,0,0,64);
    size_t modeMax = 3;

    for (size_t destColor = 0; destColor < 16; ++destColor){
        modeMax = 3;
        if (destColor >= 8){
            --modeMax;
        }
        for (size_t mode = 0; mode < modeMax; ++mode){
            VICColorfadeSetMode(vcf, mode);
            switch (mode){
            case 2:
                for (size_t startColor = 0; startColor < 8; ++startColor){
                    VICColorfadeSetLimits(vcf, startColor, destColor);
                    VICColorfadeCalcReadPtr(vcf);
                    do{
                        cout << VICColorfadeGetNextColor(vcf);
                    }while(!VICColorfadeIsComplete(vcf));
                }

            default:
                for (size_t startColor = 0; startColor < 16; ++startColor){
                    VICColorfadeSetLimits(vcf, startColor, destColor, mode);
                    VICColorfadeCalcReadPtr(vcf);
                    do{
                        cout << VICColorfadeGetNextColor(vcf);
                    }while(!VICColorfadeIsComplete(vcf));
                }

            }
        }

    }
    VICColorfadeObjDelete(vcf);
}

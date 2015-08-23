#include <stdio.h>
#include "coltab.c"//include complete source with color tables

//using namespace std;
uint16_t destOffsets[16]; //32
uint8_t modeOffsets[16][3]; //48
uint8_t startOffsets[16][3][16]; //768
//uint8_t destTable[10000];

uint8_t palette[16] = {0,15,4,12,5,9,1,13,6,2,10,3,7,14,8,11};
//1.: 0 6 9 11 2 4 8 12 14 5 10 15 3 7 13 1
/*
00,
1d, 3c, 42, 90,
29, 00,
3c, 42, 90,
42, 90,
58, 29, 00,
60,
7f, 58, 29, 00,
82, 90,
90,
a8, 29, 00,
b9, 00,
c4, 29, 00,
d3, c4, 29, 00,
e4, 29, 00,
f5, 82, 90,

00,
17, 3e, 42, b0,
2b, 00,
3e, 42, b0,
42, b0,
58, 9b, 00,
6b, 00,
73, e4, 2b, 00,
89, b0,
9b, 00,
a4, 2b, 00,
b0,
c6, b0,
df, a4, 2b, 00,
e4, 2b, 00,
fa, 42, b0,

00, 00, 00, 00,
17,
26, 00, 00, 00,
35, 42, 60, 00,
42, 60, 00, 00,
54, 26, 00, 00,
60, 00, 00, 00,
73, 54, 26, 00,
06, b4, c3, d1,*/
int main(void){
    //VICColorfade_t *vcf = VICColorfadeNew(0,0,0,64);
    size_t modeMax = 3;
    size_t destIdx = 0;
    uint8_t *readPtr = &VICColorfadeTables[0];


    for (size_t destColor = 0; destColor < 5; ++destColor){
        printf("uint8_t VICColorfadeTable_FadeTo%d = {", destColor);

        destOffsets[destColor] = destIdx;
        modeMax = 3;
        if (destColor >= 8){
            --modeMax;
        }
        for (size_t mode = 0; mode < modeMax; ++mode){
            assert(256 > destIdx-destOffsets[destColor]);
            modeOffsets[destColor][mode] = destIdx-destOffsets[destColor];
            //VICColorfadeSetMode(vcf, mode);
            switch (mode){
            case 2:
                for (size_t startColor = 0; startColor < 8; ++startColor){
                    //VICColorfadeSetLimits(vcf, startColor, destColor);
                    //VICColorfadeCalcReadPtr(vcf);
                    assert(256 > destIdx-(destOffsets[destColor]+modeOffsets[destColor][mode]));
                    startOffsets[destColor][mode][startColor] = destIdx-(destOffsets[destColor]+modeOffsets[destColor][mode]);
                    for (size_t fadePos =0; fadePos < 4; ++fadePos){

                        printf("%x%x /*%x%x*/, ",palette[readPtr[0]],palette[readPtr[1]],readPtr[0],readPtr[1]);
                        destIdx += 1;

                        if ((destColor == readPtr[0]) || (destColor == readPtr[1])) {
                            readPtr += 2*(4-fadePos);
                            break;
                        }
                        readPtr += 2;
                    }
                    printf("\n");
                }
                printf("\n");

                break;

            default:
                for (size_t startColor = 0; startColor < 16; ++startColor){
                    //VICColorfadeSetLimits(vcf, startColor, destColor);
                    //VICColorfadeCalcReadPtr(vcf);
                    assert(256 > destIdx-(destOffsets[destColor]+modeOffsets[destColor][mode]));
                    startOffsets[destColor][mode][startColor] = destIdx-(destOffsets[destColor]+modeOffsets[destColor][mode]);

                    for (size_t fadePos =0; fadePos < 4; ++fadePos){

                        printf("%x%x /*%x%x*/, ",palette[readPtr[0]],palette[readPtr[1]],readPtr[0],readPtr[1]);
                        destIdx += 1;

                        if ((destColor == readPtr[0]) || (destColor == readPtr[1])) {
                            readPtr += 2*(4-fadePos);
                            break;
                        }
                        readPtr+=2;
                    }
                    printf("\n");
                }
                printf("\n");
            }
        }
        printf("}\n\n");
    }

    printf("uint16_t endColorOffsets[] = {");
    for (size_t destColor = 0; destColor < 16; ++destColor){
        printf("%d,",destOffsets[destColor]);
    }

    printf("};\n\n uint8_t modeOffsets[] = {");

    for (size_t destColor = 0; destColor < 16; ++destColor){
        modeMax = 3;
        if (destColor >= 8){
            --modeMax;
        }
        printf("\n{");
        for (size_t mode = 0; mode< modeMax; ++mode){
            printf("%d",modeOffsets[destColor][mode]);
            if (mode != modeMax) printf(",");
        }
        printf("}");
    }

    printf("};\n\n uint8_t startColorOffsets[] = {");

    for (size_t destColor = 0; destColor < 16; ++destColor){
        modeMax = 3;
        if (destColor >= 8){
            --modeMax;
        }
        for (size_t mode = 0; mode< modeMax; ++mode){
            printf("%d,",startOffsets[destColor][mode][startColor]);
        }
    }

    printf("};\n\n");
//    VICColorfadeObjDelete(vcf);
}

#include <stdio.h>
#include "coltab.c"//include complete source with color tables

//using namespace std;
uint16_t destOffsets[16]; //32
uint8_t modeOffsets[16*3]; //48
uint8_t startOffsets[16*3*16]; //768
//uint8_t destTable[10000];

uint8_t palette[16] = {0,15,4,12,5,9,1,13,6,2,10,3,7,14,8,11};
//1.: 0 6 9 11 2 4 8 12 14 5 10 15 3 7 13 1
size_t destIdx = 0;
uint8_t *readPtr = &VICColorfadeTables[0];

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

typedef uint16_t getElementFnc_t(void** elem);
typedef getElementFnc_t *getElementFnc_Ptr;

uint16_t getuint8(void **byte){
    uint8_t tByte = (uint8_t)(*(uint8_t*)*byte);
    uint8_t **ptr = (uint8_t**)byte;
    ++(*ptr);
    return tByte;
}

uint16_t getuint16(void **word){
    uint16_t tWord = (uint16_t)(*(uint16_t*)*word);
    uint16_t **ptr = (uint16_t**)word;
    ++(*ptr);
    return tWord;
}

int printList(char* format, void *list, getElementFnc_Ptr getElem, size_t n, size_t perLine){
    uint16_t elem;
    size_t i;

    for (i = 0; i<n-1;++i){
        if (0 == i%perLine){
            printf("\n\t");
            elem = getElem(&list);
            continue;
        }
        elem = getElem(&list);
        printf(format, elem);
        printf(", ");
    }

    if (0 != i%perLine){
        elem = getElem(&list);
        printf(format, elem);
    }

    return EXIT_SUCCESS;
}


int printArray(char* format, void *arr, getElementFnc_Ptr getElem, size_t n, size_t perLine){
    uint16_t elem;
    assert (n!=0);
    printf("{");
    for (size_t i = 0; i<n-1;++i){
        if (0 == i%perLine){
            printf("\n\t");
        }
        elem = getElem(&arr);
        printf(format, elem);
        printf(", ");
    }
    elem = getElem(&arr);
    printf(format, elem);
    printf("\n}");
    return EXIT_SUCCESS;
}

uint8_t combineNibbles(uint8_t left, uint8_t right){
    assert((left < 16)&&(right < 16));
    return left*16+right;
}

uint8_t combineNibblesWithPalette(uint8_t left, uint8_t right){
    assert((left < 16)&&(right < 16));
    return palette[left]*16+palette[right];
}

int printColorSeq(uint8_t destColor){
    uint8_t colorByte_Pal;
    uint8_t colorByte_noPal;

    for (size_t fadePos =0; fadePos < 4; ++fadePos){
        colorByte_Pal = combineNibblesWithPalette(readPtr[0], readPtr[1]);
        colorByte_noPal = combineNibbles(readPtr[0], readPtr[1]);

        printf("%2x /*%2x*/, ",colorByte_Pal, colorByte_noPal);
        destIdx += 1;

        if ((destColor == readPtr[0]) || (destColor == readPtr[1])) {
            readPtr += 2*(4-fadePos);
            break;
        }

        readPtr += 2;
    }
    printf("\n");
    return EXIT_SUCCESS;
}

int pushDestColorOffset(void){
    static size_t destColor = 0;
    destOffsets[destColor++] = destIdx;
    return EXIT_SUCCESS;
}

int pushModeOffset(size_t destOffset){
    static size_t pushPos = 0;
    assert(256 > destIdx-destOffset);
    modeOffsets[pushPos++] = destIdx-destOffset;
    return EXIT_SUCCESS;
}

int pushStartOffset(size_t destOffset){
    static size_t pushPos = 0;
    assert(256 > destIdx-destOffset);
    startOffsets[pushPos++] = destIdx-destOffset;
    return EXIT_SUCCESS;
}

int main(void){
    //VICColorfade_t *vcf = VICColorfadeNew(0,0,0,64);
    size_t modeMax = 3;
    uintptr_t modeOffsetIdx = 0;
    uintptr_t startOffsetIdx = 0;
    size_t saveDestIdx;
    uint8_t maxColor;

    printf("uint8_t VICColorfadeTables = {");

    for (size_t destColor = 0; destColor < 16; ++destColor){
        //printf("uint8_t VICColorfadeTables_FadeTo%d = {", destColor);

        pushDestColorOffset();

        destOffsets[destColor] = destIdx;
        modeMax = 3;
        if (destColor >= 8){
            --modeMax;
        }
        for (size_t mode = 0; mode < modeMax; ++mode){
            saveDestIdx = destIdx;
            pushModeOffset(destOffsets[destColor]);
            //VICColorfadeSetMode(vcf, mode);
            switch (mode){
            case 2:
                for (size_t startColor = 0; startColor < 8; ++startColor){
                    //VICColorfadeSetLimits(vcf, startColor, destColor);
                    //VICColorfadeCalcReadPtr(vcf);
                    pushStartOffset(saveDestIdx);
                    //assert(256 > destIdx-(destOffsets[destColor]+modeOffsets[modeOffsetIdx]));
                    //startOffsets[destColor][mode][startColor] = destIdx-(destOffsets[destColor]+modeOffsets[destColor][mode]);
                    printColorSeq(destColor);
                    ++startOffsetIdx;
                }
                printf("\n");

                break;

            default:
                for (size_t startColor = 0; startColor < 16; ++startColor){
                    //VICColorfadeSetLimits(vcf, startColor, destColor);
                    //VICColorfadeCalcReadPtr(vcf);
                    pushStartOffset(saveDestIdx);
                    //assert(256 > destIdx-(destOffsets[destColor]+modeOffsets[destColor][mode]));
                    //startOffsets[destColor][mode][startColor] = destIdx-(destOffsets[destColor]+modeOffsets[destColor][mode]);

                    printColorSeq(destColor);
                    ++startOffsetIdx;
                }
                printf("\n");
            }
            ++modeOffsetIdx;
        }
        //printf("}\n\n");
    }
    printf("}\n\n");

    printf("/**** %d Bytes ****/\n\n", destIdx);

    printf("uint16_t endColorOffsets[] = ");
    printArray("%d", destOffsets, getuint16, 16,8);

    printf(";\n");
    printf("/**** 32 bytes ****/\n\n");
    printf("uint8_t modeOffsets[] = {");
    readPtr = &modeOffsets[0];


    for (size_t destColor = 0; destColor < 16; ++destColor){
        //modeMax = 3;
        if (destColor < 8){
            //--modeMax;
            printList("%d", &modeOffsets[3*destColor], getuint8, 2*8, 3);

        }else{
            printList("%d", &modeOffsets[2*destColor+24], getuint8, 3*8, 2);
        }
        /*readPtr++;
        printList("%d", &modeOffsets[24], getuint8, 2*8, 2);

        for (size_t mode = 1; mode< modeMax; ++mode){
            printf("%2x, ",*readPtr++);
        }*/
    }
    printf("};\n\n");
    printf("/**** %d Bytes ****/\n\n", (uintptr_t)readPtr-(uintptr_t)&modeOffsets[0]);
    printf("uint8_t startColorOffsets[] = {");

    readPtr = &startOffsets[0];
    for (size_t destColor = 0; destColor < 16; ++destColor){
        modeMax = 3;
        if (destColor >= 8){
            --modeMax;
        }
        for (size_t mode = 0; mode< modeMax; ++mode){
            maxColor = mode==2?8:16;
            readPtr++;
            for (size_t startColor = 1; startColor < maxColor; ++startColor ){
                printf("%2x, ",*readPtr++);
            }
        }
    }
    printf("};\n\n");
    printf("/**** %d Bytes ****/\n\n", (uintptr_t)readPtr-(uintptr_t)&startOffsets[0]);

//    VICColorfadeObjDelete(vcf);
}

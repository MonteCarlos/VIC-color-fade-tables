#include "VICColorfade_internal.h"
#include <conio.h>
#include <cbm.h>
#include <stdbool.h>
#include <time.h>

extern uint8_t VICColorfadeTables[];

int main()
{
    static uint8_t endcolors[] = {1,5,13,4,12,2,14,6,7,0,3,11};
    uint8_t endcolorIdx = 0;
    VICColorfade_t *vcf = VICColorfadeNew(0,endcolors[0],0,32);
	clock_t tick;

    VIC.bgcolor0 = 0;
    while(!kbhit());
    cgetc();
    while(true){
		while(VIC.ctrl1 < 128);
		while(VIC.ctrl1 > 128);
		if (endcolors[endcolorIdx] == (VIC.bgcolor0 = VICColorfadeGetNextColor(vcf))){
			VICColorfadeSetNewEndcolor(vcf, endcolors[++endcolorIdx]);
			//++endcolorIdx;
			tick = clock();
			while(clock()-tick < CLOCKS_PER_SEC);
		};

    }
    return 0;
}

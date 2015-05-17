#include "VICColorfade_internal.h"
#include <conio.h>
#include <cbm.h>
#include <stdbool.h>
#include <time.h>

extern uint8_t VICColorfadeTables[];

int main()
{
    static uint8_t endcolors[] = {1,5,13,4,10,2,14,6,7,0,3,11,15,12,9,8};
    uint8_t endcolorIdx = 0;
    VICColorfade_t *vcf = VICColorfadeNew(0,endcolors[0],1,64);
	clock_t tick;

    VIC.bordercolor = VIC.bgcolor0 = 0;
    clrscr();
	while(!kbhit());
	cgetc();
    while(true){

		while(VIC.ctrl1 < 128);
		while(VIC.ctrl1 > 128);
		VIC.bgcolor0 = VICColorfadeGetNextColor(vcf);
		if (VICColorfadeIsComplete(vcf)){
			VICColorfadeSetNewEndcolor(vcf, endcolors[++endcolorIdx]);
			if (endcolorIdx == (sizeof(endcolors)/sizeof(endcolors[0])-1)) endcolorIdx = ~0;
			//++endcolorIdx;
			tick = clock();
			while(abs(clock()-tick) < CLOCKS_PER_SEC);
			//while(!kbhit());
			//cgetc();
		};

    }
    return 0;
}

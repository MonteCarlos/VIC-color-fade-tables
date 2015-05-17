#include "VICColorfade_internal.h"
#include <conio.h>
#include <cbm.h>
#include <stdbool.h>

extern uint8_t VICColorfadeTables[];

int main()
{
    VICColorfade_t *vcf = VICColorfadeNew(0,1,0,128);
    VIC.bgcolor0 = 0;
    while(!kbhit());
    cgetc();
    while(true){
		while(VIC.ctrl1 < 128);
		while(VIC.ctrl1 > 128);
		VIC.bgcolor0 = VICColorfadeGetNextColor(vcf);
    }
    return 0;
}

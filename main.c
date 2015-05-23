#include "VICColorfade_internal.h"
#include <conio.h>
#include <cbm.h>
#include <stdbool.h>
#include <time.h>

extern uint8_t VICColorfadeTables[];

int createChoice(char *text){
	static uint8_t NumberOfChoices = 0;
	static char format[] = "%d: %s\n";

	switch(NumberOfChoices){
	case 10:
		printf("Too many entries!");
		return -1;
	default:
		printf(format, NumberOfChoices, text);
	}

	return ++NumberOfChoices;
}

int menu(void){
	uint8_t NumberOfEntries;
	char keyPressed;

	createChoice("Old VIC");
	createChoice("New VIC");
	NumberOfEntries = createChoice("Charmode");

	while(!kbhit());
	keyPressed = cgetc();
	if (keyPressed < '9'+1){
		if (keyPressed > '0'-1){
			return keyPressed - '0';
		}
	}
	return -1;
}

int main()
{
    static uint8_t endcolors[] = {1,5,13,4,10,2,14,6,7,0,3,11,15,12,9,8};
    uint8_t endcolorIdx = 0;
    VICColorfade_t *vcf;
	int8_t mode = -1;
	clock_t tick;

    VIC.bordercolor = VIC.bgcolor0 = 0;
    clrscr();

    mode = menu();
	vcf = VICColorfadeNew(0,endcolors[0],mode,64);

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

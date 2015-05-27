#include "VICColorfade_internal.h"
#include <conio.h>
#include <cbm.h>
#include <stdbool.h>
#include <time.h>

#define FADEMINSTEP 4

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

void tableFader(VICColorfade_t *vcf){
	static uint8_t endcolorIdx = 0;
	static uint8_t endcolors[] = {1,5,13,4,10,2,14,6,7,0,3,11,15,12,9,8};

	VICColorfadeSetNewEndcolor(vcf, endcolors[++endcolorIdx]);
	if (endcolorIdx == (sizeof(endcolors)/sizeof(endcolors[0])-1)) endcolorIdx = ~0;

}

void randFader(VICColorfade_t *vcf){
	static uint8_t colortableSorted[] = {0,6,9,11,2,4,8,12,14,10,5,15,3,7,13,1};
	static uint8_t colortableSortedcm[] = {0,6,2,4,5,3,7,1};
	static uint8_t lastColorIdx = 0;
	uint8_t endColorIdx = 0;
	unsigned int randVal;

	if (lastColorIdx >= FADEMINSTEP){
		if (lastColorIdx < 16-FADEMINSTEP){

			randVal = rand()%(16-2*FADEMINSTEP+1);
			if (randVal <= lastColorIdx-FADEMINSTEP){
				endColorIdx = randVal;
			}else{
				endColorIdx = randVal+(2*FADEMINSTEP-1);
			}

		}else{

			endColorIdx = rand()%(lastColorIdx-FADEMINSTEP+1);
		}
	}else{

		endColorIdx = rand()%(16-(lastColorIdx+FADEMINSTEP))+lastColorIdx+FADEMINSTEP;
	}
	lastColorIdx = endColorIdx;
	VICColorfadeSetNewEndcolor(vcf, colortableSorted[endColorIdx]);
	//printf("%d\n", endColorIdx);
}

int main()
{
    static uint8_t colortableBright[] = {1,13,7,3,15,10,14,5};
    static uint8_t colortableDark[] = {0,9,6,4,12,8,11,2};

    VICColorfade_t *vcf;
	int8_t mode = -1;
	clock_t tick;

    VIC.bordercolor = VIC.bgcolor0 = 0;
    clrscr();
	srand(3);
    mode = menu();
	vcf = VICColorfadeNew(0,0,mode,64);

    while(true){

		while(VIC.ctrl1 < 128);
		while(VIC.ctrl1 > 128);
		VIC.bgcolor0 = VICColorfadeGetNextColor(vcf);
		if (VICColorfadeIsComplete(vcf)){
			//tableFader(vcf);
			randFader(vcf);
			//++endcolorIdx;
			tick = clock();
			while(abs(clock()-tick) < CLOCKS_PER_SEC);
			//while(!kbhit());
			//cgetc();
		};

    }
    return 0;
}

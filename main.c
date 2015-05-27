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

void randFader2(VICColorfade_t *vcf){

	//colortable contains four sections with 4 darkest colors, next 4 brighter colors, ..., 4 brightest colors
	//fades are performed only between non adjacent sections
	static uint8_t colortable[][4] = {{0,6,9,11},
									 {2,4,8,12},
									 {14,10,5,15},
									 {3,7,13,1}};

	static uint8_t tableIdx=0;
	unsigned int randNr, randNr2;

	randNr = rand()/(RAND_MAX/2);//rand()%2;//
	//(2*rand())/(RAND_MAX+1);
	randNr2 = rand()/(RAND_MAX/4);//rand()%4;//
	//(4*rand())/(RAND_MAX+1);

	switch(tableIdx){
	case 0:
		tableIdx = randNr+2;
		break;
	case 1:
		tableIdx = 3;
		break;
	case 2:
		tableIdx = 0;
		break;
	case 3:
		tableIdx = randNr;
		break;
	}
	VICColorfadeSetNewEndcolor(vcf, colortable[tableIdx][randNr2]);

	//printf("%u, %u\n", randNr, randNr2);
}

int main()
{
    VICColorfade_t *vcf;
	int8_t mode = -1;
	clock_t tick;

    VIC.bordercolor = VIC.bgcolor0 = 0;
    clrscr();
	srand(time(NULL));
    mode = menu();
	vcf = VICColorfadeNew(0,0,mode,64);

    while(true){

		while(VIC.ctrl1 < 128);
		while(VIC.ctrl1 > 128);
		VIC.bgcolor0 = VICColorfadeGetNextColor(vcf);
		if (VICColorfadeIsComplete(vcf)){
			//tableFader(vcf);
			randFader2(vcf);
			//++endcolorIdx;
			tick = clock();
			while(abs(clock()-tick) < CLOCKS_PER_SEC);
			//while(!kbhit());
			//cgetc();
		};

    }
    return 0;
}

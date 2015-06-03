#include "VICColorfade_internal.h"
#include <conio.h>
#include <cbm.h>
#include <stdbool.h>
#include <time.h>

#define FADEMINSTEP 4
typedef void menufnc_t(void);
typedef bool fgvOperation_t;
enum FGVOPERATIONENUM{FGV_MINOP=-1, FGV_SET = true, FGV_GET = false, FGV_MAXOP=2};

#define ID(x) x
#define _CONCAT(x,y) x##y
#define CONCAT(x,y) _CONCAT(ID(x),ID(y))
#define MCONCAT(x,...) MCONCAT(x,__VA_ARGS__)

#define MENUBASELIST() M("Old VIC", MENU_OLDVIC, setOldVIC) M("New VIC",MENU_NEWVIC, setNewVIC),\
		 M("Charmode",MENU_CHARMODE, setCharmode),\
		 M("Start random demo",MENU_RANDSTART), M("Set start color",MENU_SETSTARTCOLOR),\
		 M("Set end color",MENU_SETENDCOLOR)

#define M(x,y) x,
#define MENUSTRINGLIST MENUBASELIST ""
#undef M

#define M(x,y) y,
#define MENUIDLIST MENUBASELIST MENU_NOID
#undef M

#pragma charmap('_', ' ')



extern uint8_t VICColorfadeTables[];

char getNumKey(void){
	char keyPressed;

	while(!kbhit());
	keyPressed = cgetc();
	if (keyPressed < '9'+1){
		if (keyPressed > '0'-1){
			return keyPressed-'0';
		}
	}
	return 255; //non valid key!
}

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

void fgvAssist(fgvOperation_t op, uint8_t N, void *src, void *dest){
    static VICColorfadeMode_t mode = VICCOLORFADE_NEWVIC;
	va_list va;
	va_start(va, op);
	switch(op){
	case FGV_SET:

		mode = va_arg(va, VICColorfadeMode_t);
		//slide through is OK, here
	case FGV_GET:
		return mode;
	}
	va_end(va);
}

VICColorfadeMode_t fgvMode(fgvOperation_t op, ...){
	static VICColorfadeMode_t mode = VICCOLORFADE_NEWVIC;
	va_list va;
	va_start(va, op);
	switch(op){
	case FGV_SET:

		mode = va_arg(va, VICColorfadeMode_t);
		//slide through is OK, here
	case FGV_GET:
		return mode;
	}
	va_end(va);
}

VICColorfadeMode_t fgvStartColor(fgvOperation_t op, ...){
	static VICColorfadeTableElement_t startColor = 0;
	va_list va;
	va_start(va, op);
	switch(op){
	case FGV_SET:

		startColor = va_arg(va, VICColorfadeTableElement_t);
		//slide through is OK, here
	case FGV_GET:
		return startColor;
	}
	va_end(va);
}

VICColorfadeMode_t fgvEndColor(fgvOperation_t op, ...){
	static VICColorfadeTableElement_t endColor = 1;
	va_list va;
	va_start(va, op);
	switch(op){
	case FGV_SET:
		endColor = va_arg(va, VICColorfadeTableElement_t);
		//slide through is OK, here
	case FGV_GET:
		return endColor;
	}
	va_end(va);
}

void menufncSetOldVIC(void){
	fgvMode(FGV_SET, VICCOLORFADE_OLDVIC);
}

void menufncSetNewVIC(void){
	fgvMode(FGV_SET, VICCOLORFADE_NEWVIC);
}

void menufncSetCharmode(void){
	fgvMode(FGV_SET, VICCOLORFADE_CHARMODE);
}

void menufncRandDemo(void){
}

void menufncCustomFade(void){
}

void menufncSetStartColor(void){
	uint8_t startColor;

	gotoxy(0, 24);
	cclear(40);
	gotoxy(0, 24);
	fputs("Startcolor?", stdout);
	startColor = getNumKey();
	putchar(startColor+'0');
	fgvStartColor(FGV_SET, startColor);
}

void menufncSetEndColor(void){
	uint8_t endColor;

	gotoxy(0, 24);
	cclear(40);
	gotoxy(0, 24);
	fputs("Endcolor?", stdout);
	endColor = getNumKey();
	putchar(endColor+'0');
	fgvEndColor(FGV_SET, endColor);
}

void statusLine(void){
	gotoxy(0, 24);
	cclear(40);
	gotoxy(0, 24);
	printf("Mode: %d, Startcolor: %d, Endcolor: %d", fgvMode(FGV_GET), fgvStartColor(FGV_GET), fgvEndColor(FGV_GET));
}

int menu(void){
	typedef struct{
		char *title;
		menufnc_t *callback;
	} menu_t;

	uint8_t NumberOfEntries, i;
	char keyPressed;
	static menu_t menuentries[] = {
		{"Old VIC", menufncSetOldVIC},
		{"New VIC", menufncSetNewVIC},
		{"Charmode",menufncSetCharmode},
		{"Start random demo",menufncRandDemo},
		{"Start custom fade",menufncCustomFade},
		{"Set start color",menufncSetStartColor},
		{"Set end color",menufncSetEndColor},
	};
	//uint8_t x,y;

	//wherey();
	for (i = 0; i < sizeof(menuentries)/sizeof(menuentries[0]); ++i){
		createChoice(menuentries[i].title);
	}

	while(true){
		statusLine();

		while(!kbhit());
		keyPressed = cgetc();
		if (keyPressed < '9'+1){
			if (keyPressed > '0'-1){
				menuentries[keyPressed - '0'].callback();
				//return keyPressed - '0';
			}
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

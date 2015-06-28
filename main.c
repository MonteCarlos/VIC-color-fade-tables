#include "VICColorfade_internal.h"
#include <conio.h>
#include <cbm.h>
#include <stdbool.h>
#include <time.h>
#include <timer/timer.h>
#include <raster/raster.h>
#include <CBMkey/cbmkey.h>
#include <conio/conio+.h>

#define FADEMINSTEP 4
typedef void menufnc_t(void);
typedef bool fgvOperation_t;
enum FGVOPERATIONENUM{FGV_MINOP=-1, FGV_SET = true, FGV_GET = false, FGV_MAXOP=2};
void randFader2(VICColorfade_t *vcf);
void statusLine(void);
uint8_t isError = 0;
char nullStr[] = "";
char* errMsg = nullStr;

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

#define ERRMSGLIST LE(ok), LE(color_out_of_range)
#define LE(x) CONCAT(ERRMSG_,x)
enum {ERRMSGLIST} ERRMSGTAGS;
#undef LE
#define LE(x) #x
char *errmsgs[] = {ERRMSGLIST};
#undef LE

extern uint8_t VICColorfadeTables[];

/*char getNumKey(void){
	char keyPressed;

	keyPressed = cbm_getkey();
	if (keyPressed < '9'+1){
		if (keyPressed > '0'-1){
			return keyPressed-'0';
		}
	}
	return 255; //non valid key!
}
*/


bool wasError(){
    return isError;
}

bool wasNoError(){
    return !isError;
}

void setError(void){
    errMsg = nullStr; //no msg given, so clear it and only indicate error
	isError = 1;
}

void clearError(void){
    errMsg = nullStr; //clear error indicator and msg
	isError = 0;
}

void setErrorMsg(char* msg){
	setError(); //set error indicator and message
	errMsg = msg;
}

int createChoice(char *text){
	static uint8_t NumberOfChoices = 0;
	static char format[] = "%d: %s\n\r";

	switch(NumberOfChoices){
	case 10:
		cprintf("Too many entries!");
		return -1;
	default:
		cprintf(format, NumberOfChoices, text);
	}

	return ++NumberOfChoices;
}

void fgvAssist(fgvOperation_t op, uint8_t size, void *src, void* dest){
    //assert(N < 4); //for performance reasons copy only max 3 bytes
	//uint8_t i;
    //va_list va;
    //va_start(va, dest);
    //(uint8_t*)dest += size-1;

	switch(op){
	case FGV_SET:
        for (; size!=0; --size){
            /*((uint8_t*)dest)++*/ *((uint8_t*)dest)++ = *((uint8_t*)src)++;//va_arg(va, uint8_t);
            //++(uint8_t*)dest;
        }
		//slide through is OK, here
	}
	//va_end(va);
}

VICColorfadeMode_t fgvMode(fgvOperation_t op, VICColorfadeMode_t desiredMode){
	static VICColorfadeMode_t mode = VICCOLORFADE_NEWVIC;
	//va_list va_start(va, op);

	fgvAssist(op, sizeof(mode), &desiredMode, &mode);

	return mode;
}

/*
VICColorfadeTableElement_t fgvColor(fgvOperation_t op, VICColorfadeTableElement_t *value, VICColorfadeTableElement_t *dest){
    switch(fgvMode(FGV_GET,0)){
	case VICCOLORFADE_CHARMODE:
		fgvAssist(op, sizeof(startColorcm), &va_arg(va, VICColorfadeTableElement_t), &startColorcm);
		return startColorcm;
	default:
		fgvAssist(op, sizeof(startColor), &va_arg(va, VICColorfadeTableElement_t), &startColor);
		return startColor;
	}

}*/

VICColorfadeTableElement_t fgvStartColor(fgvOperation_t op, ...){
	static VICColorfadeTableElement_t startColor = 0;
	static VICColorfadeTableElement_t startColorcm = 0;
    VICColorfadeTableElement_t *colorPtr = (fgvMode(FGV_GET,0)==VICCOLORFADE_CHARMODE)?&startColorcm:&startColor;

	va_list va;
	va_start(va, op);

	switch(op){
    case FGV_SET:
        {
            VICColorfadeTableElement_t colorParam = va_arg(va, VICColorfadeTableElement_t);
            if(VICColorfadeCheckColorValue(fgvMode(FGV_GET,0), colorParam)){
                *colorPtr = colorParam;
            }else{
                setErrorMsg("Color value error");
            }
        }
	}

	return *colorPtr;
}

VICColorfadeTableElement_t fgvEndColor(fgvOperation_t op, ...){
	static VICColorfadeTableElement_t endColor = 1;
	static VICColorfadeTableElement_t endColorcm = 1;
    VICColorfadeTableElement_t *colorPtr = (fgvMode(FGV_GET,0)==VICCOLORFADE_CHARMODE)?&endColorcm:&endColor;

	va_list va;
	va_start(va, op);

	switch(op){
    case FGV_SET:
        {
            VICColorfadeTableElement_t colorParam = va_arg(va, VICColorfadeTableElement_t);
            if(VICColorfadeCheckColorValue(fgvMode(FGV_GET,0), colorParam)){
                *colorPtr = colorParam;
            }else{
                setErrorMsg("Color value error");
            }
        }
	}

	return *colorPtr;
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
    VICColorfade_t *vcf = VICColorfadeNew(0,0,fgvMode(FGV_GET,0),64);
	uint8_t oldStartcolor = fgvStartColor(FGV_GET);
	uint8_t oldEndcolor = fgvEndColor(FGV_GET);

	statusLine();

    srand(time(NULL));

    cbm_flushKeyBuf();

    while(!kbhit()){
        waitretrace();

		VIC.bgcolor0 = VICColorfadeGetNextColor(vcf);
		if (VICColorfadeIsComplete(vcf)){
			//tableFader(vcf);
			randFader2(vcf);
			fgvStartColor(FGV_SET, vcf->startcolor);
			fgvEndColor(FGV_SET, vcf->endcolor);
			statusLine();
			//++endcolorIdx;
			msDelay(1000);
			//while(!kbhit());
			//cgetc();
		};

    }
    VIC.bordercolor = VIC.bgcolor0 = 0;
    fgvStartColor(FGV_SET, oldStartcolor);
	fgvEndColor(FGV_SET, oldEndcolor);
}

void menufncCustomFade(void){
	VICColorfade_t *vcf;

	vcf = VICColorfadeNew(fgvStartColor(FGV_GET),fgvEndColor(FGV_GET),fgvMode(FGV_GET,0),64);

	cbm_flushKeyBuf();

    while(!kbhit()){

		waitretrace();
		VIC.bgcolor0 = VICColorfadeGetNextColor(vcf);
		if (VICColorfadeIsComplete(vcf)){
			//tableFader(vcf);
			VICColorfadeToggleColors(vcf);
			//++endcolorIdx;
			msDelay(1000);
			//while(!kbhit());
			//cgetc();
		};

    }

}

void menufncSetStartColor(void){
	VICColorfadeTableElement_t startColor;

	cclearline(24);
	cputs("Startcolor?");
	startColor = cbm_getNumKey();

	putchar(fgvStartColor(FGV_SET, startColor)+'0');
}

void menufncSetEndColor(void){
	VICColorfadeTableElement_t endColor;

	cclearline(24);
	cputs("Endcolor?");
    endColor = cbm_getNumKey();

    putchar(fgvEndColor(FGV_SET, endColor)+'0');
}

void statusLine(void){
	cclearline(23);
	cprintf("Mode: %d, Startcolor: %d, Endcolor: %d\n\r", fgvMode(FGV_GET,0), fgvStartColor(FGV_GET), fgvEndColor(FGV_GET));
	cclearline(24);
	cprintf("Err: %d, %s", isError, errMsg);
	clearError();
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
		VIC.bordercolor = VIC.bgcolor0 = 0;
		statusLine();


		//while(!kbhit());
		//keyPressed = cgetc();
		//if (keyPressed < '9'+1){
			//if (keyPressed > '0'-1){
		if ( (keyPressed = cbm_getNumKey()) < sizeof(menuentries)/sizeof(menuentries[0]) ) menuentries[keyPressed].callback();
				//return keyPressed - '0';
		//	}
		//}

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
	typedef uint8_t endcolortable_t[4][4];

	//colortable contains four sections with 4 darkest colors, next 4 brighter colors, ..., 4 brightest colors
	//fades are performed only between non adjacent sections
	static endcolortable_t colortable = {{0,6,9,11},
									 {2,4,8,12},
									 {14,10,5,15},
									 {3,7,13,1}};

	//same as above, but for charmode
	static endcolortable_t colortable2 = {{0,6,0,0},
									 {2,4,0,0},
									 {3,5,0,0},
									 {7,1,0,0}};
	static uint8_t tableIdx=0;
	unsigned int randNr, randNr2;
	uint8_t *colortablePtr;

	randNr = rand()/(RAND_MAX/2);//rand()%2;//
	//(2*rand())/(RAND_MAX+1);


	//rand()%4;//
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

	switch (vcf->mode){
	case VICCOLORFADE_CHARMODE:
		randNr2 = rand()/(RAND_MAX/2);
		colortablePtr = &colortable2[tableIdx][randNr2];
		break;
	default:
		randNr2 = rand()/(RAND_MAX/4);
		colortablePtr = &colortable[tableIdx][randNr2];
	}

	if (VICCOLORFADEERR_OK != VICColorfadeSetNewEndcolor(vcf, *colortablePtr ) ){
		setError();
	};

	//printf("%u, %u\n", randNr, randNr2);
}

int main()
{
    VIC.bordercolor = VIC.bgcolor0 = 0;
    clrscr();
	menu();

    return 0;
}

#ifndef VICCOLORFADE_INTERNAL_H_INCLUDED
#define VICCOLORFADE_INTERNAL_H_INCLUDED

	#include "VICColorfade.h"
	#define ccAlloc(size) malloc(size)
	#define ccFree(ptr) free(ptr)


	extern VICColorfadeTableElement_t VICColorfadeTables[];
	typedef int8_t VICColorfadeState_t;


	//Enums should not emit values out of -128..127
	enum VICColorfadeMode_tag{
		VICCOLORFADE_OLDVIC,
		VICCOLORFADE_NEWVIC,
		VICCOLORFADE_CHARMODE,
	};


	struct VICColorfade_tag{
		uint8_t startcolor;
		uint8_t endcolor;
		uint8_t speed;
		uint8_t delay;
		int16_t counter;
		VICColorfadeState_t state;
		VICColorfadeMode_t mode;

		uint8_t *elementPtr;
		VICColorfadeErrorNo_t errorNo;
		VICColorfadeErrorMsg_t *errorMsg;
	};

	VICColorfadeErrorNo_t VICColorfadeSetReadPtr(VICColorfade_t *vcf, VICColorfadeTableElement_t *addr);
	VICColorfadeErrorNo_t VICColorfadeCalcReadPtr(VICColorfade_t *vcf);
	bool VICColorfadeIsComplete(VICColorfade_t *vcf);
#endif // __VICCOLORFADE_INTERNAL_H__

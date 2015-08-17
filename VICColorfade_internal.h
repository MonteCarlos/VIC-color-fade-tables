#ifndef VICCOLORFADE_INTERNAL_H_INCLUDED
#define VICCOLORFADE_INTERNAL_H_INCLUDED
    #include <MCLib.h>
	#include "VICColorfade.h"
	#ifdef UTEST
        #define ccAlloc(size) CuAlloc(size)
        #define ccFree(ptr) CuFree(ptr)
        #include <CuAlloc/CuAlloc.h>
    #else
        #define ccAlloc(size) malloc(size)
        #define ccFree(ptr) free(ptr)
    #endif

	extern VICColorfadeTableElement_t VICColorfadeTables[];
	typedef int8_t VICColorfadeState_t;
    typedef bool ccFree_t;
    typedef int8_t VICColorfadeCounter_t;
    typedef uint8_t VICColorfadeDelay_t;
    typedef uint8_t VICColorfadeSpeed_t;

	//Enums should not emit values out of -128..127
	enum VICColorfadeMode_tag{
	    VICCOLORFADE_MODE_MIN,
		VICCOLORFADE_OLDVIC = VICCOLORFADE_MODE_MIN,
		VICCOLORFADE_NEWVIC,
		VICCOLORFADE_CHARMODE,
		VICCOLORFADE_MODE_MAX = VICCOLORFADE_CHARMODE
	};


	struct VICColorfade_tag{
		VICColorfadeTableElement_t startcolor;
		VICColorfadeTableElement_t endcolor;
		VICColorfadeSpeed_t speed;
        VICColorfadeDelay_t delay;
		VICColorfadeCounter_t counter;
		VICColorfadeState_t state;
		VICColorfadeMode_t mode;

		VICColorfadeTableElement_t *elementPtr;
		VICColorfadeErrorNo_t errorNo;
		VICColorfadeErrorMsg_t *errorMsg;
	};

	VICColorfadeErrorNo_t VICColorfadeSetReadPtr(VICColorfade_t *vcf, VICColorfadeTableElement_t *addr);
	VICColorfadeErrorNo_t VICColorfadeCalcReadPtr(VICColorfade_t *vcf);
	bool VICColorfadeIsComplete(VICColorfade_t *vcf);
	bool VICColorfadeObjDelete(VICColorfade_t *vcf);
    bool VICColorfadeCheckMode(VICColorfadeMode_t mode);

#endif // __VICCOLORFADE_INTERNAL_H__

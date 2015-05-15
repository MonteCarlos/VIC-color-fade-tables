#ifndef VICCOLORFADE_INTERNAL_H_INCLUDED
#define VICCOLORFADE_INTERNAL_H_INCLUDED

	#include "VICColorfade.h"

	enum VICColorfadeMode_tag{
		VICCOLORFADE_OLDVIC,
		VICCOLORFADE_NEWVIC,
		VICCOLORFADE_CHARMODE,
	};

	struct VICColorfade_tag{
		uint8_t startcolor;
		uint8_t endcolor;
		uint8_t speed;
		VICColorfadeMode_t mode;
	};
#endif // __VICCOLORFADE_INTERNAL_H__

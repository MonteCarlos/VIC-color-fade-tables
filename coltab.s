;The table takes account of hue, so f.e. red to white is a completely different chain than blue to white!!!

;up to now each chain contains 8 colours. if the destination color needs only fewer steps, it is repeated until length equals 8
;total size: 8*(16*8+16*8+8*8)+8*(32*8) = 4608 bytes = $1200!
;save 8*(3*16)+8*(2*16) = 640 bytes by removing start color
;say on average, last color is repeated 4 times. keep it only one time:
;we save 8*(3*3*16)+8*(2*3*16)=72+48=1920 bytes -> sumup: 2560 bytes, 55%
;table for start offsets(16 bit table offset, 8 bit startcolor offset): (3*2+2*2)*8+(3*16+2*16)*8 = 80+640=720 bytes
;ideas: remove unnecessary repetitions of same color code at end of each chain
;		transform color codes to brightness sorted color codes and use delta rle compression

.EXPORT _VICColorfadeTables = *
.EXPORT _nVICColorfadeTable_toBlack = *
.BYTE $00,$00,$00,$00,$00,$00,$00,$00,$01,$0d,$03,$0c,$04,$02,$09,$00,$02,$09,$00,$00,$00,$00,$00,$00,$03,$0c,$04,$02,$09,$00,$00,$00,$04,$02,$09,$00,$00,$00,$00,$00,$05,$08,$02,$09,$00,$00,$00,$00,$06,$00,$00,$00,$00,$00,$00,$00,$07,$0f,$05,$08,$02,$09,$00,$00,$08,$02,$09,$00,$00,$00,$00,$00,$09,$00,$00,$00,$00,$00,$00,$00,$0a,$08,$02,$09,$00,$00,$00,$00,$0b,$09,$00,$00,$00,$00,$00,$00,$0c,$04,$02,$09,$00,$00,$00,$00,$0d,$03,$0c,$04,$02,$09,$00,$00,$0e,$04,$02,$09,$00,$00,$00,$00,$0f,$05,$08,$02,$09,$00,$00,$00
.EXPORT _oVICColorfadeTable_toBlack = *
.BYTE $00,$00,$00,$00,$00,$00,$00,$00,$01,$07,$03,$0e,$04,$02,$0b,$00,$02,$0b,$00,$00,$00,$00,$00,$00,$03,$0e,$04,$02,$0b,$00,$00,$00,$04,$02,$0b,$00,$00,$00,$00,$00,$05,$08,$09,$0b,$00,$00,$00,$00,$06,$0b,$00,$00,$00,$00,$00,$00,$07,$03,$0e,$04,$02,$0b,$00,$00,$08,$09,$0b,$00,$00,$00,$00,$00,$09,$0b,$00,$00,$00,$00,$00,$00,$0a,$04,$02,$0b,$00,$00,$00,$00,$0b,$00,$00,$00,$00,$00,$00,$00,$0c,$06,$0b,$00,$00,$00,$00,$00,$0d,$0f,$0a,$04,$02,$0b,$00,$00,$0e,$04,$02,$0b,$00,$00,$00,$00,$0f,$0a,$04,$02,$0b,$00,$00,$00
.EXPORT _VICColorfadeTable_toBlack_cm = *
.BYTE $00,$00,$00,$00,$00,$00,$00,$00,$01,$07,$03,$05,$04,$02,$06,$00,$02,$06,$00,$00,$00,$00,$00,$00,$03,$05,$04,$02,$06,$00,$00,$00,$04,$02,$06,$00,$00,$00,$00,$00,$05,$04,$02,$06,$00,$00,$00,$00,$06,$00,$00,$00,$00,$00,$00,$00,$07,$03,$05,$04,$02,$06,$00,$00

.EXPORT _nVICColorfadeTable_toWhite = *
.BYTE $00,$06,$0b,$04,$0c,$03,$0d,$01,$01,$01,$01,$01,$01,$01,$01,$01,$02,$08,$0a,$0f,$07,$01,$01,$01,$03,$0d,$01,$01,$01,$01,$01,$01,$04,$0c,$03,$0d,$01,$01,$01,$01,$05,$03,$0d,$01,$01,$01,$01,$01,$06,$0b,$04,$0c,$03,$0d,$01,$01,$07,$01,$01,$01,$01,$01,$01,$01,$08,$0a,$0f,$07,$01,$01,$01,$01,$09,$02,$08,$0a,$0f,$07,$01,$01,$0a,$0f,$07,$01,$01,$01,$01,$01,$0b,$04,$0c,$03,$0d,$01,$01,$01,$0c,$03,$0d,$01,$01,$01,$01,$01,$0d,$01,$01,$01,$01,$01,$01,$01,$0e,$03,$0d,$01,$01,$01,$01,$01,$0f,$07,$01,$01,$01,$01,$01,$01
.EXPORT _oVICColorfadeTable_toWhite = *
.BYTE $00,$0b,$02,$04,$0e,$03,$0d,$01,$01,$01,$01,$01,$01,$01,$01,$01,$02,$04,$0e,$03,$0d,$01,$01,$01,$03,$0d,$01,$01,$01,$01,$01,$01,$04,$0e,$03,$0d,$01,$01,$01,$01,$05,$0f,$07,$01,$01,$01,$01,$01,$06,$02,$04,$0e,$03,$0d,$01,$01,$07,$01,$01,$01,$01,$01,$01,$01,$08,$05,$0f,$07,$01,$01,$01,$01,$09,$08,$05,$0f,$07,$01,$01,$01,$0a,$0f,$07,$01,$01,$01,$01,$01,$0b,$02,$04,$0e,$03,$0d,$01,$01,$0c,$08,$05,$0f,$07,$01,$01,$01,$0d,$01,$01,$01,$01,$01,$01,$01,$0e,$03,$07,$01,$01,$01,$01,$01,$0f,$07,$01,$01,$01,$01,$01,$01
.EXPORT _VICColorfadeTable_toWhite_cm = *
.BYTE $00,$06,$02,$04,$05,$03,$07,$01,$01,$01,$01,$01,$01,$01,$01,$01,$02,$04,$05,$03,$07,$01,$01,$01,$03,$07,$01,$01,$01,$01,$01,$01,$04,$05,$03,$07,$01,$01,$01,$01,$05,$03,$07,$01,$01,$01,$01,$01,$06,$02,$04,$05,$03,$07,$01,$01,$07,$01,$01,$01,$01,$01,$01,$01

.EXPORT _nVICColorfadeTable_toRed = *
.BYTE $00,$09,$02,$02,$02,$02,$02,$02,$01,$07,$0f,$0a,$08,$02,$02,$02,$02,$02,$02,$02,$02,$02,$02,$02,$03,$0c,$04,$02,$02,$02,$02,$02,$04,$02,$02,$02,$02,$02,$02,$02,$05,$04,$02,$02,$02,$02,$02,$02,$06,$0b,$02,$02,$02,$02,$02,$02,$07,$0f,$0a,$08,$02,$02,$02,$02,$08,$02,$02,$02,$02,$02,$02,$02,$09,$02,$02,$02,$02,$02,$02,$02,$0a,$08,$02,$02,$02,$02,$02,$02,$0b,$02,$02,$02,$02,$02,$02,$02,$0c,$04,$02,$02,$02,$02,$02,$02,$0d,$03,$0c,$04,$02,$02,$02,$02,$0e,$04,$02,$02,$02,$02,$02,$02,$0f,$0a,$08,$02,$02,$02,$02,$02
.EXPORT _oVICColorfadeTable_toRed = *
.BYTE $00,$0b,$09,$02,$02,$02,$02,$02,$01,$0d,$0e,$04,$02,$02,$02,$02,$02,$02,$02,$02,$02,$02,$02,$02,$03,$0e,$04,$02,$02,$02,$02,$02,$04,$02,$02,$02,$02,$02,$02,$02,$05,$0c,$02,$02,$02,$02,$02,$02,$06,$09,$02,$02,$02,$02,$02,$02,$07,$08,$02,$02,$02,$02,$02,$02,$08,$02,$02,$02,$02,$02,$02,$02,$09,$02,$02,$02,$02,$02,$02,$02,$0a,$08,$02,$02,$02,$02,$02,$02,$0b,$09,$02,$02,$02,$02,$02,$02,$0c,$02,$02,$02,$02,$02,$02,$02,$0d,$0e,$04,$02,$02,$02,$02,$02,$0e,$04,$02,$02,$02,$02,$02,$02,$0f,$04,$02,$02,$02,$02,$02,$02
.EXPORT _VICColorfadeTable_toRed_cm = *
.BYTE $00,$06,$02,$02,$02,$02,$02,$02,$01,$07,$03,$05,$04,$02,$02,$02,$02,$02,$02,$02,$02,$02,$02,$02,$03,$05,$04,$02,$02,$02,$02,$02,$04,$02,$02,$02,$02,$02,$02,$02,$05,$04,$02,$02,$02,$02,$02,$02,$06,$02,$02,$02,$02,$02,$02,$02,$07,$03,$05,$04,$02,$02,$02,$02

.EXPORT _nVICColorfadeTable_toCyan = *
.BYTE $00,$06,$0b,$04,$0c,$03,$03,$03,$01,$0d,$03,$03,$03,$03,$03,$03,$02,$04,$0c,$03,$03,$03,$03,$03,$03,$03,$03,$03,$03,$03,$03,$03,$04,$0c,$03,$03,$03,$03,$03,$03,$05,$03,$03,$03,$03,$03,$03,$03,$06,$0b,$04,$0c,$03,$03,$03,$03,$07,$0f,$03,$03,$03,$03,$03,$03,$08,$0c,$03,$03,$03,$03,$03,$03,$09,$02,$04,$0c,$03,$03,$03,$03,$0a,$0c,$03,$03,$03,$03,$03,$03,$0b,$04,$0c,$03,$03,$03,$03,$03,$0c,$03,$03,$03,$03,$03,$03,$03,$0d,$03,$03,$03,$03,$03,$03,$03,$0e,$03,$03,$03,$03,$03,$03,$03,$0f,$03,$03,$03,$03,$03,$03,$03
.EXPORT _oVICColorfadeTable_toCyan = *
.BYTE $00,$0b,$06,$0e,$03,$03,$03,$03,$01,$0d,$03,$03,$03,$03,$03,$03,$02,$04,$0e,$03,$03,$03,$03,$03,$03,$03,$03,$03,$03,$03,$03,$03,$04,$0e,$03,$03,$03,$03,$03,$03,$05,$03,$03,$03,$03,$03,$03,$03,$06,$0e,$03,$03,$03,$03,$03,$03,$07,$03,$03,$03,$03,$03,$03,$03,$08,$05,$03,$03,$03,$03,$03,$03,$09,$04,$0e,$03,$03,$03,$03,$03,$0a,$03,$03,$03,$03,$03,$03,$03,$0b,$06,$0e,$03,$03,$03,$03,$03,$0c,$0e,$03,$03,$03,$03,$03,$03,$0d,$03,$03,$03,$03,$03,$03,$03,$0e,$03,$03,$03,$03,$03,$03,$03,$0f,$03,$03,$03,$03,$03,$03,$03
.EXPORT _VICColorfadeTable_toCyan_cm = *
.BYTE $00,$06,$02,$04,$05,$03,$03,$03,$01,$07,$03,$03,$03,$03,$03,$03,$02,$04,$05,$03,$03,$03,$03,$03,$03,$03,$03,$03,$03,$03,$03,$03,$04,$05,$03,$03,$03,$03,$03,$03,$05,$03,$03,$03,$03,$03,$03,$03,$06,$02,$04,$05,$03,$03,$03,$03,$07,$03,$03,$03,$03,$03,$03,$03

.EXPORT _nVICColorfadeTable_toMag = *
.BYTE $00,$06,$0b,$04,$04,$04,$04,$04,$01,$0d,$03,$0c,$04,$04,$04,$04,$02,$04,$04,$04,$04,$04,$04,$04,$03,$0c,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$05,$0c,$04,$04,$04,$04,$04,$04,$06,$0b,$04,$04,$04,$04,$04,$04,$07,$0f,$0a,$04,$04,$04,$04,$04,$08,$04,$04,$04,$04,$04,$04,$04,$09,$02,$04,$04,$04,$04,$04,$04,$0a,$04,$04,$04,$04,$04,$04,$04,$0b,$04,$04,$04,$04,$04,$04,$04,$0c,$04,$04,$04,$04,$04,$04,$04,$0d,$03,$0c,$04,$04,$04,$04,$04,$0e,$04,$04,$04,$04,$04,$04,$04,$0f,$0a,$04,$04,$04,$04,$04,$04
.EXPORT _oVICColorfadeTable_toMag = *
.BYTE $00,$0b,$02,$0c,$04,$04,$04,$04,$01,$07,$0f,$0a,$04,$04,$04,$04,$02,$0c,$04,$04,$04,$04,$04,$04,$03,$05,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$05,$04,$04,$04,$04,$04,$04,$04,$06,$02,$0c,$04,$04,$04,$04,$04,$07,$0f,$0a,$04,$04,$04,$04,$04,$08,$04,$04,$04,$04,$04,$04,$04,$09,$0c,$04,$04,$04,$04,$04,$04,$0a,$04,$04,$04,$04,$04,$04,$04,$0b,$02,$0c,$04,$04,$04,$04,$04,$0c,$04,$04,$04,$04,$04,$04,$04,$0d,$0f,$0a,$04,$04,$04,$04,$04,$0e,$04,$04,$04,$04,$04,$04,$04,$0f,$0a,$04,$04,$04,$04,$04,$04
.EXPORT _VICColorfadeTable_toMag_cm = *
.BYTE $00,$06,$02,$04,$04,$04,$04,$04,$01,$07,$03,$05,$04,$04,$04,$04,$02,$04,$04,$04,$04,$04,$04,$04,$03,$05,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$05,$04,$04,$04,$04,$04,$04,$04,$06,$02,$04,$04,$04,$04,$04,$04,$07,$03,$05,$04,$04,$04,$04,$04

.EXPORT _nVICColorfadeTable_toGreen = *
.BYTE $00,$06,$0b,$04,$0c,$05,$05,$05,$01,$0d,$03,$05,$05,$05,$05,$05,$02,$08,$0c,$05,$05,$05,$05,$05,$03,$05,$05,$05,$05,$05,$05,$05,$04,$0c,$05,$05,$05,$05,$05,$05,$05,$05,$05,$05,$05,$05,$05,$05,$06,$0b,$04,$0c,$05,$05,$05,$05,$07,$0f,$05,$05,$05,$05,$05,$05,$08,$0c,$05,$05,$05,$05,$05,$05,$09,$02,$08,$0c,$05,$05,$05,$05,$0a,$0c,$05,$05,$05,$05,$05,$05,$0b,$04,$0c,$05,$05,$05,$05,$05,$0c,$05,$05,$05,$05,$05,$05,$05,$0d,$03,$05,$05,$05,$05,$05,$05,$0e,$05,$05,$05,$05,$05,$05,$05,$0f,$05,$05,$05,$05,$05,$05,$05
.EXPORT _oVICColorfadeTable_toGreen = *
.BYTE $00,$0b,$09,$0c,$05,$05,$05,$05,$01,$0d,$0f,$05,$05,$05,$05,$05,$02,$08,$05,$05,$05,$05,$05,$05,$03,$05,$05,$05,$05,$05,$05,$05,$04,$05,$05,$05,$05,$05,$05,$05,$05,$05,$05,$05,$05,$05,$05,$05,$06,$0c,$05,$05,$05,$05,$05,$05,$07,$0f,$05,$05,$05,$05,$05,$05,$08,$05,$05,$05,$05,$05,$05,$05,$09,$0c,$05,$05,$05,$05,$05,$05,$0a,$08,$05,$05,$05,$05,$05,$05,$0b,$09,$0c,$05,$05,$05,$05,$05,$0c,$05,$05,$05,$05,$05,$05,$05,$0d,$0f,$05,$05,$05,$05,$05,$05,$0e,$05,$05,$05,$05,$05,$05,$05,$0f,$05,$05,$05,$05,$05,$05,$05
.EXPORT _VICColorfadeTable_toGreen_cm = *
.BYTE $00,$06,$02,$04,$05,$05,$05,$05,$01,$07,$03,$05,$05,$05,$05,$05,$02,$04,$05,$05,$05,$05,$05,$05,$03,$05,$05,$05,$05,$05,$05,$05,$04,$05,$05,$05,$05,$05,$05,$05,$05,$05,$05,$05,$05,$05,$05,$05,$06,$02,$04,$05,$05,$05,$05,$05,$07,$03,$05,$05,$05,$05,$05,$05

.EXPORT _nVICColorfadeTable_toBlue = *
.BYTE $00,$06,$06,$06,$06,$06,$06,$06,$01,$0d,$03,$0e,$04,$0b,$06,$06,$02,$0b,$06,$06,$06,$06,$06,$06,$03,$0e,$04,$0b,$06,$06,$06,$06,$04,$0b,$06,$06,$06,$06,$06,$06,$05,$08,$0b,$06,$06,$06,$06,$06,$06,$06,$06,$06,$06,$06,$06,$06,$07,$0f,$0c,$04,$0b,$06,$06,$06,$08,$0b,$06,$06,$06,$06,$06,$06,$09,$0b,$06,$06,$06,$06,$06,$06,$0a,$08,$0b,$06,$06,$06,$06,$06,$0b,$06,$06,$06,$06,$06,$06,$06,$0c,$04,$0b,$06,$06,$06,$06,$06,$0d,$03,$0e,$04,$0b,$06,$06,$06,$0e,$04,$0b,$06,$06,$06,$06,$06,$0f,$0c,$04,$0b,$06,$06,$06,$06
.EXPORT _oVICColorfadeTable_toBlue = *
.BYTE $00,$0b,$06,$06,$06,$06,$06,$06,$01,$0d,$03,$0e,$06,$06,$06,$06,$02,$06,$06,$06,$06,$06,$06,$06,$03,$0e,$06,$06,$06,$06,$06,$06,$04,$09,$06,$06,$06,$06,$06,$06,$05,$04,$09,$06,$06,$06,$06,$06,$06,$06,$06,$06,$06,$06,$06,$06,$07,$0f,$0e,$06,$06,$06,$06,$06,$08,$09,$06,$06,$06,$06,$06,$06,$09,$06,$06,$06,$06,$06,$06,$06,$0a,$08,$09,$06,$06,$06,$06,$06,$0b,$06,$06,$06,$06,$06,$06,$06,$0c,$06,$06,$06,$06,$06,$06,$06,$0d,$03,$0e,$06,$06,$06,$06,$06,$0e,$06,$06,$06,$06,$06,$06,$06,$0f,$0e,$06,$06,$06,$06,$06,$06
.EXPORT _VICColorfadeTable_toBlue_cm = *
.BYTE $00,$06,$06,$06,$06,$06,$06,$06,$01,$07,$03,$05,$04,$02,$06,$06,$02,$06,$06,$06,$06,$06,$06,$06,$03,$05,$04,$02,$06,$06,$06,$06,$04,$02,$06,$06,$06,$06,$06,$06,$05,$04,$02,$06,$06,$06,$06,$06,$06,$06,$06,$06,$06,$06,$06,$06,$07,$03,$05,$04,$02,$06,$06,$06

.EXPORT _nVICColorfadeTable_toYellow = *
.BYTE $00,$09,$02,$08,$0a,$0f,$07,$07,$01,$07,$07,$07,$07,$07,$07,$07,$02,$08,$0a,$0f,$07,$07,$07,$07,$03,$0f,$07,$07,$07,$07,$07,$07,$04,$0a,$0f,$07,$07,$07,$07,$07,$05,$0f,$07,$07,$07,$07,$07,$07,$06,$0b,$04,$0a,$0f,$07,$07,$07,$07,$07,$07,$07,$07,$07,$07,$07,$08,$0a,$0f,$07,$07,$07,$07,$07,$09,$02,$08,$0a,$0f,$07,$07,$07,$0a,$0f,$07,$07,$07,$07,$07,$07,$0b,$04,$0a,$0f,$07,$07,$07,$07,$0c,$0f,$07,$07,$07,$07,$07,$07,$0d,$07,$07,$07,$07,$07,$07,$07,$0e,$0f,$07,$07,$07,$07,$07,$07,$0f,$07,$07,$07,$07,$07,$07,$07
.EXPORT _oVICColorfadeTable_toYellow = *
.BYTE $00,$0b,$0c,$08,$0f,$07,$07,$07,$01,$07,$07,$07,$07,$07,$07,$07,$02,$08,$0f,$07,$07,$07,$07,$07,$03,$07,$07,$07,$07,$07,$07,$07,$04,$0a,$0f,$07,$07,$07,$07,$07,$05,$0f,$07,$07,$07,$07,$07,$07,$06,$0e,$0f,$07,$07,$07,$07,$07,$07,$07,$07,$07,$07,$07,$07,$07,$08,$0f,$07,$07,$07,$07,$07,$07,$09,$08,$0f,$07,$07,$07,$07,$07,$0a,$0f,$07,$07,$07,$07,$07,$07,$0b,$0c,$08,$0f,$07,$07,$07,$07,$0c,$08,$0f,$07,$07,$07,$07,$07,$0d,$07,$07,$07,$07,$07,$07,$07,$0e,$0f,$07,$07,$07,$07,$07,$07,$0f,$07,$07,$07,$07,$07,$07,$07
.EXPORT _VICColorfadeTable_toYellow_cm = *
.BYTE $00,$06,$02,$04,$05,$03,$07,$07,$01,$07,$07,$07,$07,$07,$07,$07,$02,$04,$05,$03,$07,$07,$07,$07,$03,$07,$07,$07,$07,$07,$07,$07,$04,$05,$03,$07,$07,$07,$07,$07,$05,$03,$07,$07,$07,$07,$07,$07,$06,$02,$04,$05,$03,$07,$07,$07,$07,$07,$07,$07,$07,$07,$07,$07

.EXPORT _nVICColorfadeTable_toOrange = *
.BYTE $00,$09,$02,$08,$08,$08,$08,$08,$01,$07,$0f,$0c,$08,$08,$08,$08,$02,$08,$08,$08,$08,$08,$08,$08,$03,$0c,$08,$08,$08,$08,$08,$08,$04,$08,$08,$08,$08,$08,$08,$08,$05,$0c,$08,$08,$08,$08,$08,$08,$06,$0b,$04,$08,$08,$08,$08,$08,$07,$0f,$0c,$08,$08,$08,$08,$08,$08,$08,$08,$08,$08,$08,$08,$08,$09,$02,$08,$08,$08,$08,$08,$08,$0a,$08,$08,$08,$08,$08,$08,$08,$0b,$08,$08,$08,$08,$08,$08,$08,$0c,$08,$08,$08,$08,$08,$08,$08,$0d,$03,$0c,$08,$08,$08,$08,$08,$0e,$04,$08,$08,$08,$08,$08,$08,$0f,$0c,$08,$08,$08,$08,$08,$08
.EXPORT _oVICColorfadeTable_toOrange = *
.BYTE $00,$0b,$09,$0c,$08,$08,$08,$08,$01,$07,$0f,$08,$08,$08,$08,$08,$02,$08,$08,$08,$08,$08,$08,$08,$03,$0a,$08,$08,$08,$08,$08,$08,$04,$08,$08,$08,$08,$08,$08,$08,$05,$08,$08,$08,$08,$08,$08,$08,$06,$09,$0c,$08,$08,$08,$08,$08,$07,$0f,$08,$08,$08,$08,$08,$08,$08,$08,$08,$08,$08,$08,$08,$08,$09,$0c,$08,$08,$08,$08,$08,$08,$0a,$08,$08,$08,$08,$08,$08,$08,$0b,$09,$0c,$08,$08,$08,$08,$08,$0c,$08,$08,$08,$08,$08,$08,$08,$0d,$0f,$08,$08,$08,$08,$08,$08,$0e,$08,$08,$08,$08,$08,$08,$08,$0f,$08,$08,$08,$08,$08,$08,$08

.EXPORT _nVICColorfadeTable_toBrown = *
.BYTE $00,$09,$09,$09,$09,$09,$09,$09,$01,$07,$0f,$0c,$08,$02,$09,$09,$02,$09,$09,$09,$09,$09,$09,$09,$03,$0c,$08,$02,$09,$09,$09,$09,$04,$02,$09,$09,$09,$09,$09,$09,$05,$08,$02,$09,$09,$09,$09,$09,$06,$0b,$09,$09,$09,$09,$09,$09,$07,$0f,$0c,$08,$02,$09,$09,$09,$08,$02,$09,$09,$09,$09,$09,$09,$09,$09,$09,$09,$09,$09,$09,$09,$0a,$08,$02,$09,$09,$09,$09,$09,$0b,$09,$09,$09,$09,$09,$09,$09,$0c,$08,$02,$09,$09,$09,$09,$09,$0d,$03,$0c,$08,$02,$09,$09,$09,$0e,$04,$02,$09,$09,$09,$09,$09,$0f,$0c,$08,$02,$09,$09,$09,$09
.EXPORT _oVICColorfadeTable_toBrown = *
.BYTE $00,$0b,$09,$09,$09,$09,$09,$09,$01,$07,$0a,$08,$02,$09,$09,$09,$02,$09,$09,$09,$09,$09,$09,$09,$03,$05,$0c,$09,$09,$09,$09,$09,$04,$09,$09,$09,$09,$09,$09,$09,$05,$0c,$09,$09,$09,$09,$09,$09,$06,$09,$09,$09,$09,$09,$09,$09,$07,$0a,$08,$02,$09,$09,$09,$09,$08,$02,$09,$09,$09,$09,$09,$09,$09,$09,$09,$09,$09,$09,$09,$09,$0a,$08,$02,$09,$09,$09,$09,$09,$0b,$09,$09,$09,$09,$09,$09,$09,$0c,$09,$09,$09,$09,$09,$09,$09,$0d,$0f,$05,$0c,$09,$09,$09,$09,$0e,$0c,$09,$09,$09,$09,$09,$09,$0f,$05,$0c,$09,$09,$09,$09,$09

.EXPORT _nVICColorfadeTable_toLightred = *
.BYTE $00,$09,$02,$04,$0a,$0a,$0a,$0a,$01,$07,$0f,$0a,$0a,$0a,$0a,$0a,$02,$04,$0a,$0a,$0a,$0a,$0a,$0a,$03,$0c,$0a,$0a,$0a,$0a,$0a,$0a,$04,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$05,$0c,$0a,$0a,$0a,$0a,$0a,$0a,$06,$0b,$04,$0a,$0a,$0a,$0a,$0a,$07,$0f,$0a,$0a,$0a,$0a,$0a,$0a,$08,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$09,$02,$04,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$0b,$04,$0a,$0a,$0a,$0a,$0a,$0a,$0c,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$0d,$0f,$0a,$0a,$0a,$0a,$0a,$0a,$0e,$0c,$0a,$0a,$0a,$0a,$0a,$0a,$0f,$0a,$0a,$0a,$0a,$0a,$0a,$0a
.EXPORT _oVICColorfadeTable_toLightred = *
.BYTE $00,$0b,$09,$08,$0a,$0a,$0a,$0a,$01,$07,$0f,$0a,$0a,$0a,$0a,$0a,$02,$08,$0a,$0a,$0a,$0a,$0a,$0a,$03,$0f,$0a,$0a,$0a,$0a,$0a,$0a,$04,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$05,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$06,$09,$08,$0a,$0a,$0a,$0a,$0a,$07,$0f,$0a,$0a,$0a,$0a,$0a,$0a,$08,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$09,$08,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$0b,$09,$08,$0a,$0a,$0a,$0a,$0a,$0c,$08,$0a,$0a,$0a,$0a,$0a,$0a,$0d,$0f,$0a,$0a,$0a,$0a,$0a,$0a,$0e,$0a,$0a,$0a,$0a,$0a,$0a,$0a,$0f,$0a,$0a,$0a,$0a,$0a,$0a,$0a

.EXPORT _nVICColorfadeTable_toDarkgrey = *
.BYTE $00,$06,$0b,$0b,$0b,$0b,$0b,$0b,$01,$0d,$03,$0e,$04,$0b,$0b,$0b,$02,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$03,$0e,$04,$0b,$0b,$0b,$0b,$0b,$04,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$05,$08,$0b,$0b,$0b,$0b,$0b,$0b,$06,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$07,$0f,$0c,$04,$0b,$0b,$0b,$0b,$08,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$09,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$0a,$08,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$0c,$04,$0b,$0b,$0b,$0b,$0b,$0b,$0d,$03,$0e,$04,$0b,$0b,$0b,$0b,$0e,$04,$0b,$0b,$0b,$0b,$0b,$0b,$0f,$0c,$04,$0b,$0b,$0b,$0b,$0b
.EXPORT _oVICColorfadeTable_toDarkgrey = *
.BYTE $00,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$01,$0d,$05,$08,$09,$0b,$0b,$0b,$02,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$03,$05,$08,$09,$0b,$0b,$0b,$0b,$04,$09,$0b,$0b,$0b,$0b,$0b,$0b,$05,$08,$09,$0b,$0b,$0b,$0b,$0b,$06,$09,$0b,$0b,$0b,$0b,$0b,$0b,$07,$0a,$08,$09,$0b,$0b,$0b,$0b,$08,$09,$0b,$0b,$0b,$0b,$0b,$0b,$09,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$0a,$08,$09,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$0b,$0c,$09,$0b,$0b,$0b,$0b,$0b,$0b,$0d,$05,$08,$09,$0b,$0b,$0b,$0b,$0e,$06,$09,$0b,$0b,$0b,$0b,$0b,$0f,$0c,$09,$0b,$0b,$0b,$0b,$0b

.EXPORT _nVICColorfadeTable_toMediumgrey = *
.BYTE $00,$06,$0b,$04,$0c,$0c,$0c,$0c,$01,$0d,$03,$0c,$0c,$0c,$0c,$0c,$02,$08,$0c,$0c,$0c,$0c,$0c,$0c,$03,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$04,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$05,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$06,$0b,$04,$0c,$0c,$0c,$0c,$0c,$07,$0f,$0c,$0c,$0c,$0c,$0c,$0c,$08,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$09,$02,$08,$0c,$0c,$0c,$0c,$0c,$0a,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0b,$04,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0d,$03,$0c,$0c,$0c,$0c,$0c,$0c,$0e,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0f,$0c,$0c,$0c,$0c,$0c,$0c,$0c
.EXPORT _oVICColorfadeTable_toMediumgrey = *
.BYTE $00,$0b,$09,$0c,$0c,$0c,$0c,$0c,$01,$07,$0f,$04,$0c,$0c,$0c,$0c,$02,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$03,$0f,$04,$0c,$0c,$0c,$0c,$0c,$04,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$05,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$06,$09,$0c,$0c,$0c,$0c,$0c,$0c,$07,$0f,$04,$0c,$0c,$0c,$0c,$0c,$08,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$09,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0a,$08,$0c,$0c,$0c,$0c,$0c,$0c,$0b,$09,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0d,$0f,$04,$0c,$0c,$0c,$0c,$0c,$0e,$0c,$0c,$0c,$0c,$0c,$0c,$0c,$0f,$04,$0c,$0c,$0c,$0c,$0c,$0c

.EXPORT _nVICColorfadeTable_toLightgreen = *
.BYTE $00,$09,$02,$08,$0c,$0f,$0d,$0d,$01,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$02,$08,$0c,$0f,$0d,$0d,$0d,$0d,$03,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$04,$0c,$0f,$0d,$0d,$0d,$0d,$0d,$05,$03,$0d,$0d,$0d,$0d,$0d,$0d,$06,$0b,$04,$0c,$0f,$0d,$0d,$0d,$07,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$08,$0c,$0f,$0d,$0d,$0d,$0d,$0d,$09,$02,$08,$0c,$0f,$0d,$0d,$0d,$0a,$0f,$0d,$0d,$0d,$0d,$0d,$0d,$0b,$04,$0c,$0f,$0d,$0d,$0d,$0d,$0c,$0f,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$0e,$03,$0d,$0d,$0d,$0d,$0d,$0d,$0f,$0d,$0d,$0d,$0d,$0d,$0d,$0d
.EXPORT _oVICColorfadeTable_toLightgreen = *
.BYTE $00,$0b,$0c,$05,$0d,$0d,$0d,$0d,$01,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$02,$0c,$05,$0d,$0d,$0d,$0d,$0d,$03,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$04,$0f,$0d,$0d,$0d,$0d,$0d,$0d,$05,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$06,$0c,$05,$0d,$0d,$0d,$0d,$0d,$07,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$08,$05,$0d,$0d,$0d,$0d,$0d,$0d,$09,$0c,$05,$0d,$0d,$0d,$0d,$0d,$0a,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$0b,$0c,$05,$0d,$0d,$0d,$0d,$0d,$0c,$05,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$0d,$0e,$05,$0d,$0d,$0d,$0d,$0d,$0d,$0f,$0d,$0d,$0d,$0d,$0d,$0d,$0d

.EXPORT _nVICColorfadeTable_toLightblue = *
.BYTE $00,$06,$0b,$04,$0c,$0e,$0e,$0e,$01,$0d,$03,$0e,$0e,$0e,$0e,$0e,$02,$04,$0c,$0e,$0e,$0e,$0e,$0e,$03,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$04,$0c,$0e,$0e,$0e,$0e,$0e,$0e,$05,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$06,$0b,$04,$0c,$0e,$0e,$0e,$0e,$07,$0f,$0e,$0e,$0e,$0e,$0e,$0e,$08,$0c,$0e,$0e,$0e,$0e,$0e,$0e,$09,$02,$04,$0c,$0e,$0e,$0e,$0e,$0a,$0c,$0e,$0e,$0e,$0e,$0e,$0e,$0b,$04,$0c,$0e,$0e,$0e,$0e,$0e,$0c,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0d,$03,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0f,$0e,$0e,$0e,$0e,$0e,$0e,$0e
.EXPORT _oVICColorfadeTable_toLightblue = *
.BYTE $00,$0b,$04,$0e,$0e,$0e,$0e,$0e,$01,$0d,$0f,$0e,$0e,$0e,$0e,$0e,$02,$04,$0e,$0e,$0e,$0e,$0e,$0e,$03,$0f,$0e,$0e,$0e,$0e,$0e,$0e,$04,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$05,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$06,$04,$0e,$0e,$0e,$0e,$0e,$0e,$07,$0f,$0e,$0e,$0e,$0e,$0e,$0e,$08,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$09,$04,$0e,$0e,$0e,$0e,$0e,$0e,$0a,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0b,$04,$0e,$0e,$0e,$0e,$0e,$0e,$0c,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0d,$0f,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0e,$0f,$0e,$0e,$0e,$0e,$0e,$0e,$0e

.EXPORT _nVICColorfadeTable_toLightgrey = *
.BYTE $00,$06,$0b,$04,$0c,$0f,$0f,$0f,$01,$0d,$0f,$0f,$0f,$0f,$0f,$0f,$02,$08,$0c,$0f,$0f,$0f,$0f,$0f,$03,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$04,$0c,$0f,$0f,$0f,$0f,$0f,$0f,$05,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$06,$0b,$04,$0c,$0f,$0f,$0f,$0f,$07,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$08,$0c,$0f,$0f,$0f,$0f,$0f,$0f,$09,$02,$04,$0c,$0f,$0f,$0f,$0f,$0a,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0b,$04,$0c,$0f,$0f,$0f,$0f,$0f,$0c,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0d,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0e,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f
.EXPORT _oVICColorfadeTable_toLightgrey = *
.BYTE $00,$0b,$09,$08,$0a,$0f,$0f,$0f,$01,$07,$0f,$0f,$0f,$0f,$0f,$0f,$02,$04,$0a,$0f,$0f,$0f,$0f,$0f,$03,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$04,$0a,$0f,$0f,$0f,$0f,$0f,$0f,$05,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$06,$09,$08,$0a,$0f,$0f,$0f,$0f,$07,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$08,$0a,$0f,$0f,$0f,$0f,$0f,$0f,$09,$08,$0a,$0f,$0f,$0f,$0f,$0f,$0a,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0b,$09,$08,$0a,$0f,$0f,$0f,$0f,$0c,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0d,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0e,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f

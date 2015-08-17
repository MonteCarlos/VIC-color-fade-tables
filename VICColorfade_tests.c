
#include "VICColorfade_internal.h"
#include <conio.h>
//#include <cbm.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
//#include <timer/timer.h>
//#include <raster/raster.h>
//#include <CBMkey/cbmkey.h>
//#include <conio/conio+.h>
//#include <conversion/asc2hex8.h>
#include <CuTest.h>

VICColorfadeTableElement_t startColor = 13, endColor = 3, mode = VICCOLORFADE_NEWVIC, speed = 100;

void testColfadeObjAlloc(CuTest *tc){
    VICColorfade_t *colfadeObj = VICColorfadeObjAlloc();
    CuAssertPtrNotNull(tc, colfadeObj);
    CuAssertTrue(tc, CuAlloc_getBufferValidity(colfadeObj));
    CuAssertIntEquals(tc, CuAlloc_getDataSize(colfadeObj), sizeof(VICColorfade_t));
    VICColorfadeObjDelete(colfadeObj);
}

void testColfadeObjDelete(CuTest *tc){
    VICColorfade_t *colfadeObj = VICColorfadeObjAlloc();
    CuAssertTrue(tc, VICColorfadeObjDelete(colfadeObj));
    CuAssertFalse(tc, CuAlloc_getBufferValidity(colfadeObj));
}

void testColfadeSetMode(CuTest *tc){
    VICColorfade_t *vcf = VICColorfadeObjAlloc();

    CuAssertIntEquals(tc, VICCOLORFADEERR_OK, VICColorfadeSetMode(vcf, VICCOLORFADE_MODE_MIN));
    CuAssertIntEquals(tc, VICCOLORFADE_MODE_MIN, vcf->mode);
    CuAssertIntEquals(tc, VICCOLORFADEERR_OK, VICColorfadeSetMode(vcf, VICCOLORFADE_MODE_MAX) );
    CuAssertIntEquals(tc, VICCOLORFADE_MODE_MAX, vcf->mode);

    CuAssertIntEquals(tc, VICCOLORFADEERR_ILLMODE, VICColorfadeSetMode(vcf, VICCOLORFADE_MODE_MIN-1));

    CuAssertIntEquals(tc, VICCOLORFADEERR_ILLMODE, VICColorfadeSetMode(vcf, VICCOLORFADE_MODE_MAX+1));
    VICColorfadeObjDelete(vcf);
}

void testColfadeSetLimits(CuTest *tc){
    VICColorfade_t *vcf = VICColorfadeObjAlloc();
    VICColorfadeSetMode(vcf, VICCOLORFADE_NEWVIC);

    CuAssertIntEquals(tc, VICCOLORFADEERR_OK, VICColorfadeSetLimits(vcf,startColor,endColor));
    CuAssertIntEquals(tc, startColor, vcf->startcolor);
    CuAssertIntEquals(tc, endColor, vcf->endcolor);

    CuAssertIntEquals(tc, VICCOLORFADEERR_CVALUE, VICColorfadeSetLimits(vcf,16,15));
    CuAssertIntEquals(tc, VICCOLORFADEERR_CVALUE, VICColorfadeSetLimits(vcf,1,16));
    CuAssertIntEquals(tc, VICCOLORFADEERR_CVALUE, VICColorfadeSetLimits(vcf,16,16));

    VICColorfadeObjDelete(vcf);
}

void testColfadeSetSpeed(CuTest *tc){
    VICColorfade_t *vcf = VICColorfadeObjAlloc();

    CuAssertIntEquals(tc, VICCOLORFADEERR_OK, VICColorfadeSetSpeed(vcf, speed));
    CuAssertIntEquals(tc, speed, vcf->speed);
    VICColorfadeObjDelete(vcf);
}

void testColfadeIsComplete(CuTest *tc){
    VICColorfade_t *vcf = VICColorfadeObjAlloc();

    vcf->state = VICCOLORFADE_COMPLETE;
    CuAssertTrue(tc, VICColorfadeIsComplete(vcf));
    vcf->state = VICCOLORFADE_INCOMPLETE;
    CuAssertFalse(tc, VICColorfadeIsComplete(vcf));
    VICColorfadeObjDelete(vcf);
}

void testColfadeSetNewEndcolor(CuTest *tc){
    VICColorfade_t *vcf = VICColorfadeObjAlloc();
    VICColorfadeSetMode(vcf, VICCOLORFADE_NEWVIC);
    uint8_t endColor2 = (endColor+1)&15;

    VICColorfadeSetLimits(vcf,startColor,endColor);

    CuAssertIntEquals(tc, VICCOLORFADEERR_OK, VICColorfadeSetNewEndcolor(vcf,endColor2));
    CuAssertIntEquals(tc, endColor2, vcf->endcolor);
    CuAssertIntEquals(tc, endColor, vcf->startcolor);

    CuAssertIntEquals(tc, VICCOLORFADEERR_CVALUE, VICColorfadeSetNewEndcolor(vcf,16));

    VICColorfadeObjDelete(vcf);
}

void testColfadeToggleStartEndcolor(CuTest *tc){
    VICColorfade_t *vcf = VICColorfadeObjAlloc();
    VICColorfadeSetMode(vcf, VICCOLORFADE_NEWVIC);

    VICColorfadeSetLimits(vcf,startColor,endColor);

    CuAssertIntEquals(tc, VICCOLORFADEERR_OK, VICColorfadeToggleColors(vcf));
    CuAssertIntEquals(tc, startColor, vcf->endcolor);
    CuAssertIntEquals(tc, endColor, vcf->startcolor);

    VICColorfadeObjDelete(vcf);
}

void testColfadeSetReadPtr(CuTest *tc){
    VICColorfade_t *vcf = VICColorfadeObjAlloc();
    VICColorfadeSetReadPtr(vcf, (VICColorfadeTableElement_t*)0x1234);
    CuAssertIntEquals(tc, 0x1234, (uintptr_t)vcf->elementPtr);

    VICColorfadeObjDelete(vcf);
}

void testColfadeCalcReadPtr(CuTest *tc){
    VICColorfade_t *vcf = VICColorfadeObjAlloc();
    vcf->mode = VICCOLORFADE_NEWVIC;
    for (VICColorfadeTableElement_t c = 0; c < 16; ++c){
        vcf->startcolor = c;
        vcf->endcolor = 0;
        VICColorfadeCalcReadPtr(vcf);
        CuAssertIntEquals(tc, c, vcf->elementPtr[0]);
        CuAssertIntEquals(tc, 0, vcf->elementPtr[15]);
    }

    VICColorfadeObjDelete(vcf);
}

void testColfadeGetNextColor(CuTest *tc){
    VICColorfade_t *vcf = VICColorfadeNew(startColor, endColor, mode, 128);

    CuAssertIntEquals(tc, startColor, VICColorfadeGetNextColor(vcf));
    VICColorfadeSetLimits(vcf, 0,6);

    CuAssertIntEquals(tc, 0, VICColorfadeGetNextColor(vcf));
    CuAssertFalse(tc, VICColorfadeIsComplete(vcf));
    CuAssertIntEquals(tc, 6, VICColorfadeGetNextColor(vcf));
    CuAssertTrue(tc, VICColorfadeIsComplete(vcf));

    VICColorfadeObjDelete(vcf);
}

void testColfadeNew(CuTest *tc){

    VICColorfade_t *colfadeObj = VICColorfadeNew(startColor, endColor, mode, speed);
    CuAssertPtrNotNull(tc, colfadeObj);
    CuAssertTrue(tc, CuAlloc_getBufferValidity(colfadeObj));
    CuAssertIntEquals(tc, startColor, colfadeObj->startcolor);
    CuAssertIntEquals(tc, endColor, colfadeObj->endcolor);
    CuAssertIntEquals(tc, mode, colfadeObj->mode);
    CuAssertIntEquals(tc, speed, colfadeObj->speed);
    CuAssertIntEquals(tc, 0, colfadeObj->delay);
    CuAssertIntEquals(tc, 127, colfadeObj->counter);

    CuAssertIntEquals(tc, CuAlloc_getDataSize(colfadeObj), sizeof(VICColorfade_t));
    VICColorfadeObjDelete(colfadeObj);
}

CuSuite *getSuite_independentFncs(void){
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testColfadeObjAlloc);
    SUITE_ADD_TEST(suite, testColfadeObjDelete);
    SUITE_ADD_TEST(suite, testColfadeSetLimits);
    SUITE_ADD_TEST(suite, testColfadeSetMode);
    SUITE_ADD_TEST(suite, testColfadeSetNewEndcolor);
    SUITE_ADD_TEST(suite, testColfadeToggleStartEndcolor);
    SUITE_ADD_TEST(suite, testColfadeSetReadPtr);
    SUITE_ADD_TEST(suite, testColfadeSetSpeed);
    SUITE_ADD_TEST(suite, testColfadeIsComplete);

    return suite;
}

CuSuite *getSuite_singleDependentFncs(void){
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testColfadeNew);
    SUITE_ADD_TEST(suite, testColfadeGetNextColor);
    SUITE_ADD_TEST(suite, testColfadeCalcReadPtr);

    return suite;
}

typedef CuSuitePtr getSuitefnc_t(void);
size_t suiteRunner(){
    CuSuite *suite = CuSuiteNew();
    size_t testcnt;

    CuSuiteAddSuite(suite, getSuite_independentFncs());
    CuSuiteAddSuite(suite, getSuite_singleDependentFncs());
    CuSuiteRun(suite);
    CuSuiteDetails(suite, stdout);

    assert(0 == CuSuiteGetFailcount(suite));
    testcnt = CuSuiteGetTestcount(suite);
    CuSuiteDelete(suite);
    return testcnt;
}

int main(void){
    //printf("colortable size: %d\n\n", sizeof(VICColorfadeTables));
    suiteRunner();
    return 0;
}

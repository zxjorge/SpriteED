/*
 *George Benyeogor
 *CS3505
 *A2: Classes, Facades, and Makefiles
 */

#include <string.h>
#include <math.h>
#include "hpdf.h"
#ifndef HARUPDF_H
#define HARUPDF_H

class HaruPDF
{
private:
    HPDF_Doc pdf_;
    HPDF_Page page_;
    char fname_[256];
    HPDF_Font font_;

public:
    HaruPDF(char *nameOfPDF);
    void setAndShowText(float rad1, float x, float y, char *buf);
    ~HaruPDF();
};
#endif

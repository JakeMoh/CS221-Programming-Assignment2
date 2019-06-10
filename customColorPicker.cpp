#include "customColorPicker.h"

customColorPicker::customColorPicker(int x, PNG& img)
{
    space = x;
    im = img;
}

HSLAPixel customColorPicker::operator()(int x, int y)
{
    int count = 0;
    double hue = 0;
    double sat = 0;
    double lum = 0;
    double alp = 0;

    double avgHue;
    double avgSat;
    double avgLum;
    double avgAlp;

    // if there im.width % space == 0;
    for (int c = (x / space) * space; c < (((x / space)+1) * space)-1; c++)
    {
        for (int r = (y / space) * space; r < (((y / space)+1) * space)-1; r++)
        {
            if (c < (int)im.width() && r < (int)im.height())
            {
                hue += (*im.getPixel(c, r)).h;
                sat += (*im.getPixel(c, r)).s;
                lum += (*im.getPixel(c, r)).l;
                alp += (*im.getPixel(c, r)).a;

                count++;
            }
        }
    }

    avgHue = hue/count;
    avgSat = sat/count;
    avgLum = lum/count;
    avgAlp = alp/count;

    return HSLAPixel(avgHue, avgSat, avgLum, avgAlp);
}

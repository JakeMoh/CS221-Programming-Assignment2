#include "dotColorPicker.h"

dotColorPicker::dotColorPicker(HSLAPixel fillColor, int dotGrid,int dotSize)
{
    color = fillColor;
    spacing = dotGrid;
    size = dotSize;
}

HSLAPixel dotColorPicker::operator()(int x, int y)
{

    // declare variable for organization
    int eDisTL = (x % spacing)*(x % spacing) + (y % spacing)*(y % spacing);
    int eDisBL = (x % spacing)*(x % spacing) + (spacing - (y % spacing))*(spacing - (y % spacing));
    int eDisTR = (spacing - (x % spacing))*(spacing - (x % spacing)) + (y % spacing)*(y % spacing);
    int eDisBR = (spacing - (x % spacing))*(spacing - (x % spacing)) + (spacing - (y % spacing))*(spacing - (y % spacing));
    int sizeSq = size*size;

    //  if current cell is in the 4 circles
    if (eDisTL <= sizeSq || eDisBL <= sizeSq || eDisTR <= sizeSq || eDisBR <= sizeSq)
    {
        //  return the color we set to
        return color;
    }
    else
    {
        //  return white pixel
        HSLAPixel ret;
        ret.h = 0.; ret.s = 0.; ret.l = 1.;
        return ret;
    }
}
        

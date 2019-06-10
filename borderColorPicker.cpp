#include "borderColorPicker.h"

borderColorPicker::borderColorPicker(HSLAPixel fillColor, PNG & img, double tolerance,HSLAPixel center)
{
    color = fillColor;
    im = img;
    tol = tolerance;
    ctr = center;
}

HSLAPixel borderColorPicker::operator()(int x, int y)
{

    //  Note:
    //      Current cell is HSLAPixel of image at coordinate x and y 
    //      cell is same as pixel

    
    //  ---------------------------------------------
    //  << checking edges of the image >>
    //  if coordinate is near the edge of the picture

    if ((x <= 2) || (x >= (int)im.width() - 3) || (y <= 2) || (y >= (int)im.width() - 3))
    {
        //  change the color
        return color;
    }
    //  ---------------------------------------------
        

    //  ---------------------------------------------
    //  << checking boarders >>
    //  for 10 by 10 grid (stating from -3 to 3) where the current cell 
    //  is at position (0, 0) go along the for loop
        
    //  go along the columns
    for (int c = x - 3; c <= x + 3; c++)
    {
        //  go along the rows
        for (int r = y - 3; r <= y + 3; r++)
        {
                
            //  if the distance between looping cell and "center"
            //  are different by "tolerance" - CHECK HSLAPixel::dist(HSLAPixel p)
            if (ctr.dist(*im.getPixel(c, r)) > tol)
            {
                //  AND
                //  if (c - x)^2 + (r - y)^2 <= 3
                if ((c - x)*(c - x) + (r - y)*(r - y) <= 3*3)
                {
                        //  if we know current cell is near the boarder
                        //  return the color to be filled
                        return color;
                }
            }
                
        }
    }

    // if we know current cell is NOT near the boarder
    //  return the original color
    return *im.getPixel(x, y);
    //  ---------------------------------------------
}
/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. 
 *
 */
//#include "filler.h"


// animation filler::fillCustomDFS(PNG& img, int x, int y,
//                                 int space, double tolerance, int frameFreq)
// {
//     customColorPicker a(space, img);
//     return fill<Stack>(img, x, y, a, tolerance, frameFreq);
// }

// animation filler::fillCustomBFS(PNG& img, int x, int y,
//                                 int space, double tolerance, int frameFreq)
// {
//     customColorPicker a(space, img);
//     return fill<Queue>(img, x, y, a, tolerance, frameFreq);
// }

animation filler::fillDotDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int dotGrid,int dotSize, double tolerance, int frameFreq)
{
    dotColorPicker a(fillColor, dotGrid, dotSize);
    return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillBorderDFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
    borderColorPicker a(borderColor, img, tolerance, *img.getPixel(x, y));
    return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillRainDFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{

/* example, implemented for you! */
    rainbowColorPicker a(freq);
    return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillDotBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int dotGrid,int dotSize, double tolerance, int frameFreq)
{
    dotColorPicker a(fillColor, dotGrid, dotSize);
    return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillBorderBFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
    borderColorPicker a(borderColor, img, tolerance, *img.getPixel(x, y));
    return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillRainBFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
/* example, completed for you! */
    rainbowColorPicker a(freq);
    return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}


template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       double tolerance, int frameFreq)
{    
    animation ani;
    int frame = 0;

    //  processed 2D-vectors
    vector<vector<bool>> processed;
    processed.resize(img.width());
    for (unsigned int i = 0 ; i < img.width() ; i++) {
      processed[i].resize(img.height());
      for (unsigned int j = 0 ; j< img.height() ; j++) {
        processed[i][j] = false;
      }
    }
    
    //  add changed cell with coordinate and color to the os
    OrderingStructure<pair<int, int>> os;
    pair<int, int> startCoordinate (x, y);
    HSLAPixel startPixel = *img.getPixel(x, y);
    *img.getPixel(x, y) = fillColor(x, y);
    frame++;
    os.add(startCoordinate);
    //  mark as processed
    processed[x][y] = true;

    //  while structure is not empty
    while (!os.isEmpty())
    {    
        //  remove a cell from os
        pair<int, int> removedCoordinate = os.remove();
        int currX = removedCoordinate.first;
        int currY = removedCoordinate.second;

        //  if above neighbor is not on edges of the picture, unprocessed, and within tolerance
        if (currY > 0 && !processed[currX][currY-1] && startPixel.dist(*img.getPixel(currX, currY-1)) <= tolerance)
        {
            //  mark as processed
            processed[currX][currY-1] = true;
            //  change color of the neighbor cell
            //  insert in os
            pair<int, int> aboveCoordinate (currX, currY-1);
            os.add(aboveCoordinate);
            *img.getPixel(currX, currY-1) = fillColor(currX, currY-1);
            frame++;
            //  if frameFreq is appropriate
            if (frame % frameFreq == 0)
            {
                //  update PNG to animation
                ani.addFrame(img);
            }
        }

        //  if left neighbor is not on edges of the picture, unprocessed, and within tolerance
        if (currX > 0 && !processed[currX-1][currY] && startPixel.dist(*img.getPixel(currX-1, currY)) <= tolerance)
        {
            //  mark as processed
            processed[currX-1][currY] = true;
            //  change color of the neighbor cell
            //  insert in os
            pair<int, int> leftCoordinate (currX-1, currY);
            os.add(leftCoordinate);
            *img.getPixel(currX-1, currY) = fillColor(currX-1, currY);
            frame++;
            //  if frameFreq is appropriate
            if (frame % frameFreq == 0)
            {
                //  update PNG to animation
                ani.addFrame(img);
            }
        }

        //  if down neighbor is not on edges of the picture, unprocessed, and within tolerance
        if (currY+1 < (int)img.height() && !processed[currX][currY+1] && startPixel.dist(*img.getPixel(currX, currY+1)) <= tolerance)
        {
            //  mark as processed
            processed[currX][currY+1] = true;
            //  change color of the neighbor cell
            //  insert in os
            pair<int, int> downCoordinate (currX, currY+1);
            os.add(downCoordinate);
            *img.getPixel(currX, currY+1) = fillColor(currX, currY+1);
            frame++;
            //  if frameFreq is appropriate
            if (frame % frameFreq == 0)
            {
                //  update PNG to animation
                ani.addFrame(img);
            }
        }

         //  if right neighbor is not on edges of the picture, unprocessed, and within tolerance
        if (currX+1 < (int)img.width() && !processed[currX+1][currY] && startPixel.dist(*img.getPixel(currX+1, currY)) <= tolerance)
        {
            //  mark as processed
            processed[currX+1][currY] = true;
            //  change color of the neighbor cell
            //  insert in os
            pair<int, int> rightCoordinate (currX+1, currY);
            os.add(rightCoordinate);
            *img.getPixel(currX+1, currY) = fillColor(currX+1, currY);
            frame++;
            //  if frameFreq is appropriate
            if (frame % frameFreq == 0)
            {
                //  update PNG to animation
                ani.addFrame(img);
            }
        }
    }

    ani.addFrame(img);
    return ani;
}
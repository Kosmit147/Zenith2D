#include "Helpers.h"

bool Helpers::wheterIntersect(Line firstLine, Line secondLine)
{
    int s1 = firstLine.from.x * secondLine.from.y + secondLine.from.x * secondLine.to.y
             + firstLine.from.y * secondLine.to.x - secondLine.from.y * secondLine.to.x
             - secondLine.to.y * firstLine.from.x - firstLine.from.y * secondLine.from.x;

    int s2 = firstLine.to.x * secondLine.from.y + secondLine.from.x * secondLine.to.y
             + firstLine.to.y * secondLine.to.x - secondLine.from.y * secondLine.to.x
             - secondLine.to.y * firstLine.to.x - firstLine.to.y * secondLine.from.x;
    int s3 = secondLine.from.x * firstLine.from.y + firstLine.from.x * firstLine.to.y
             + secondLine.from.y * firstLine.to.x - firstLine.from.y * firstLine.to.x
             - firstLine.to.y * secondLine.from.x - secondLine.from.y * firstLine.from.x;

    int s4 = secondLine.to.x * firstLine.from.y + firstLine.from.x * firstLine.to.y
             + secondLine.to.y * firstLine.to.x - firstLine.from.y * firstLine.to.x
             - firstLine.to.y * secondLine.to.x - secondLine.to.y * firstLine.from.x;

    if (s1 < 0 && s2 > 0 && s3 > 0 && s4 < 0 || s1 > 0 && s2 < 0 && s3 < 0 && s4 > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

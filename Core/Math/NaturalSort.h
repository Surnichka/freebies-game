#pragma once

namespace core
{

int NaturalCompare(const char *a, const char *b)
{
    if (!a || !b)   // if one doesn't exist, it comes first
        return a ? 1 : b ? -1 : 0;

    if (isdigit(*a) && isdigit(*b))     // both start with numbers
    {
        char *remainderA;
        char *remainderB;
        long valA = strtol(a, &remainderA, 10);
        long valB = strtol(b, &remainderB, 10);
        if (valA != valB)
        {
            return valA - valB;         // smaller comes first
        }
        else
        {
            std::ptrdiff_t lengthA = remainderA - a;
            std::ptrdiff_t lengthB = remainderB - b;
            if (lengthA != lengthB)
                return lengthA - lengthB;   // shorter comes first
            else                            // all being equal, recurse
                return strcmp_natural(remainderA, remainderB);
        }
    }

    if (isdigit(*a) || isdigit(*b))     // if just one is a number
        return isdigit(*a) ? -1 : 1;    // numbers always come first

    while (*a && *b)    // non-numeric characters
    {
        if (isdigit(*a) || isdigit(*b))
            return strcmp_natural(a, b);    // recurse
        if (*a != *b)
            return *a - *b;
        a++;
        b++;
    }
    return *a ? 1 : *b ? -1 : 0;
}

} //end of core

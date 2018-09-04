#pragma once
#include <cctype>
#include <cstdlib>
#include <string>
#include <string.h>

namespace math
{

struct NaturalCompare
{
    bool operator()(const std::string& lhs, const std::string& rhs) const
    {
        const char* p1 = lhs.c_str();
        const char* p2 = rhs.c_str();
        const unsigned short st_scan = 0;
        const unsigned short st_alpha = 1;
        const unsigned short st_numeric = 2;
        unsigned short state = st_scan;
        const char* numstart1 = nullptr;
        const char* numstart2 = nullptr;
        const char* numend1 = nullptr;
        const char* numend2 = nullptr;
        unsigned long sz1 = 0;
        unsigned long sz2 = 0;
        while ( *p1 && *p2  ) {
        switch ( state ) {
          case st_scan:
            if ( !isdigit(*p1) && !isdigit(*p2) ) {
              state = st_alpha;
              if ( *p1 == *p2 ) {
                p1++;p2++;
              } else return *p1 < *p2;
            } else
            if ( isdigit(*p1) && !isdigit(*p2) ) return true;
            else if ( !isdigit(*p1) && isdigit(*p2) ) return false;
            else {
              state = st_numeric;
              if ( sz1 == 0 )
                while ( *p1 == '0' ) {p1++; sz1++;}
              else
                while ( *p1 == '0' ) p1++;
              if ( sz2 == 0 )
                while ( *p2 == '0' ) {p2++; sz2++;}
              else
                while ( *p2 == '0' ) p2++;
              if ( sz1 == sz2 ) { sz1 = 0; sz2 = 0; };
              if ( !isdigit(*p1) ) p1--;
              if ( !isdigit(*p2) ) p2--;
              numstart1 = p1;
              numstart2 = p2;
              numend1 = numstart1;
              numend2 = numstart2;
            }
            break;
          case st_alpha:
            if ( !isdigit(*p1) && !isdigit(*p2) ) {
              if ( *p1 == *p2 ) {
                p1++;p2++;
              } else return *p1 < *p2;
            } else state = st_scan;
            break;
          case st_numeric:
            while ( isdigit(*p1) ) numend1 = p1++;
            while ( isdigit(*p2) ) numend2 = p2++;
            if ( numend1-numstart1 == numend2-numstart2 &&
                !strncmp( numstart1,numstart2,size_t(numend2-numstart2+1)) ) state = st_scan; else {
              if ( numend1-numstart1 != numend2-numstart2 )
                return numend1-numstart1 < numend2-numstart2;
              while ( *numstart1 && *numstart2 ) {
                if ( *numstart1 != *numstart2 ) return *numstart1 < *numstart2;
                numstart1++;
                numstart2++;
              }
            }
            break;
        }
        }
        if ( sz1 < sz2 ) return true;
        if ( sz1 > sz2 ) return false;
        if ( *p1 == 0 && *p2 != 0 ) return true;
        if ( *p1 != 0 && *p2 == 0 ) return false;
        return false;
    }
};


} //end of math

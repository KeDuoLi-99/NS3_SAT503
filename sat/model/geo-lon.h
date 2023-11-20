#ifndef GEO_LON_H
#define GEO_LON_H

#include <iostream>

namespace ns3
{
    class GeoLon
    {
        public:
        GeoLon();
        GeoLon(double longitude);
        virtual ~GeoLon();
        double longitude;
    };

    std::ostream &operator << (std::ostream &os, const GeoLon &lon);
    std::istream &operator >> (std::istream &is, GeoLon &lon);
};

#endif
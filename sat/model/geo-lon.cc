#include "geo-lon.h"

namespace ns3
{
    std::ostream &operator << (std::ostream &os, const GeoLon &lon)
    {
        os << lon.longitude;
        return os;
    }

    std::istream &operator >> (std::istream &is, GeoLon &lon)
    {
        is >> lon.longitude;
        return is;
    }
    
    GeoLon::GeoLon() : longitude(0){}
    GeoLon::GeoLon(double lo) : longitude(lo){}
    GeoLon::~GeoLon() {}
}; // namespace ns3

#ifndef GEO_NODE_HELPER_H
#define GEO_NODE_HELPER_H

#include <string>
#include "ns3/object-factory.h"
#include "ns3/node-container.h"
#include "ns3/constant-position-mobility-model.h"
#include "ns3/geo-lon.h"

#define GEO_NODE_RAD_ORBIT 4.2164e7  //h=3.5786e7

namespace ns3
{
    class GeoNodeHelper
    {
    private:
        /* data */
        ObjectFactory m_geoNodeFactory;
        //获取卫星的位置
        static Vector3D GetGeoPosition(const double lon);
    public:
        GeoNodeHelper();
        ~GeoNodeHelper();
        //从文件读取卫星坐标
        NodeContainer Install(const std::string &file);
        //直接输入经度
        NodeContainer Install(const GeoLon &lon);
        //输入GEO个数，等间隔分布从0度开始
        NodeContainer Install(uint32_t num);
        void SetAttribute(std::string name, const AttributeValue &value);
    };
    
}; // namespace ns3

#endif

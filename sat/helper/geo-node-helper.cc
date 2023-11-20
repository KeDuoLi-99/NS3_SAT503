#include <fstream>
#include "math.h"
#include "ns3/log.h"
#include "ns3/waypoint.h"
#include "ns3/double.h"
#include "ns3/uinteger.h"
#include "ns3/mobility-helper.h"
#include "geo-node-helper.h"

using namespace std;

namespace ns3
{
    NS_LOG_COMPONENT_DEFINE("GeoNodeHelper");

    GeoNodeHelper::GeoNodeHelper()
    {
        m_geoNodeFactory.SetTypeId ("ns3::Node");
    }

    GeoNodeHelper::~GeoNodeHelper()
    {

    }

    void
    GeoNodeHelper::SetAttribute(string name, const AttributeValue &value)
    {
        m_geoNodeFactory.Set(name, value);
    }
    
    NodeContainer
    GeoNodeHelper::Install(const std::string &file)
    {
        NS_LOG_FUNCTION(this << file);

        NodeContainer nodes;
        ifstream stream;
        stream.open(file, ifstream::in);
        GeoLon lon;
        while((stream >> lon))
        {
            Ptr<ConstantPositionMobilityModel> mob = CreateObject<ConstantPositionMobilityModel>();
            Vector3D pos = GetGeoPosition(lon.longitude);
            mob->SetPosition(pos);
            Ptr<Node> node = m_geoNodeFactory.Create<Node>();
            node->AggregateObject(mob);
            nodes.Add(node);
            NS_LOG_INFO("Added geo node at" << pos);
        }
        stream.close();
        NS_LOG_INFO("Added " << nodes.GetN() << " geo nodes");
        return nodes;
    }

    NodeContainer
    GeoNodeHelper::Install(uint32_t num)
    {
        NodeContainer nodes;
        double lon;
        for(uint32_t i = 0; i < num; i++)
        {
            lon = 360 * i / num;
            Ptr<ConstantPositionMobilityModel> mob = CreateObject<ConstantPositionMobilityModel>();
            Vector3D pos = GetGeoPosition(lon);
            mob->SetPosition(pos);
            Ptr<Node> node = m_geoNodeFactory.Create<Node>();
            node->AggregateObject(mob);
            nodes.Add(node);
            NS_LOG_INFO("Added geo node at" << pos);
        }
        NS_LOG_INFO("Added " << nodes.GetN() << " geo nodes");
        return nodes;
    }

    NodeContainer
    GeoNodeHelper::Install(const GeoLon &lon)
    {
        NodeContainer nodes;
        Vector3D pos = GetGeoPosition(lon.longitude);
        Ptr<ConstantPositionMobilityModel> mob = CreateObject<ConstantPositionMobilityModel>();
        mob->SetPosition(pos);
        Ptr<Node> node = m_geoNodeFactory.Create<Node>();
        node->AggregateObject(mob);
        nodes.Add(node);
        return nodes;
    }

    Vector3D
    GeoNodeHelper::GetGeoPosition(const double lon)
    {
        double lon_r = lon * (M_PI / 180);
        Vector3D pos = Vector3D(GEO_NODE_RAD_ORBIT * cos(lon_r),
                                GEO_NODE_RAD_ORBIT * sin(lon_r), 0);
        return pos;
    }
};
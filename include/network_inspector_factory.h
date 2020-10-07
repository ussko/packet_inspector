#include <memory>

#include "network_inspector_v1.h"
#include "network_inspector_v2.h"

class NetworkInspectorFactory
{
public:
    std::unique_ptr<INetworkInspector> make_network_inspector(network_version version)
    {
        switch (version)
        {
        case NETWORK_V1:
            return std::make_unique<NetworkInspectorV1>();
        case NETWORK_V2:
            return std::make_unique<NetworkInspectorV2>();
        default:
            return nullptr;
        }
    }
};

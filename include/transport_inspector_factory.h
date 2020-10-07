#pragma once

#include <memory>

#include "transport_inspector_v1.h"
#include "transport_inspector_v2.h"

class TransportInspectorFactory
{
public:
    std::unique_ptr<ITransportInspector> make_transport_inspector(transport_version version)
    {
        switch (version)
        {
        case TRANSPORT_V1:
            return std::make_unique<TransportInspectorV1>();
        case TRANSPORT_V2:
            return std::make_unique<TransportInspectorV2>();
        default:
            return nullptr;
        }
    }
};

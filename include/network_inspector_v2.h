#pragma once

#include <unordered_set>

#include "network_inspector.h"

class NetworkInspectorV2: public NetworkInspector
{
public:
    NetworkInspectorV2();

protected:
    std::pair<transport_version, uint16_t> _process_header(network_t &header) override;
    void _update_stats(stats_t &stats) override;

private:
    unsigned _packets{0};
    std::unordered_set<uint64_t> _addresses;
};

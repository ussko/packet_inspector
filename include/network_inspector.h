#pragma once

#include <fstream>
#include <unordered_set>

#include "protocols.h"
#include "stats.h"

class NetworkInspector
{
public:
    NetworkInspector(network_version version);

    bool read_packet(std::istream &input);
    void update_stats(stats_t &stats);

private:
    network_version _version;
    unsigned _packets_v1{0};
    unsigned _packets_v2{0};
    std::unordered_set<uint32_t> _addresses_v1;
    std::unordered_set<uint64_t> _addresses_v2;

    uint16_t _check_sum(uint8_t *data, size_t size);
};

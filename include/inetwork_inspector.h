#pragma once

#include <fstream>

#include "stats.h"

class INetworkInspector
{
public:
    ~INetworkInspector() = default;

    virtual bool read_packet(std::istream &input) = 0;
    virtual void update_stats(stats_t &stats) = 0;
};

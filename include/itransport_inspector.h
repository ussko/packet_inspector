#pragma once

#include <array>
#include <cstddef>

#include "protocols.h"
#include "stats.h"

class ITransportInspector
{
public:
    virtual ~ITransportInspector() = default;

    using buf_iterator = std::array<uint8_t, MAX_DATA_SIZE>::iterator;

    virtual bool process_packet(buf_iterator begin, buf_iterator end) = 0;
    virtual void update_stats(stats_t &stats) = 0;
};

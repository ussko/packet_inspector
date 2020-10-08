#pragma once

#include <array>
#include <cstddef>

#include "buffer.h"
#include "protocols.h"
#include "stats.h"

class ITransportInspector
{
public:
    virtual ~ITransportInspector() = default;

    virtual bool process_packet(buf_iterator begin, buf_iterator end) = 0;
    virtual void update_stats(stats_t &stats) = 0;
};

#pragma once

#include "transport_inspector.h"

class TransportInspectorV1: public TransportInspector
{
public:
    TransportInspectorV1();

    void update_stats(stats_t &stats) override;

protected:
    bool _process_header(buf_iterator header_begin) override;
};

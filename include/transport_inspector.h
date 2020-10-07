#pragma once

#include <unordered_set>

#include "itransport_inspector.h"

class TransportInspector: public ITransportInspector
{
public:
    bool process_packet(buf_iterator begin, buf_iterator end) override;

protected:
    std::unordered_set<uint16_t> _ports;
    unsigned _packets{0};
    unsigned _errors{0};
    size_t _header_size{0};

    virtual bool _process_header(buf_iterator header_begin) = 0;
    uint16_t _check_sum(buf_iterator begin, buf_iterator end);
};

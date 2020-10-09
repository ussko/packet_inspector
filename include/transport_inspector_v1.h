#pragma once

#include "application_inspector.h"
#include "transport_inspector.h"

class TransportInspectorV1: public TransportInspector
{
public:
    TransportInspectorV1();

    void update_stats(stats_t &stats) override;

protected:
    uint16_t _process_header(buf_iterator header_begin) override;
    void _process_payload(buf_iterator data_begin, buf_iterator data_end) override;

private:
    ApplicationInspector _app;
    unsigned _num_binary{0};
    unsigned _num_json{0};
    unsigned _num_text{0};
};

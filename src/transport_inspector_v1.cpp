#include <netinet/in.h>

#include "transport_inspector_v1.h"

TransportInspectorV1::TransportInspectorV1()
{
    _header_size = sizeof(transport_v1_t);
}

void TransportInspectorV1::update_stats(stats_t &stats)
{
    stats.transport_v1_packets += _packets;
    stats.transport_v1_errors += _errors;
}

uint16_t TransportInspectorV1::_process_header(buf_iterator header_begin)
{
    const auto &header = *(reinterpret_cast<transport_v1_t*>(&(*header_begin)));
    uint16_t app_size = ntohs(header.data_size);
    return app_size;
}

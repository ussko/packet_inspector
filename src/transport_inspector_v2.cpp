#include <netinet/in.h>

#include "transport_inspector_v2.h"

TransportInspectorV2::TransportInspectorV2()
{
    _header_size = sizeof(transport_v2_t);
}

void TransportInspectorV2::update_stats(stats_t &stats)
{
    stats.transport_v2_packets += _packets;
    stats.transport_v2_errors += _errors;
}

uint16_t TransportInspectorV2::_process_header(buf_iterator header_begin)
{
    const auto &header = *(reinterpret_cast<transport_v2_t*>(&(*header_begin)));
    uint16_t app_size = ntohs(header.data_size);
    return app_size;
}

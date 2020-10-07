#include <netinet/in.h>

#include "transport_inspector_v2.h"

TransportInspectorV2::TransportInspectorV2()
{
    _header_size = sizeof(transport_v2_t);
}

void TransportInspectorV2::update_stats(stats_t &stats)
{
    stats.transport_v2_packets += _packets;
    stats.transport_v2_ports += _ports.size();
    stats.transport_v2_errors += _errors;
}

bool TransportInspectorV2::_process_header(buf_iterator header_begin)
{
    const auto &header = *(reinterpret_cast<transport_v2_t*>(&(*header_begin)));
    uint16_t port_src = ntohs(header.port_src);
    uint16_t port_dst = ntohs(header.port_dst);
    _ports.insert(port_src);
    _ports.insert(port_dst);

    return true;
}

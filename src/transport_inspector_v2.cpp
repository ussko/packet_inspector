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

    _session_mgr.update_stats(stats);
}

void TransportInspectorV2::set_current_addr(uint64_t addr_src, uint64_t addr_dst)
{
    _src_current.addr = addr_src;
    _dst_current.addr = addr_dst;
}

bool TransportInspectorV2::_process_header(buf_iterator header_begin)
{
    const auto &header = *(reinterpret_cast<transport_v2_t*>(&(*header_begin)));
    uint16_t port_src = ntohs(header.port_src);
    uint16_t port_dst = ntohs(header.port_dst);
    _ports.insert(port_src);
    _ports.insert(port_dst);

    _src_current.port = port_src;
    _dst_current.port = port_dst;
    _fragment_num_current = ntohl(header.fragment_number);
    _session_mgr.add_fragment(_src_current, _dst_current, _fragment_num_current, header.flags);

    return true;
}

void TransportInspectorV2::_process_payload(buf_iterator data_begin, buf_iterator data_end)
{
    _session_mgr.add_fragment_data(_src_current, _dst_current, _fragment_num_current,
                                   data_begin, data_end);
}

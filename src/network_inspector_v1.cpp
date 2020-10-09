#include <netinet/in.h>

#include "network_inspector_v1.h"

NetworkInspectorV1::NetworkInspectorV1()
{
    _header_size = sizeof(network_v1_t);
}

std::pair<transport_version, uint16_t> NetworkInspectorV1::_process_header(network_t &header)
{
    uint32_t addr_src = ntohl(header.v1.addr_src);
    uint32_t addr_dst = ntohl(header.v1.addr_dst);
    uint8_t protocol = header.v1.protocol;
    uint16_t data_size = ntohs(header.v1.data_size);
    uint16_t check_sum = ntohs(header.v1.check_sum);

    buf_iterator begin = reinterpret_cast<uint8_t*>(&header);
    buf_iterator end = begin + _header_size - sizeof(check_sum);

    if (check_sum != _check_sum(begin, end))
        throw std::runtime_error("Network v.1 bad checksum");

    _packets++;
    _addresses.insert(addr_src);
    _addresses.insert(addr_dst);

    if (protocol == TRANSPORT_V2)
    {
        if (auto tv2 = dynamic_cast<TransportInspectorV2*>(_transport_v2.get()); tv2 != nullptr)
            tv2->set_current_addr(static_cast<uint64_t>(addr_src), static_cast<uint64_t>(addr_dst));
    }
    return std::make_pair(static_cast<transport_version>(protocol), data_size);
}

void NetworkInspectorV1::_update_stats(stats_t &stats)
{
    stats.network_v1_packets += _packets;
    stats.network_v1_addresses += _addresses.size();
}

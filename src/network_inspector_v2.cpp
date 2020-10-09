#include <netinet/in.h>

#include "network_inspector_v2.h"
#include "swap6.h"

NetworkInspectorV2::NetworkInspectorV2()
{
    _header_size = sizeof(network_v2_t);
}

std::pair<transport_version, uint16_t> NetworkInspectorV2::_process_header(network_t &header)
{
    uint64_t addr_src = 0;
    uint64_t addr_dst = 0;
    ntoh6(header.v2.addr_src, addr_src);
    ntoh6(header.v2.addr_dst, addr_dst);
    uint8_t protocol = header.v2.protocol;
    uint16_t data_size = ntohs(header.v2.data_size);
    uint16_t check_sum = ntohs(header.v2.check_sum);

    buf_iterator begin = reinterpret_cast<uint8_t*>(&header);
    buf_iterator end = begin + _header_size - sizeof(check_sum);

    if (check_sum != _check_sum(begin, end))
        throw std::runtime_error("Network v.2 bad checksum");

    _packets++;
    _addresses.insert(addr_src);
    _addresses.insert(addr_dst);

    if (protocol == TRANSPORT_V2)
    {
        if (auto tv2 = dynamic_cast<TransportInspectorV2*>(_transport_v2.get()); tv2 != nullptr)
            tv2->set_current_addr(addr_src, addr_dst);
    }

    return std::make_pair(static_cast<transport_version>(protocol), data_size);
}

void NetworkInspectorV2::_update_stats(stats_t &stats)
{
    stats.network_v2_packets += _packets;
    stats.network_v2_addresses += _addresses.size();
}

#include <array>

#include <netinet/in.h>

#include "network_inspector.h"
#include "swap6.h"

NetworkInspector::NetworkInspector(network_version version)
:   _version{version}
{

}

bool NetworkInspector::read_packet(std::istream &input)
{
    network_t header;
    std::array<uint8_t, MAX_DATA_SIZE> data;
    size_t header_size = 0;

    if (_version == NETWORK_V1)
        header_size = sizeof(network_v1_t);
    else if (_version == NETWORK_V2)
        header_size = sizeof(network_v2_t);

    input.read(reinterpret_cast<char*>(&header), header_size);
    if (header.v2.version != _version)
        return false;

    uint32_t addr_src_v1 = 0;
    uint32_t addr_dst_v1 = 0;
    uint64_t addr_src_v2 = 0;
    uint64_t addr_dst_v2 = 0;
    uint8_t protocol = 0;
    uint16_t data_size = 0;
    uint16_t check_sum = 0;

    if (_version == NETWORK_V1)
    {
        addr_src_v1 = ntohl(header.v1.addr_src);
        addr_dst_v1 = ntohl(header.v1.addr_dst);
        protocol = header.v1.protocol;
        data_size = ntohs(header.v1.data_size);
        check_sum = ntohs(header.v1.check_sum);

        if (check_sum != _check_sum(reinterpret_cast<uint8_t*>(&header),
            header_size - sizeof(check_sum)))
            return false;

        _packets_v1++;
        _addresses_v1.insert(addr_src_v1);
        _addresses_v1.insert(addr_dst_v1);
    }
    else if (_version == NETWORK_V2)
    {
        ntoh6(header.v2.addr_src, addr_src_v2);
        ntoh6(header.v2.addr_dst, addr_dst_v2);
        protocol = header.v2.protocol;
        data_size = ntohs(header.v2.data_size);
        check_sum = ntohs(header.v2.check_sum);

        if (check_sum != _check_sum(reinterpret_cast<uint8_t*>(&header),
                                    header_size - sizeof(check_sum)))
            return false;

        _packets_v2++;
        _addresses_v2.insert(addr_src_v2);
        _addresses_v2.insert(addr_dst_v2);
    }

    input.read(reinterpret_cast<char*>(data.data()), data_size);

    return true;
}

void NetworkInspector::update_stats(stats_t &stats)
{
    stats.network_v1_packets += _packets_v1;
    stats.network_v2_packets += _packets_v2;
    stats.network_v1_addresses += _addresses_v1.size();
    stats.network_v2_addresses += _addresses_v2.size();
}

uint16_t NetworkInspector::_check_sum(uint8_t *data, size_t size)
{
    uint16_t result = 0;

    for (size_t i = 0; i < size; ++i)
        result += data[i];

    return result;
}

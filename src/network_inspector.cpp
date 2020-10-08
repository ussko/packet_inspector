#include <iostream>

#include "network_inspector.h"
#include "transport_inspector_factory.h"

NetworkInspector::NetworkInspector()
{
    TransportInspectorFactory transport;

    _transport_v1 = transport.make_transport_inspector(TRANSPORT_V1);
    _transport_v2 = transport.make_transport_inspector(TRANSPORT_V2);
}

bool NetworkInspector::read_packet(std::istream &input)
{
    network_t header;
    buf_t data;

    input.read(reinterpret_cast<char*>(&header), _header_size);
    try
    {
        const auto [protocol, data_size] = _process_header(header);
        input.read(reinterpret_cast<char*>(data.data()), data_size);

        auto data_begin = data.begin();
        auto data_end = data_begin;
        std::advance(data_end, data_size);

        switch (protocol)
        {
        case TRANSPORT_V1:
            _transport_v1->process_packet(data_begin, data_end);
            break;
        case TRANSPORT_V2:
            _transport_v2->process_packet(data_begin, data_end);
            break;
        default:
            return false;
        }
    }
    catch (std::runtime_error &e)
    {
        std::cerr << e.what() << "\n";
        return false;
    }
    return true;
}

void NetworkInspector::update_stats(stats_t &stats)
{
    _update_stats(stats);

    _transport_v1->update_stats(stats);
    _transport_v2->update_stats(stats);
}

uint16_t NetworkInspector::_check_sum(buf_iterator begin, buf_iterator end)
{
    uint16_t result = 0;

    while (begin != end)
        result += *(begin++);

    return result;
}

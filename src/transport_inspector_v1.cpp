#include <netinet/in.h>

#include "transport_inspector_v1.h"

TransportInspectorV1::TransportInspectorV1()
{
    _header_size = sizeof(transport_v1_t);
}

void TransportInspectorV1::update_stats(stats_t &stats)
{
    stats.transport_v1_packets += _packets;
    stats.transport_v1_ports += _ports.size();
    stats.transport_v1_errors += _errors;

    stats.binary_packets += _num_binary;
    stats.json_packets += _num_json;
    stats.text_packets += _num_text;
}

uint16_t TransportInspectorV1::_process_header(buf_iterator header_begin)
{
    const auto &header = *(reinterpret_cast<transport_v1_t*>(&(*header_begin)));
    uint16_t port_src = ntohs(header.port_src);
    uint16_t port_dst = ntohs(header.port_dst);
    _ports.insert(port_src);
    _ports.insert(port_dst);

    return ntohs(header.data_size);
}

void TransportInspectorV1::_process_payload(buf_iterator data_begin, buf_iterator data_end)
{
    switch (auto data_class = _app.process_data(data_begin, data_end); data_class)
    {
    case ApplicationInspector::APP_BINARY:
        _num_binary++;
        break;
    case ApplicationInspector::APP_JSON:
        _num_json++;
        break;
    case ApplicationInspector::APP_TEXT:
        _num_text++;
        break;
    default:
        break;
    }
}

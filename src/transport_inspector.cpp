#include <netinet/in.h>

#include "protocols.h"
#include "transport_inspector.h"

bool TransportInspector::process_packet(buf_iterator begin, buf_iterator end)
{
    _packets++;
    if (!_process_header(begin))
        return false;

    auto check_sum_offset = end;
    std::advance(check_sum_offset, -sizeof(transport_t::v1.data_size));
    const uint16_t check_sum = ntohs(*reinterpret_cast<uint16_t*>(&(*check_sum_offset)));
    if (check_sum != _check_sum(begin, check_sum_offset))
    {
        _errors++;
        return false;
    }

    auto data_begin = begin;
    auto data_end = check_sum_offset;
    std::advance(data_begin, _header_size);
    _process_payload(data_begin, data_end);

    return true;
}

uint16_t TransportInspector::_check_sum(buf_iterator begin, buf_iterator end)
{
    uint16_t result = 0;

    while (begin != end)
        result += *(begin++);

    return result;
}

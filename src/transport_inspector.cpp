#include <netinet/in.h>

#include "protocols.h"
#include "transport_inspector.h"

bool TransportInspector::process_packet(buf_iterator begin, buf_iterator end)
{
    _packets++;
    const auto app_size = _process_header(begin);

    auto check_sum_offset = end;
    std::advance(check_sum_offset, _header_size + app_size);
    const uint16_t check_sum = ntohs(*reinterpret_cast<uint16_t*>(&(*check_sum_offset)));
    if (check_sum != _check_sum(begin, check_sum_offset))
    {
        _errors++;
        return false;
    }
    return true;
}

uint16_t TransportInspector::_check_sum(buf_iterator begin, buf_iterator end)
{
    uint16_t result = 0;

    while (begin != end)
        result += *(begin++);

    return result;
}

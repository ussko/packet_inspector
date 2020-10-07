#include <netinet/in.h>

#include "protocols.h"
#include "transport_inspector.h"

bool TransportInspector::process_packet(buf_iterator begin, buf_iterator end)
{
    _packets++;
    const auto app_size = _process_header(begin);
//    const auto check_sum_offset = _header_size + app_size;
//    const uint16_t check_sum = ntohs(data.data()[check_sum_offset]);
//    if (check_sum != _check_sum(data.data(), size))
//    {
//        _errors++;
//        throw std::runtime_error("Bad transport checksum");
////        return false;
//    }
    return true;
}

uint16_t TransportInspector::_check_sum(const uint8_t *data, size_t size)
{
    uint16_t result = 0;

    for (size_t i = 0; i < size; ++i)
        result += data[i];

    return result;
}

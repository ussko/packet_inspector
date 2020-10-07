#include <array>
#include <iostream>

#include "network_inspector.h"

bool NetworkInspector::read_packet(std::istream &input)
{
    network_t header;
    std::array<uint8_t, MAX_DATA_SIZE> data;

    input.read(reinterpret_cast<char*>(&header), _header_size);
    try
    {
        const auto [protocol, data_size] = _process_header(header);
        input.read(reinterpret_cast<char*>(data.data()), data_size);
    }
    catch (std::runtime_error &e)
    {
        std::cerr << e.what() << "\n";
        return false;
    }
    return true;
}

uint16_t NetworkInspector::_check_sum(const uint8_t *data, size_t size)
{
    uint16_t result = 0;

    for (size_t i = 0; i < size; ++i)
        result += data[i];

    return result;
}

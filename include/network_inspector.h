#pragma once

#include <unordered_set>

#include "inetwork_inspector.h"
#include "protocols.h"

class NetworkInspector: public INetworkInspector
{
public:
    bool read_packet(std::istream &input) override;

protected:
    size_t _header_size{0};

    virtual std::pair<transport_version, uint16_t> _process_header(network_t &header) = 0;
    uint16_t _check_sum(const uint8_t *data, size_t size);
};

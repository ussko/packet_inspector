#pragma once

#include <unordered_set>

#include "inetwork_inspector.h"
#include "protocols.h"
#include "transport_inspector_factory.h"

class NetworkInspector: public INetworkInspector
{
public:
    NetworkInspector();

    bool read_packet(std::istream &input) override;
    void update_stats(stats_t &stats) override;

protected:
    size_t _header_size{0};
    std::unique_ptr<ITransportInspector> _transport_v1;
    std::unique_ptr<ITransportInspector> _transport_v2;

    virtual std::pair<transport_version, uint16_t> _process_header(network_t &header) = 0;
    virtual void _update_stats(stats_t &stats) = 0;
    uint16_t _check_sum(const uint8_t *data, size_t size);
};

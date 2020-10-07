#pragma once

struct stats_t
{
    unsigned network_v1_packets{0};
    unsigned network_v2_packets{0};
    unsigned network_v1_addresses{0};
    unsigned network_v2_addresses{0};
    unsigned transport_v1_packets{0};
    unsigned transport_v2_packets{0};
    unsigned transport_v1_errors{0};
    unsigned transport_v2_errors{0};
    unsigned transport_v1_ports{0};
    unsigned transport_v2_ports{0};
    unsigned transport_v2_sessions{0};
    unsigned text_packets{0};
    unsigned binary_packets{0};
    unsigned json_packets{0};
};

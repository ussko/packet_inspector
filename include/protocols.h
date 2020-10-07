#pragma once

#include <stdint.h>

#pragma pack(1)

enum network_version
{
    NETWORK_V1 = 0x01,
    NETWORK_V2 = 0x02
};

struct network_v1_t
{
    uint8_t     version;
    uint32_t    addr_src;
    uint32_t    addr_dst;
    uint8_t     protocol;
    uint16_t    data_size;
    uint16_t    check_sum;
};

struct network_v2_t
{
    uint8_t     version;
    uint8_t     addr_src[6];
    uint8_t     addr_dst[6];
    uint8_t     protocol;
    uint16_t    data_size;
    uint16_t    check_sum;
};

union network_t
{
    network_v1_t v1;
    network_v2_t v2;
};

static const size_t MAX_DATA_SIZE = UINT16_MAX + 1;

enum transport_version
{
    TRANSPORT_V1 = 0x01,
    TRANSPORT_V2 = 0x02
};

struct transport_v1_t
{
    uint16_t    port_src;
    uint16_t    port_dst;
    uint16_t    data_size;
};

struct transport_v2_t
{
    uint16_t    port_src;
    uint16_t    port_dst;
    uint32_t    num_fragment;
    uint8_t     session;
    uint16_t    data_size;
};

static const uint8_t SESSION_FIRST = 0x01;
static const uint8_t SESSION_LAST  = 0x02;

#pragma pack()

#pragma once

#include <stdint.h>

inline void ntoh6(uint8_t *in, uint64_t &out)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    reinterpret_cast<uint8_t*>(&out)[5] = in[0];
    reinterpret_cast<uint8_t*>(&out)[4] = in[1];
    reinterpret_cast<uint8_t*>(&out)[3] = in[2];
    reinterpret_cast<uint8_t*>(&out)[2] = in[3];
    reinterpret_cast<uint8_t*>(&out)[1] = in[4];
    reinterpret_cast<uint8_t*>(&out)[0] = in[5];
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    reinterpret_cast<uint8_t*>(&out)[0] = in[0];
    reinterpret_cast<uint8_t*>(&out)[1] = in[1];
    reinterpret_cast<uint8_t*>(&out)[2] = in[2];
    reinterpret_cast<uint8_t*>(&out)[3] = in[3];
    reinterpret_cast<uint8_t*>(&out)[4] = in[4];
    reinterpret_cast<uint8_t*>(&out)[5] = in[5];
#endif
}

inline void hton6(uint64_t &in, uint8_t *out)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    out[5] = reinterpret_cast<uint8_t*>(&in)[0];
    out[4] = reinterpret_cast<uint8_t*>(&in)[1];
    out[3] = reinterpret_cast<uint8_t*>(&in)[2];
    out[2] = reinterpret_cast<uint8_t*>(&in)[3];
    out[1] = reinterpret_cast<uint8_t*>(&in)[4];
    out[0] = reinterpret_cast<uint8_t*>(&in)[5];
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    out[0] = reinterpret_cast<uint8_t*>(&in)[0];
    out[1] = reinterpret_cast<uint8_t*>(&in)[1];
    out[2] = reinterpret_cast<uint8_t*>(&in)[2];
    out[3] = reinterpret_cast<uint8_t*>(&in)[3];
    out[4] = reinterpret_cast<uint8_t*>(&in)[4];
    out[5] = reinterpret_cast<uint8_t*>(&in)[5];
#endif
}

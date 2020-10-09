#pragma once

#include <map>
#include <unordered_map>
#include <vector>

#include "buffer.h"
#include "protocols.h"
#include "stats.h"

class SessionManager
{
public:
    struct endpoint_t
    {
        uint64_t addr;
        uint16_t port;
    };

    void add_fragment(endpoint_t src, endpoint_t dst, uint32_t fragment_number,
                      uint8_t flags);
    void add_fragment_data(endpoint_t src, endpoint_t dst, uint32_t fragment_number,
                           buf_iterator data_begin, buf_iterator data_end);
    void update_stats(stats_t &stats);

private:
    struct session_id_t
    {
        endpoint_t src;
        endpoint_t dst;
    };
    struct session_id_hash
    {
        size_t operator()(const session_id_t &id) const;
    };
    struct session_id_eq
    {
        bool operator()(const session_id_t &lhs, const session_id_t &rhs) const;
    };
    struct session_t
    {
        std::map<uint32_t, std::vector<uint8_t>> fragments;
        uint32_t first{0};
        uint32_t last{0};
        bool has_first{false};
        bool has_last{false};
    };

    std::unordered_multimap<session_id_t, session_t, session_id_hash, session_id_eq> _sessions;
    unsigned _num_sessions{0};

    bool _is_valid_session(const session_t &session);
};

inline size_t SessionManager::session_id_hash::operator()(const session_id_t &id) const
{
    return std::hash<uint64_t>{}(id.src.addr) ^ (std::hash<uint16_t>{}(id.src.port) << 1) ^
           std::hash<uint64_t>{}(id.dst.addr) ^ (std::hash<uint16_t>{}(id.dst.port) << 1);
}

inline bool SessionManager::session_id_eq::operator()(const session_id_t &lhs,
                                                      const session_id_t &rhs) const
{
    return lhs.src.addr == rhs.src.addr && lhs.src.port == rhs.src.port &&
           lhs.dst.addr == rhs.dst.addr && lhs.dst.port == rhs.dst.port;
}

#pragma once

#include "session_manager.h"
#include "transport_inspector.h"

class TransportInspectorV2: public TransportInspector
{
public:
    TransportInspectorV2();

    void update_stats(stats_t &stats) override;
    void set_current_addr(uint64_t addr_src, uint64_t addr_dst);

protected:
    bool _process_header(buf_iterator header_begin) override;
    void _process_payload(buf_iterator data_begin, buf_iterator data_end) override;

private:
    SessionManager _session_mgr;
    SessionManager::endpoint_t _src_current;
    SessionManager::endpoint_t _dst_current;
    uint32_t _fragment_num_current{0};
};

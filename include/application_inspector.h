#pragma once

#include <vector>

#include "buffer.h"

class ApplicationInspector
{
public:
    enum app_data_class
    {
        APP_ERROR,

        APP_JSON,
        APP_TEXT,
        APP_BINARY
    };

    app_data_class process_data(buf_iterator begin, buf_iterator end);
    void add_session_fragment(const std::vector<uint8_t> &fragment);
    app_data_class process_session();

private:
    static constexpr uint8_t JSON_MIN{' '};
    static constexpr uint8_t JSON_MAX{'}'};
    static constexpr uint8_t TEXT_MIN{'\n'};
    static constexpr uint8_t TEXT_MAX{'z'};

    uint8_t _session_max{0};
    uint8_t _session_min{UINT8_MAX};

    void _get_min_max(const uint8_t *data, size_t length, uint8_t &min, uint8_t &max);
    app_data_class _get_data_class(uint8_t min, uint8_t max);
};

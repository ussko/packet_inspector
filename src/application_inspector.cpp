#include "application_inspector.h"

ApplicationInspector::app_data_class ApplicationInspector::process_data(buf_iterator begin,
                                                                        buf_iterator end)
{
    uint8_t data_max{0};
    uint8_t data_min{UINT8_MAX};

    _get_min_max(begin, std::distance(begin, end), data_min, data_max);
    return _get_data_class(data_min, data_max);
}

void ApplicationInspector::add_session_fragment(const std::vector<uint8_t> &fragment)
{
    _get_min_max(fragment.data(), fragment.size(), _session_min, _session_max);
}

ApplicationInspector::app_data_class ApplicationInspector::process_session()
{
    if (_session_max < _session_min)
        return APP_ERROR;

    auto data_class = _get_data_class(_session_min, _session_max);
    _session_max = 0;
    _session_min = UINT8_MAX;
    return data_class;
}

void ApplicationInspector::_get_min_max(const uint8_t *data, size_t length,
                                        uint8_t &min, uint8_t &max)
{
    for (size_t i = 0; i < length; ++i)
    {
        if (data[i] > max)
            max = data[i];
        if (data[i] < min)
            min = data[i];
    }
}

ApplicationInspector::app_data_class ApplicationInspector::_get_data_class(uint8_t min,
                                                                           uint8_t max)
{
    if (max > 0x80)
        return APP_BINARY;
    if (min >= TEXT_MIN && max <= TEXT_MAX)
        return APP_TEXT;
    if (min >= JSON_MIN && max <= JSON_MAX)
        return APP_JSON;
    return APP_BINARY;
}

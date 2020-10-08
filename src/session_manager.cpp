#include "session_manager.h"

void SessionManager::add_fragment(endpoint_t src, endpoint_t dst,
                                  uint32_t fragment_number, uint8_t flags)
{
    const session_id_t session_id{src, dst};
    const session_fragment_t fragment{.fragment_number = fragment_number, .data{}};

    auto insert_fragment = [&fragment, &flags](session_t &session)
    {
        session.fragments.insert(fragment);
        if (flags & SESSION_FIRST)
        {
            session.has_first = true;
            session.first = fragment.fragment_number;
        }
        if (flags & SESSION_LAST)
        {
            session.has_last = true;
            session.last = fragment.fragment_number;
        }
    };

    if (_sessions.count(session_id) == 0)
    {
        session_t session;
        insert_fragment(session);
        _sessions.insert({session_id, session});
    }

    auto [begin, end] = _sessions.equal_range(session_id);
    for (; begin != end; ++begin)
    {
        if (auto &[id, session] = *begin; session.fragments.count(fragment))
            continue;
        else
            insert_fragment(session);
    }
}

void SessionManager::add_fragment_data(endpoint_t src, endpoint_t dst, uint32_t fragment_number,
                                       buf_iterator data_begin, buf_iterator data_end)
{
    const session_id_t session_id{src, dst};
    const session_fragment_t fragment{.fragment_number = fragment_number, .data{}};

    if (_sessions.count(session_id) == 0)
        return;

    auto [begin, end] = _sessions.equal_range(session_id);
    for (; begin != end; ++begin)
    {
        auto &[id, session] = *begin;
        if (auto it = session.fragments.find(fragment);
            it != session.fragments.end())
        {
            auto fragment_handler = session.fragments.extract(it);
            fragment_handler.value().data.assign(data_begin, data_end);
            session.fragments.insert(std::move(fragment_handler));
        }
    }
}

void SessionManager::update_stats(stats_t &stats)
{
    for (const auto &[id, session] : _sessions)
    {
        if (!_is_valid_session(session))
            continue;
        _num_sessions++;
    }

    stats.transport_v2_sessions += _num_sessions;
}

bool SessionManager::_is_valid_session(const session_t &session)
{
    if (!session.has_first || !session.has_last)
        return false;

    for (auto begin = session.fragments.begin(); begin != session.fragments.end(); ++begin)
    {
        if (begin == session.fragments.begin())
            continue;

        auto prev = begin;
        std::advance(prev, -1);
        if (begin->fragment_number != prev->fragment_number + 1)
            return false;
    }
    return true;
}

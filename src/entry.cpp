#include "ar/entry.hpp"

ar::entry::entry(day_type day, entry_type type)
    : _day{day}
    , _type{type}
    , _checkin{QTime(0, 0)}
    , _checkout{QTime(0, 0)}
    , _break_begin{QTime(0, 0)}
    , _break_end{QTime(0, 0)}
{
}

bool ar::entry::validate()
{
    _is_valid = _checkin.isValid() && _checkout.isValid() && _break_begin.isValid() && _break_end.isValid();
    _is_valid &= _checkin <= _checkout;
    _is_valid &= _break_begin <= _break_end;
    _is_valid &= _checkin <= _break_begin;
    
    return _is_valid;
}

void ar::entry::set_checkin(QTime checkin)
{
    _checkin = checkin;
    refresh();
}

void ar::entry::set_checkout(QTime checkout)
{
    _checkout = checkout;
    refresh();
}

void ar::entry::set_break_begin(QTime break_begin)
{
    _break_begin = break_begin;
    refresh();
}

void ar::entry::set_break_end(QTime break_end)
{
    _break_end = break_end;
}

QTime ar::entry::get_checkin()
{
    return _checkin;
}

QTime ar::entry::get_checkout()
{
    return _checkout;
}

QTime ar::entry::get_break_begin()
{
    return _break_begin;
}

QTime ar::entry::get_break_end()
{
    return _break_end;
}

void ar::entry::refresh()
{
    if (validate())
    {
        auto time_attended = _checkout - _checkin;
        auto time_break = _break_end - _break_begin;
        _time_worked = time_attended - time_break;
    }
}

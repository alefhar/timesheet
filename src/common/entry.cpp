#include "ar/entry.hpp"

#include <iostream>

ar::entry::entry()
    : entry{-1, ar::entry_type::DEFAULT}
{}

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
    if (_break_begin != QTime(0, 0) || _break_end != QTime(0, 0))
    {
        _is_valid &= _break_begin <= _break_end;
        _is_valid &= _checkin <= _break_begin;
    }
   
    return _is_valid;
}

void ar::entry::set(const QVariant &object, int column)
{
    switch (column)
    {
        case TYPE_COLUMN:
            set_type(static_cast<entry_type>(object.toInt()));
            break;
        case CHECKIN_COLUMN:
            set_checkin(object.toTime());
            break;
        case CHECKOUT_COLUMN:
            set_checkout(object.toTime());
            break;
        case BREAK_BEGIN_COLUMN:
            set_break_begin(object.toTime());
            break;
        case BREAK_END_COLUMN:
            set_break_end(object.toTime());
    }
}

void ar::entry::set_type(const entry_type &type)
{
    _type = type;
    refresh();
}

void ar::entry::set_checkin(const QTime &checkin)
{
    _checkin = checkin;
    refresh();
}

void ar::entry::set_checkout(const QTime &checkout)
{
    _checkout = checkout;
    refresh();
}

void ar::entry::set_break_begin(const QTime &break_begin)
{
    _break_begin = break_begin;
    refresh();
}

void ar::entry::set_break_end(const QTime &break_end)
{
    _break_end = break_end;
    refresh();
}

QVariant ar::entry::get(int column) const
{
    switch (column)
    {
        case 0:
            return QVariant(get_day());
        case 1:
            return QVariant(static_cast<int>(_type));
        case 2:
            return QVariant(get_checkin());
        case 3:
            return QVariant(get_checkout());
        case 4:
            return QVariant(get_break_begin());
        case 5:
            return QVariant(get_break_end());
        case 6:
            return QVariant(get_time_worked());
    }
}

int ar::entry::get_day() const
{
    return _day;
}

ar::entry_type ar::entry::get_type() const
{
    return _type;
}

QTime ar::entry::get_checkin() const
{
    return _checkin;
}

QTime ar::entry::get_checkout() const
{
    return _checkout;
}

QTime ar::entry::get_break_begin() const
{
    return _break_begin;
}

QTime ar::entry::get_break_end() const
{
    return _break_end;
}

QString ar::entry::get_time_worked() const
{
    return _time_worked.toString(TIME_FORMAT);
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
void ar::entry::read(const QJsonObject &json)
{
    _type = static_cast<entry_type>(json["type"].toString().toUInt());
    _day = json["day"].toString().toUInt();
    _checkin = QTime::fromString(json["checkin"].toString(), TIME_FORMAT);
    _checkout = QTime::fromString(json["checkout"].toString(), TIME_FORMAT);
    _break_begin = QTime::fromString(json["break_begin"].toString(), TIME_FORMAT);
    _break_end = QTime::fromString(json["break_end"].toString(), TIME_FORMAT);
    _time_worked = QTimeSpan::fromString(json["time_worked"].toString(), TIME_FORMAT);
}

void ar::entry::write(QJsonObject &json) const
{
    json["type"] = QString::number(static_cast<int>(_type));
    json["day"] = QString::number(_day);
    json["checkin"] = _checkin.toString(TIME_FORMAT);
    json["checkout"] = _checkout.toString(TIME_FORMAT);
    json["break_begin"] = _break_begin.toString(TIME_FORMAT);
    json["break_end"] = _break_end.toString(TIME_FORMAT);
    json["time_worked"] = _time_worked.toString(TIME_FORMAT);
}

int ar::entry::get_column_count()
{
    return COLUMN_COUNT;
}

QString ar::entry::get_header_name(int index)
{
    return COLUMN_NAMES[index];
}
            
Qt::ItemFlags ar::entry::get_flags(Qt::ItemFlags current_flags, int index) const
{
    if (_type == entry_type::HOLIDAY || _type == entry_type::VACATION)
    {
        if (index == TYPE_COLUMN)
        {
            return current_flags | Qt::ItemIsEditable;
        }
        else
        {
            return current_flags & ~Qt::ItemIsEditable;
        }
    }

    if (index >= TYPE_COLUMN && index <= BREAK_END_COLUMN)
    {
        return current_flags | Qt::ItemIsEditable;
    }

    return current_flags & ~Qt::ItemIsEditable;
}

const QString ar::entry::TIME_FORMAT = "hh:mm";

const QString ar::entry::COLUMN_NAMES[] = {"Day", "Type", "Checkin", "Checkout", "Break Begin", "Break End", "Time Worked" };

#include "ar/timesheet_page.hpp"

ar::timesheet_page::timesheet_page()
    : timesheet_page{-1, -1}
{
    QDate date = QDate::currentDate();
    _year = date.year();
    _month = date.month();
    
    init();
}

ar::timesheet_page::timesheet_page(int year, int month)
    : _entries{}
    , _year{year}
    , _month{month}
{
    if (QDate::isValid(_year, _month, 1))
    {
        init();
    }
}
            
QVariant ar::timesheet_page::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (orientation == Qt::Horizontal)
    {
        return ar::entry::get_header_name(section);
    }

    return QVariant();
}

int ar::timesheet_page::rowCount(const QModelIndex &/*parent*/) const
{
    return _entries.size();
}

int ar::timesheet_page::columnCount(const QModelIndex &/*parent*/) const
{
    return ar::entry::get_column_count();
}

QVariant ar::timesheet_page::data(const QModelIndex &index, int role) const
{
    if (role == Qt::BackgroundRole)
    {
        QDate date(_year, _month, index.row() + 1);
        int day_of_week = date.dayOfWeek();
        if (day_of_week == Qt::Saturday || day_of_week == Qt::Sunday)
        {
            return QVariant(QBrush(Qt::lightGray));
        }
        else
        {
            return QVariant(QBrush(Qt::white));
        }
    }

    if (role == Qt::DisplayRole)
    {
        auto &entry = _entries[index.row()];
        return entry.get(index.column());
    }

    return QVariant();
}
            
Qt::ItemFlags ar::timesheet_page::flags(const QModelIndex &index) const
{
    Qt::ItemFlags current_flags = QAbstractTableModel::flags(index);
    Qt::ItemFlags entry_flags = _entries[index.row()].get_flags(current_flags, index.column());
    if (!is_weekday(index.row() + 1)) {
        entry_flags &= ~Qt::ItemIsEditable;
    }

    return entry_flags;
}
            
bool ar::timesheet_page::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
    {
        return false;
    }

    _entries[index.row()].set(value, index.column());

    return true;
}

void ar::timesheet_page::init()
{
    QDate date(_year, _month, 1);
    _entries.reserve(date.daysInMonth());
    for (auto day = 1; day <= date.daysInMonth(); ++day)
    {
        _entries.push_back(entry{day, ar::entry_type::DEFAULT});
    }
}

bool ar::timesheet_page::is_weekday(int day) const
{
    QDate date(_year, _month, day);

    int day_of_week = date.dayOfWeek();
    return day_of_week != Qt::Saturday && day_of_week != Qt::Sunday;
}

void ar::timesheet_page::read(const QJsonObject &json)
{
    _year = json["year"].toInt();
    _month = json["month"].toInt();
    QJsonArray entries = json["entries"].toArray();
    _entries.reserve(entries.size());
    for (const auto& jsonEntry : entries)
    {
        entry e;
        e.read(jsonEntry.toObject());
        _entries.push_back(e);
    }
}

void ar::timesheet_page::write(QJsonObject &json)
{
    json["year"] = QString::number(_year);
    json["month"] = QString::number(_month);
    QJsonArray entries;
    for (const auto &e : _entries)
    {
        QJsonObject jsonEntry;
        e.write(jsonEntry);
        entries.append(jsonEntry);
    }
    json["entries"] = entries;
}

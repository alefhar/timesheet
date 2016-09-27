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

void ar::timesheet_page::init()
{
    QDate date(_year, _month, 1);
    _entries.reserve(date.daysInMonth());
    for (auto day = 1; day <= date.daysInMonth(); ++day)
    {
        _entries.push_back(entry{day, ar::entry_type::DEFAULT});
    }
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

#include "ar/preferences.hpp"

double ar::preferences::get_hourly_wage()
{
    return _hourly_wage;
}

double ar::preferences::get_monthly_wage()
{
    return _monthly_wage;
}

int ar::preferences::get_vacation_days()
{
    return _vacation_days;
}

void ar::preferences::set_hourly_wage(double hourly_wage)
{
    _hourly_wage = hourly_wage;
}

void ar::preferences::set_monthly_wage(double monthly_wage)
{
    _monthly_wage = monthly_wage;
}

void ar::preferences::set_vacation_days(int vacation_days)
{
    _vacation_days = vacation_days;
}

void ar::preferences::read(const QJsonObject &json)
{
    set_hourly_wage(json["hourly_wage"].toDouble());
    set_monthly_wage(json["monthly_wage"].toDouble());
    set_vacation_days(json["vacation_days"].toInt());
}

void ar::preferences::write(QJsonObject &json)
{
    json["hourly_wage"] = QString::number(_hourly_wage);
    json["monthly_wage"] = QString::number(_monthly_wage);
    json["vacation_days"] = QString::number(_vacation_days);
}

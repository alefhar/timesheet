#ifndef PREFERENCES_HPP_JWOPJI1V
#define PREFERENCES_HPP_JWOPJI1V

#include <QtCore/QJsonObject>

namespace ar
{
    class preferences
    {
        private:
            double _hourly_wage;

            double _monthly_wage;

            int _vacation_days;

        public:
            double get_hourly_wage();

            double get_monthly_wage();

            int get_vacation_days();

            void set_hourly_wage(double hourly_wage);

            void set_monthly_wage(double monthly_wage);

            void set_vacation_days(int vacation_days);
            
            void read(const QJsonObject &json);

            void write(QJsonObject &json);
    };
}

#endif /* end of include guard: PREFERENCES_HPP_JWOPJI1V */

#ifndef ENTRY_HPP_AFKDJFSC
#define ENTRY_HPP_AFKDJFSC

#include "defines.hpp"
#include "entry_type.hpp"

#include "qtimespan.h"

#include <QtCore/QTime>
#include <QtCore/QString>
#include <QtCore/QJsonObject>

namespace ar
{
    class entry
    {
        private:
            day_type _day;
            
            entry_type _type;

            QTime _checkin;

            QTime _checkout;

            QTime _break_begin;

            QTime _break_end;

            QTimeSpan _time_worked;

            bool _is_valid;

            const QString TIME_FORMAT = "hh:mm";

        public:
            entry();

            entry(day_type day, entry_type type);

            bool validate();

            void set_checkin(QTime checkin);

            void set_checkout(QTime checkout);

            void set_break_begin(QTime break_begin);

            void set_break_end(QTime break_end);

            QTime get_checkin() const;

            QTime get_checkout() const;

            QTime get_break_begin() const;

            QTime get_break_end() const;

            void read(const QJsonObject &json);

            void write(QJsonObject &json) const;

        private:
            void refresh();
    };
}

#endif /* end of include guard: ENTRY_HPP_AFKDJFSC */

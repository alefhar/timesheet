#ifndef ENTRY_HPP_AFKDJFSC
#define ENTRY_HPP_AFKDJFSC

#include "defines.hpp"
#include "entry_type.hpp"

#include "qtimespan.h"

#include <QtCore/QTime>
#include <QtCore/QString>
#include <QtCore/QVariant>
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

            static const QString TIME_FORMAT;// = "hh:mm";

            static const int DAY_COLUMN = 0;

            static const int TYPE_COLUMN = 1;

            static const int CHECKIN_COLUMN = 2;

            static const int CHECKOUT_COLUMN = 3;

            static const int BREAK_BEGIN_COLUMN = 4;

            static const int BREAK_END_COLUMN = 5;

            static const int TIME_WORKED_COLUMN = 6;

            static const int COLUMN_COUNT = 7;

            static const QString COLUMN_NAMES[];

        public:
            entry();

            entry(day_type day, entry_type type);

            bool validate();

            void set(const QVariant &object, int column);

            void set_type(const entry_type &type);

            void set_checkin(const QTime &checkin);

            void set_checkout(const QTime &checkout);

            void set_break_begin(const QTime &break_begin);

            void set_break_end(const QTime &break_end);

            QVariant get(int column) const;

            int get_day() const;

            entry_type get_type() const;

            QTime get_checkin() const;

            QTime get_checkout() const;

            QTime get_break_begin() const;

            QString get_time_worked() const;

            QTime get_break_end() const;

            Qt::ItemFlags get_flags(Qt::ItemFlags current_flags, int index) const;

            void read(const QJsonObject &json);

            void write(QJsonObject &json) const;

            static int get_column_count();

            static QString get_header_name(int index);

        private:
            void refresh();
    };
}

#endif /* end of include guard: ENTRY_HPP_AFKDJFSC */

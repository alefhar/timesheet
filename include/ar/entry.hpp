#pragma once

#include "defines.hpp"
#include "entry_type.hpp"

#include "qtimespan.h"

#include <QtCore/QTime>

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

        public:
            entry(day_type day, entry_type type);

            bool validate();

            void set_checkin(QTime checkin);

            void set_checkout(QTime checkout);

            void set_break_begin(QTime break_begin);

            void set_break_end(QTime break_end);

            QTime get_checkin();

            QTime get_checkout();

            QTime get_break_begin();

            QTime get_break_end();

        private:
            void refresh();
    };
}

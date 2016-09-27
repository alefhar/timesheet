#ifndef TIMESHEET_PAGE_HPP_89BZKGFX
#define TIMESHEET_PAGE_HPP_89BZKGFX

#include "ar/entry.hpp"

#include <vector>

#include <QtCore/QDate>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>

namespace ar
{
    class timesheet_page
    {
        private:
            std::vector<entry> _entries;

            int _year;

            int _month;

        public:
            timesheet_page();

            timesheet_page(int year, int month);

            void read(const QJsonObject &json);

            void write(QJsonObject &json);

        private:
            void init();
    };
}

#endif /* end of include guard: TIMESHEET_PAGE_HPP_89BZKGFX */

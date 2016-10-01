#ifndef TIMESHEET_PAGE_HPP_89BZKGFX
#define TIMESHEET_PAGE_HPP_89BZKGFX

#include "ar/entry.hpp"

#include <vector>

#include <QtCore/QAbstractTableModel>
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>
#include <QtCore/QDate>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>

#include <QtGui/QBrush>

namespace ar
{
    class timesheet_page : public QAbstractTableModel
    {
        private:
            std::vector<entry> _entries;

            int _year;

            int _month;

        public:
            timesheet_page();

            timesheet_page(int year, int month);

            virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

            virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

            virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

            virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

            virtual Qt::ItemFlags flags(const QModelIndex &index) const;

            virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

            void read(const QJsonObject &json);

            void write(QJsonObject &json);

        private:
            void init();
    };
}

#endif /* end of include guard: TIMESHEET_PAGE_HPP_89BZKGFX */

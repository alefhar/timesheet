#include "ar/defines.hpp"
#include "ar/timesheet_page.hpp"
#include "ar/entry_type_delegate.hpp"

#include <QtWidgets/QApplication>
#include <QtWidgets/QTableView>
#include <QtWidgets/QHeaderView>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QTableView *view = new QTableView();
    ar::entry_type_delegate delegate;
    
    ar::timesheet_page *model = new ar::timesheet_page();
    view->setModel(model);
    view->setItemDelegateForColumn(1, &delegate);

    view->show();
    view->horizontalHeader()->show();

    return app.exec();
}

//! [Quoting ModelView Tutorial]
// main.cpp
#include <QtGui>
#include <QtWidgets>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTableView>

#include "cell.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Board<> board;
    auto c = board.cellAt(0);

    QMessageBox msg;
    msg.setText( QString( "Hello %1" ).arg( c.id() ) );
    msg.show();

    return a.exec();
}

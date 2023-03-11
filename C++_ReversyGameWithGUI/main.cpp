#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *main_menu = new MainWindow;
    main_menu->show();

    return app.exec();
}

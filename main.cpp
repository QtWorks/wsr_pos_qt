#include "mainwindow.h"
#include "Setting/settingwidget.h"
#include "print/printer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	//MainWindow w;
	//SettingWidget w;
	printer w;
	w.show();


    return a.exec();
}

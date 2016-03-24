#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include "ui_main.h"
#include "pkginfo.h"
#include "pkgr.h"

#include <iostream>
using std::cerr;
using std::endl;

void
addPkgDetailToTable(QTableWidget *tableWidget, PkgDetail pkgDetail) {

	QTableWidgetItem *name = new QTableWidgetItem(pkgDetail.name);
	QTableWidgetItem *desc = new QTableWidgetItem(pkgDetail.desc);
	QTableWidgetItem *version = new QTableWidgetItem(pkgDetail.version);
	QTableWidgetItem *installed = new QTableWidgetItem(pkgDetail.installed);

	int rowCount = tableWidget->rowCount();
	tableWidget->setRowCount(rowCount+1);

	tableWidget->setItem(rowCount, 0, name);
	tableWidget->setItem(rowCount, 1, version);
	tableWidget->setItem(rowCount, 2, installed);
	tableWidget->setItem(rowCount, 3, desc);
}

int
main(int argc, char *argv[])
{
	QString user = qgetenv("USER");
	if ( user != "root" ) {
		cerr << "qkgr must be run with root privileges, please use \"gksu qkgr\"." << endl;
		return -1;
	}

    QApplication app(argc, argv);
    QMainWindow *mainWindow = new QMainWindow;
    Ui::MainWindow ui;
    ui.setupUi(mainWindow);

    mainWindow->show();

	ui.tableWidget->setColumnCount(4);

	QStringList headerLabels;
	headerLabels << "Name" << "Version" << "Installed" << "Description";
	ui.tableWidget->setHorizontalHeaderLabels(headerLabels);

	foreach( QString pkg, PkgInfo::GetPkgList() ) {
		cerr << "Adding " << pkg.toStdString() << endl;
		addPkgDetailToTable(ui.tableWidget, PkgInfo::GetPkgDetail(pkg));
	}

	return app.exec();
}

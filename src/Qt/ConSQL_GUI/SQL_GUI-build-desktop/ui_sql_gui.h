/********************************************************************************
** Form generated from reading UI file 'sql_gui.ui'
**
** Created: Thu Mar 15 20:07:01 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SQL_GUI_H
#define UI_SQL_GUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SQL_GUI
{
public:
    QWidget *centralWidget;
    QTextEdit *FenetreInfo;
    QTableView *tableView;
    QTextEdit *FenetreRequete;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SQL_GUI)
    {
        if (SQL_GUI->objectName().isEmpty())
            SQL_GUI->setObjectName(QString::fromUtf8("SQL_GUI"));
        SQL_GUI->resize(422, 366);
        centralWidget = new QWidget(SQL_GUI);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        FenetreInfo = new QTextEdit(centralWidget);
        FenetreInfo->setObjectName(QString::fromUtf8("FenetreInfo"));
        FenetreInfo->setGeometry(QRect(5, 230, 411, 71));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(244, 10, 171, 192));
        FenetreRequete = new QTextEdit(centralWidget);
        FenetreRequete->setObjectName(QString::fromUtf8("FenetreRequete"));
        FenetreRequete->setGeometry(QRect(10, 10, 221, 191));
        SQL_GUI->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SQL_GUI);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 422, 25));
        SQL_GUI->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SQL_GUI);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SQL_GUI->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SQL_GUI);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SQL_GUI->setStatusBar(statusBar);

        retranslateUi(SQL_GUI);

        QMetaObject::connectSlotsByName(SQL_GUI);
    } // setupUi

    void retranslateUi(QMainWindow *SQL_GUI)
    {
        SQL_GUI->setWindowTitle(QApplication::translate("SQL_GUI", "SQL_GUI", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SQL_GUI: public Ui_SQL_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SQL_GUI_H

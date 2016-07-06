/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *itemsGroup;
    QLineEdit *itemName;
    QPushButton *pushButton;
    QListWidget *listWidget;
    QGroupBox *groupBox;
    QPushButton *searchButton;
    QLineEdit *queryLine;
    QListWidget *searchResultsList;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(892, 626);
        MainWindow->setMinimumSize(QSize(892, 626));
        MainWindow->setMaximumSize(QSize(892, 626));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        itemsGroup = new QGroupBox(centralWidget);
        itemsGroup->setObjectName(QStringLiteral("itemsGroup"));
        itemsGroup->setGeometry(QRect(10, 10, 451, 401));
        itemName = new QLineEdit(itemsGroup);
        itemName->setObjectName(QStringLiteral("itemName"));
        itemName->setGeometry(QRect(10, 20, 351, 20));
        pushButton = new QPushButton(itemsGroup);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(365, 20, 75, 23));
        listWidget = new QListWidget(itemsGroup);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 50, 431, 341));
        QFont font;
        font.setPointSize(10);
        listWidget->setFont(font);
        listWidget->setIconSize(QSize(32, 44));
        listWidget->setFlow(QListView::TopToBottom);
        listWidget->setProperty("isWrapping", QVariant(false));
        listWidget->setResizeMode(QListView::Fixed);
        listWidget->setViewMode(QListView::ListMode);
        listWidget->setSelectionRectVisible(true);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(470, 10, 391, 401));
        searchButton = new QPushButton(groupBox);
        searchButton->setObjectName(QStringLiteral("searchButton"));
        searchButton->setGeometry(QRect(300, 20, 75, 23));
        queryLine = new QLineEdit(groupBox);
        queryLine->setObjectName(QStringLiteral("queryLine"));
        queryLine->setGeometry(QRect(20, 20, 271, 20));
        searchResultsList = new QListWidget(groupBox);
        searchResultsList->setObjectName(QStringLiteral("searchResultsList"));
        searchResultsList->setGeometry(QRect(20, 50, 351, 341));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Tv Tracker V1.0", 0));
        itemsGroup->setTitle(QApplication::translate("MainWindow", "Items list", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Add item", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Search", 0));
        searchButton->setText(QApplication::translate("MainWindow", "Search", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

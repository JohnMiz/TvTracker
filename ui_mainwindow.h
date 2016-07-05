/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
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
        itemsGroup->setGeometry(QRect(430, 10, 451, 401));
        itemName = new QLineEdit(itemsGroup);
        itemName->setObjectName(QStringLiteral("itemName"));
        itemName->setGeometry(QRect(10, 30, 351, 20));
        pushButton = new QPushButton(itemsGroup);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(365, 30, 75, 23));
        listWidget = new QListWidget(itemsGroup);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 60, 431, 331));
        QFont font;
        font.setPointSize(10);
        listWidget->setFont(font);
        listWidget->setIconSize(QSize(32, 44));
        listWidget->setFlow(QListView::TopToBottom);
        listWidget->setProperty("isWrapping", QVariant(false));
        listWidget->setResizeMode(QListView::Fixed);
        listWidget->setViewMode(QListView::ListMode);
        listWidget->setSelectionRectVisible(true);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Tv Tracker V1.0", 0));
        itemsGroup->setTitle(QApplication::translate("MainWindow", "Items list", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Add item", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

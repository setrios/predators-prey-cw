/********************************************************************************
** Form generated from reading UI file 'statswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATSWINDOW_H
#define UI_STATSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_StatsWindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *ShowLabel;
    QCheckBox *plantsCheckBox;
    QCheckBox *preysCheckBox;
    QCheckBox *predatorsCheckBox;
    QTableView *tableView;

    void setupUi(QDialog *StatsWindow)
    {
        if (StatsWindow->objectName().isEmpty())
            StatsWindow->setObjectName("StatsWindow");
        StatsWindow->resize(1000, 500);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(StatsWindow->sizePolicy().hasHeightForWidth());
        StatsWindow->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(StatsWindow);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        ShowLabel = new QLabel(StatsWindow);
        ShowLabel->setObjectName("ShowLabel");

        horizontalLayout->addWidget(ShowLabel);

        plantsCheckBox = new QCheckBox(StatsWindow);
        plantsCheckBox->setObjectName("plantsCheckBox");
        plantsCheckBox->setChecked(false);

        horizontalLayout->addWidget(plantsCheckBox);

        preysCheckBox = new QCheckBox(StatsWindow);
        preysCheckBox->setObjectName("preysCheckBox");
        preysCheckBox->setChecked(true);

        horizontalLayout->addWidget(preysCheckBox);

        predatorsCheckBox = new QCheckBox(StatsWindow);
        predatorsCheckBox->setObjectName("predatorsCheckBox");
        predatorsCheckBox->setChecked(true);

        horizontalLayout->addWidget(predatorsCheckBox);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(StatsWindow);
        tableView->setObjectName("tableView");

        verticalLayout->addWidget(tableView);


        retranslateUi(StatsWindow);

        QMetaObject::connectSlotsByName(StatsWindow);
    } // setupUi

    void retranslateUi(QDialog *StatsWindow)
    {
        StatsWindow->setWindowTitle(QCoreApplication::translate("StatsWindow", "Dialog", nullptr));
        ShowLabel->setText(QCoreApplication::translate("StatsWindow", "Show: ", nullptr));
        plantsCheckBox->setText(QCoreApplication::translate("StatsWindow", "Plants", nullptr));
        preysCheckBox->setText(QCoreApplication::translate("StatsWindow", "Preys", nullptr));
        predatorsCheckBox->setText(QCoreApplication::translate("StatsWindow", "Predators", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StatsWindow: public Ui_StatsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATSWINDOW_H

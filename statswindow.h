#ifndef STATSWINDOW_H
#define STATSWINDOW_H

#include <QDialog>
#include <QStandardItemModel>
#include <QTimer>
#include "field.h"


namespace Ui {
class StatsWindow;
}

class StatsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StatsWindow(QWidget *parent = nullptr, Field* field = nullptr);
    ~StatsWindow();
    void showStats();

public slots:
    void updateStats();
    void setRefreshRate(int milliseconds);
    void pauseRefresh();
    void resumeRefresh();

private slots:
    void on_plantsCheckBox_checkStateChanged(const Qt::CheckState &arg1);

    void on_preysCheckBox_checkStateChanged(const Qt::CheckState &arg1);

    void on_predatorsCheckBox_checkStateChanged(const Qt::CheckState &arg1);

private:
    Ui::StatsWindow *ui;
    Field* fieldPtr;
    QStandardItemModel* model;
    QTimer *refreshTimer;

    bool showPlants = false;
    bool showPreys = true;
    bool showPredators = true;
};

#endif // STATSWINDOW_H

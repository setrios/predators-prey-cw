#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer> // for setting update speed for scene and stats table
#include <QtCharts>

#include <field.h>
#include "statswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void runSimulationStep();

    void updateChartDisplay();

    void on_runButton_clicked();

    void on_finishButton_clicked();

    void on_grassNumSpinBox_valueChanged(int arg1);

    void on_bunnyNumSpinBox_valueChanged(int arg1);

    void on_shroomNumSpinBox_valueChanged(int arg1);

    void on_deerNumSpinBox_valueChanged(int arg1);

    void on_foxNumSpinBox_valueChanged(int arg1);

    void on_wolfNumSpinBox_valueChanged(int arg1);

    void on_bunnyHungerSpinBox_valueChanged(int arg1);

    void on_deerHungerSpinBox_valueChanged(int arg1);

    void on_foxHungerSpinBox_valueChanged(int arg1);

    void on_wolfHungerSpinBox_valueChanged(int arg1);

    void on_grassReprChanceSpinBox_valueChanged(int arg1);

    void on_shroomReprChanceSpinBox_valueChanged(int arg1);

    void on_bunnyReprChanceSpinBox_valueChanged(int arg1);

    void on_deerReprChanceSpinBox_valueChanged(int arg1);

    void on_foxReprChanceSpinBox_valueChanged(int arg1);

    void on_wolfReprChanceSpinBox_valueChanged(int arg1);

    void on_bunnyFovSpinBox_valueChanged(int arg1);

    void on_deerFovSpinBox_valueChanged(int arg1);

    void on_foxFovSpinBox_valueChanged(int arg1);

    void on_wolfFovSpinBox_valueChanged(int arg1);

    void on_bunnyGetHungryAtSpinBox_valueChanged(int arg1);

    void on_deerGetHungryAtSpinBox_valueChanged(int arg1);

    void on_foxGetHungryAtSpinBox_valueChanged(int arg1);

    void on_wolfGetHungryAtSpinBox_valueChanged(int arg1);

    void on_bunnyReprAgeSpinBox_valueChanged(int arg1);

    void on_deerReprAgeSpinBox_valueChanged(int arg1);

    void on_foxReprAgeSpinBox_valueChanged(int arg1);

    void on_wolfReprAgeSpinBox_valueChanged(int arg1);

    void on_deerAgeSpinBox_valueChanged(int arg1);

    void on_foxAgeSpinBox_valueChanged(int arg1);

    void on_wolfAgeSpinBox_valueChanged(int arg1);

    void on_bunnyAgeSpinBox_valueChanged(int arg1);

    void on_simSpeedhorizontalSlider_valueChanged(int value);

    void on_bunnyDeathAgeSpinBox_valueChanged(int arg1);

    void on_deerDeathAgeSpinBox_valueChanged(int arg1);

    void on_foxDeathAgeSpinBox_valueChanged(int arg1);

    void on_wolfDeathAgeSpinBox_valueChanged(int arg1);

    void on_showStatsButton_clicked();

    void on_pauseButton_clicked();

    void on_addGrassButton_clicked();

    void on_addMushroomButton_clicked();

    void on_addBunnyButton_clicked();

    void on_addDeerButton_clicked();

    void on_addFoxButton_clicked();

    void on_addWolfButton_clicked();

    void on_deerValueSpinBox_valueChanged(int arg1);

    void on_bunnyValueSpinBox_valueChanged(int arg1);

    void on_shroomValueSpinBox_valueChanged(int arg1);

    void on_grassValueSpinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    Field field;

    QGraphicsScene *scene;
    QGraphicsScene *sceneLegend;

    StatsWindow *statsWindow;

    QTimer *simulationTimer;

    QLineSeries *grassNumSeries;
    QLineSeries *mushroomNumSeries;
    QLineSeries *bunnyNumSeries;
    QLineSeries *deerNumSeries;
    QLineSeries *foxNumSeries;
    QLineSeries *wolfNumSeries;

    QChart *chart;

};
#endif // MAINWINDOW_H

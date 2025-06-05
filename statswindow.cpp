#include "statswindow.h"
#include "ui_statswindow.h"
#include "base_classes/plant.h"
#include "type/predator.h"
#include "type/prey.h"
#include <QTimer>
#include <QScrollBar>

StatsWindow::StatsWindow(QWidget *parent, Field* field)
    : QDialog(parent)
    , ui(new Ui::StatsWindow)
{
    ui->setupUi(this);
    fieldPtr = field;

    model = new QStandardItemModel(this);
    model->setColumnCount(10);
    QStringList headers;
    headers << "Entity" << "Type" << "x" << "y" << "Nutr. value" << "Age" << "Death age" << "FOV" << "Hunger" << "State";
    model->setHorizontalHeaderLabels(headers);
    ui->tableView->setModel(model);

    // set up auto-refresh timer
    refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, this, &StatsWindow::updateStats);

    // set refresh interval (e.g., 500ms = 0.5 seconds)
    refreshTimer->start(500);

    // initial stats display
    updateStats();

    // Configure table to resize with window
    ui->tableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

StatsWindow::~StatsWindow()
{
    refreshTimer->stop();
    delete ui;
    delete model;
}

void StatsWindow::updateStats()
{
    // Save scroll position
    QScrollBar *vScrollBar = ui->tableView->verticalScrollBar();
    int scrollPos = vScrollBar->value();

    // Disable updates for performance and flicker prevention
    ui->tableView->setUpdatesEnabled(false);

    // Clear existing data | clear causes flickering
    model->removeRows(0, model->rowCount());

    // Add plants
    if (showPlants)
    {
        std::vector<Plant*> plants = fieldPtr->getAllPlantsRaw();
        for (const auto& plant : plants)
        {
            QList<QStandardItem*> row;
            if (plant->getIcon()[0] == '*')  // Entity
                row << new QStandardItem("Grass");
            else if (plant->getIcon()[0] == 'o')
                row << new QStandardItem("Mushroom");
            row << new QStandardItem("Plant"); // type
            row << new QStandardItem(QString::number(plant->getX())); // x
            row << new QStandardItem(QString::number(plant->getY())); // y
            row << new QStandardItem(QString::number(plant->getValue())); // nutrition value
            row << new QStandardItem("-");                            // Age (not applicable)
            row << new QStandardItem("-");                            // Death Age (not applicable)
            row << new QStandardItem("-");                            // Fov (not applicable)
            row << new QStandardItem("-");                            // Hunger (not applicable)
            row << new QStandardItem("-");                            // State (not applicable)
            model->appendRow(row);
        }
    }

    // Add preys
    if (showPreys)
    {
        std::vector<Prey*> preys = fieldPtr->getAllPreysRaw();
        for (const auto& prey : preys)
        {
            QList<QStandardItem*> row;
            if (prey->getIcon()[0] == 'B')
                row << new QStandardItem("Bunny");                             // Entity
            else if (prey->getIcon()[0] == 'D')
                row << new QStandardItem("Deer");
            row << new QStandardItem("Prey"); // type
            row << new QStandardItem(QString::number(prey->getX()));      // x
            row << new QStandardItem(QString::number(prey->getY()));      // y
            row << new QStandardItem(QString::number(prey->getValue()));  // nutrition value
            row << new QStandardItem(QString::number(prey->getAge()));    // Age
            row << new QStandardItem(QString::number(prey->getDeathAge()));    // Death Age
            row << new QStandardItem(QString::number(prey->getFov()));    // Fov
            row << new QStandardItem(QString::number(prey->getHunger())); // Hunger
            row << new QStandardItem(prey->getStateName());               // State
            model->appendRow(row);
        }
    }

    // Add predators
    if (showPredators)
    {
        std::vector<Predator*> predators = fieldPtr->getAllPredatorsRaw();
        for (const auto& predator : predators)
        {
            QList<QStandardItem*> row;
            if (predator->getIcon()[0] == 'F')
                row << new QStandardItem("Fox");                             // Entity
            else if (predator->getIcon()[0] == 'W')
                row << new QStandardItem("Wolf");
            row << new QStandardItem("Predator"); // type
            row << new QStandardItem(QString::number(predator->getX()));      // x
            row << new QStandardItem(QString::number(predator->getY()));      // y
            row << new QStandardItem("-"); // nutrition value
            row << new QStandardItem(QString::number(predator->getAge()));    // Age
            row << new QStandardItem(QString::number(predator->getDeathAge()));// Death Age
            row << new QStandardItem(QString::number(predator->getFov()));    // Fov
            row << new QStandardItem(QString::number(predator->getHunger())); // Hunger
            row << new QStandardItem(predator->getStateName());               // State
            model->appendRow(row);
        }
    }

    // Re-enable updates
    ui->tableView->setUpdatesEnabled(true);

    // Restore scroll position
    vScrollBar->setValue(scrollPos);
}

void StatsWindow::showStats()
{
    // This method is now just for compatibility
    // The actual updating is handled by the timer
    updateStats();
}

void StatsWindow::setRefreshRate(int milliseconds)
{
    refreshTimer->setInterval(milliseconds);
}

void StatsWindow::pauseRefresh()
{
    refreshTimer->stop();
}

void StatsWindow::resumeRefresh()
{
    if (!refreshTimer->isActive()) {
        refreshTimer->start();
    }
}

void StatsWindow::on_plantsCheckBox_checkStateChanged(const Qt::CheckState &arg1)
{
    if (arg1 == Qt::Checked)
        showPlants = true;
    else
        showPlants = false;

}

void StatsWindow::on_preysCheckBox_checkStateChanged(const Qt::CheckState &arg1)
{
    if (arg1 == Qt::Checked)
        showPreys = true;
    else
        showPreys = false;
}


void StatsWindow::on_predatorsCheckBox_checkStateChanged(const Qt::CheckState &arg1)
{
    if (arg1 == Qt::Checked)
        showPredators = true;
    else
        showPredators = false;
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "statswindow.h"

#include "species/animals/wolf.h"
#include "species/animals/fox.h"
#include "species/animals/deer.h"
#include "species/animals/bunny.h"
#include "species/plants/mushroom.h"
#include "species/plants/grass.h"

// foxes die too fast

int fX = 100;
int fY = 100;

int plantsNumCap = fX *fY;
int preysNumCap = 100;
int predatorsNumCap = 100;

int gNum, mNum;
int bNum, dNum;
int fNum, wNum;

int bHunger, dHunger;
int fHunger, wHunger;

int bFov, dFov;
int fFov, wFov;

int gAge, mAge; // not used
int bAge, dAge;
int fAge, wAge;

int gDeathAge, mDeathAge; // not used
int bDeathAge, dDeathAge;
int fDeathAge, wDeathAge;

int gValue, mValue;
int bValue, dValue;
// int fValue, wValue; // not used

int gReprAge, mReprAge;
int bReprAge, dReprAge;
int fReprAge, wReprAge;

int gReprChance, mReprChance;
int bReprChance, dReprChance;
int fReprChance, wReprChance;

int bGetHungryAt, dGetHungryAt;
int fGetHungryAt, wGetHungryAt;

int simulationStepTime;

bool running = false;
bool showGrassPlot = false;
bool showMushroomPlot = false;
bool showBunnyPlot = true;
bool showDeerPlot = true;
bool showFoxPlot = true;
bool showWolfPlot = true;

QPen pen(Qt::black);
QBrush grassBrush(Qt::green);
QBrush mushroomBrush(Qt::red);
QBrush bunnyBrush(Qt::white);
QBrush deerBrush(QColor("#964B00")); // brown color
QBrush foxBrush(QColor("#FFA500")); // orange color
QBrush wolfBrush(Qt::gray);

int grassIconSize = 5;
int mushroomIconSize = 5;
int bunnyIconSize = 10;
int deerIconSize = 10;
int foxIconSize = 10;
int wolfIconSize = 10;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , field(fX, fY, plantsNumCap, preysNumCap, predatorsNumCap) // init field 100x100 with window creation
{
    ui->setupUi(this);

    scene = new QGraphicsScene(); // create scene
    ui->graphicsView->setScene(scene); // link scene and ui

    sceneLegend = new QGraphicsScene(); // create scene
    ui->legendGraphicsView->setScene(sceneLegend); // link scene and ui

    statsWindow = nullptr;

    // init series
    grassNumSeries = new QLineSeries();
    mushroomNumSeries = new QLineSeries();
    bunnyNumSeries = new QLineSeries();
    deerNumSeries = new QLineSeries();
    foxNumSeries = new QLineSeries();
    wolfNumSeries = new QLineSeries();

    // Set names
    grassNumSeries->setName("Grass");
    mushroomNumSeries->setName("Mushrooms");
    bunnyNumSeries->setName("Bunnies");
    deerNumSeries->setName("Deer");
    foxNumSeries->setName("Foxes");
    wolfNumSeries->setName("Wolves");

    // set colors
    grassNumSeries->setPen(QPen(Qt::green, 2));
    mushroomNumSeries->setPen(QPen(Qt::red, 2));
    bunnyNumSeries->setPen(QPen(Qt::black, 2));
    deerNumSeries->setPen(QPen(QColor("#964B00"), 2));
    foxNumSeries->setPen(QPen(QColor("#FFA500"), 2));
    wolfNumSeries->setPen(QPen(Qt::gray, 2));

    // init chart
    chart = new QChart();

    // add series to chart
    chart->addSeries(grassNumSeries);
    chart->addSeries(mushroomNumSeries);
    chart->addSeries(bunnyNumSeries);
    chart->addSeries(deerNumSeries);
    chart->addSeries(foxNumSeries);
    chart->addSeries(wolfNumSeries);
    chart->legend()->setAlignment(Qt::AlignLeft);
    chart->createDefaultAxes();

    // set chart for chartview
    ui->chartView->setChart(chart);

    // Initialize simulation timer
    simulationTimer = new QTimer(this);
    connect(simulationTimer, &QTimer::timeout, this, &MainWindow::runSimulationStep);

    // show legend
    sceneLegend->addEllipse(0, 15, grassIconSize, grassIconSize, pen, grassBrush);
    sceneLegend->addEllipse(0, 45, mushroomIconSize, mushroomIconSize, pen, mushroomBrush);
    sceneLegend->addEllipse(0, 75, bunnyIconSize, bunnyIconSize, pen, bunnyBrush);
    sceneLegend->addEllipse(0, 105, deerIconSize, deerIconSize, pen, deerBrush);
    sceneLegend->addEllipse(0, 135, foxIconSize, foxIconSize, pen, foxBrush);
    sceneLegend->addEllipse(0, 165, wolfIconSize, wolfIconSize, pen, wolfBrush);

    // set progress bars
    ui->grassNumProgressBar->setRange(0, plantsNumCap);
    ui->shroomNumProgressBar->setRange(0, plantsNumCap);
    ui->bunnyNumProgressBar->setRange(0, preysNumCap);
    ui->deerNumProgressBar->setRange(0, preysNumCap);
    ui->foxNumProgressBar->setRange(0, predatorsNumCap);
    ui->wolfNumProgressBar->setRange(0, predatorsNumCap);

    // show caps
    ui->capPlantsLabel->setText(QString::number(plantsNumCap));
    ui->capPreysLabel->setText(QString::number(preysNumCap));
    ui->capPredatorsLabel->setText(QString::number(predatorsNumCap));

    gNum = ui->grassNumSpinBox->value();
    mNum = ui->shroomNumSpinBox->value();
    bNum = ui->bunnyNumSpinBox->value();
    dNum = ui->deerNumSpinBox->value();
    fNum = ui->foxNumSpinBox->value();
    wNum = ui->wolfNumSpinBox->value();

    bHunger = ui->bunnyHungerSpinBox->value();
    dHunger = ui->deerHungerSpinBox->value();
    fHunger = ui->foxHungerSpinBox->value();
    wHunger = ui->wolfHungerSpinBox->value();

    bFov = ui->bunnyFovSpinBox->value();
    dFov = ui->deerFovSpinBox->value();
    fFov = ui->foxFovSpinBox->value();
    wFov = ui->wolfFovSpinBox->value();

    bAge = ui->bunnyAgeSpinBox->value();
    dAge = ui->deerAgeSpinBox->value();
    fAge = ui->foxAgeSpinBox->value();
    wAge = ui->wolfAgeSpinBox->value();

    bDeathAge = ui->bunnyDeathAgeSpinBox->value();
    dDeathAge = ui->deerDeathAgeSpinBox->value();
    fDeathAge = ui->foxDeathAgeSpinBox->value();
    wDeathAge = ui->wolfDeathAgeSpinBox->value();

    gValue = ui->grassValueSpinBox->value();
    mValue = ui->shroomValueSpinBox->value();
    bValue = ui->bunnyValueSpinBox->value();
    dValue = ui->deerValueSpinBox->value();

    gReprChance = ui->grassReprChanceSpinBox->value();
    mReprChance = ui->shroomReprChanceSpinBox->value();
    bReprChance = ui->bunnyReprChanceSpinBox->value();
    dReprChance = ui->deerReprChanceSpinBox->value();
    fReprChance = ui->foxReprChanceSpinBox->value();
    wReprChance = ui->wolfReprChanceSpinBox->value();

    bReprAge = ui->bunnyReprAgeSpinBox->value();
    dReprAge = ui->deerReprAgeSpinBox->value();
    fReprAge = ui->foxReprAgeSpinBox->value();
    wReprAge = ui->wolfReprAgeSpinBox->value();

    bGetHungryAt = ui->bunnyGetHungryAtSpinBox->value();
    dGetHungryAt = ui->deerGetHungryAtSpinBox->value();
    fGetHungryAt = ui->foxGetHungryAtSpinBox->value();
    wGetHungryAt = ui->wolfGetHungryAtSpinBox->value();

    simulationStepTime = ui->simSpeedhorizontalSlider->value();

    // update chart
    updateChartDisplay();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete sceneLegend;
    delete statsWindow;
    delete simulationTimer;

    delete grassNumSeries;
    delete mushroomNumSeries;
    delete bunnyNumSeries;
    delete deerNumSeries;
    delete foxNumSeries;
    delete wolfNumSeries;

    delete chart;
}

void MainWindow::on_runButton_clicked()
{
    running = true;

    // clear series
    grassNumSeries->clear();
    mushroomNumSeries->clear();
    bunnyNumSeries->clear();
    deerNumSeries->clear();
    foxNumSeries->clear();
    wolfNumSeries->clear();

    field.clearAll();
    scene->clear();

    field.createAnyPlants<Grass>(gValue, gReprChance, gNum); // 30 | 200
    field.createAnyPlants<Mushroom>(mValue, mReprChance, mNum); // 10 | 40
    field.createAnyPreys<Bunny>(bAge, bDeathAge, 10, bFov, bHunger, bValue, bReprAge, bReprChance,  bGetHungryAt, bNum); // 5 | 20
    field.createAnyPreys<Deer>(dAge, dDeathAge,  10, dFov, dHunger, dValue, dReprAge, dReprChance, dGetHungryAt, dNum); // 5 | 20
    field.createAnyPredators<Fox>(fAge, fDeathAge, 10, fFov, fHunger, 1, fReprAge, fReprChance, fGetHungryAt, fNum); // 5 | 10
    field.createAnyPredators<Wolf>(wAge, wDeathAge, 10, wFov, wHunger, 1, wReprAge, wReprChance, wGetHungryAt, wNum); // 5 | 10

    // enable add entities buttons
    ui->addGrassButton->setEnabled(true);
    ui->addMushroomButton->setEnabled(true);
    ui->addBunnyButton->setEnabled(true);
    ui->addDeerButton->setEnabled(true);
    ui->addFoxButton->setEnabled(true);
    ui->addWolfButton->setEnabled(true);

    // rename pause button if sim was resatarted after pause
    ui->pauseButton->setText("Pause simulation");

    // Start the timer instead of the while loop
    simulationTimer->start(simulationStepTime);
}

void MainWindow::runSimulationStep()
{
    scene->clear();

    std::vector<Plant*> plantsCoords = field.getAllPlantsRaw();
    std::vector<Prey*> preysCoords = field.getAllPreysRaw();
    std::vector<Predator*> predatorsCoords = field.getAllPredatorsRaw();

    // set progress bars
    ui->grassNumProgressBar->setRange(0, plantsNumCap);
    ui->shroomNumProgressBar->setRange(0, plantsNumCap);
    ui->bunnyNumProgressBar->setRange(0, preysNumCap);
    ui->deerNumProgressBar->setRange(0, preysNumCap);
    ui->foxNumProgressBar->setRange(0, predatorsNumCap);
    ui->wolfNumProgressBar->setRange(0, predatorsNumCap);

    int currentGrassNum = 0;
    int currentMushroomNum = 0;
    int currentBunnyNum = 0;
    int currentDeerNum = 0;
    int currentFoxNum = 0;
    int currentWolfNum = 0;

    int scaleFactor = 5;

    for (const auto& plant : plantsCoords)
    {
        if (plant->getIcon()[0] == '*')
        {
            scene->addEllipse(plant->getX() * scaleFactor, plant->getY() * scaleFactor, grassIconSize, grassIconSize, pen, grassBrush);
            currentGrassNum++;
        }

        if (plant->getIcon()[0] == 'o')
        {
            scene->addEllipse(plant->getX() * scaleFactor, plant->getY() * scaleFactor, mushroomIconSize, mushroomIconSize, pen, mushroomBrush);
            currentMushroomNum++;
        }
    }

    for (const auto& prey : preysCoords)
    {
        if (prey->getIcon()[0] == 'B')
        {
            scene->addEllipse(prey->getX() * scaleFactor, prey->getY() * scaleFactor, bunnyIconSize, bunnyIconSize, pen, bunnyBrush);
            currentBunnyNum++;
        }

        if (prey->getIcon()[0] == 'D')
        {
            scene->addEllipse(prey->getX() * scaleFactor, prey->getY() * scaleFactor, deerIconSize, deerIconSize, pen, deerBrush);
            currentDeerNum++;
        }
    }

    for (const auto& predator : predatorsCoords)
    {
        if (predator->getIcon()[0] == 'F')
        {
            scene->addEllipse(predator->getX() * scaleFactor, predator->getY() * scaleFactor, foxIconSize, foxIconSize, pen, foxBrush);
            currentFoxNum++;
        }

        if (predator->getIcon()[0] == 'W')
        {
            scene->addEllipse(predator->getX() * scaleFactor, predator->getY() * scaleFactor, wolfIconSize, wolfIconSize, pen, wolfBrush);
            currentWolfNum++;
        }
    }

    // update progress bars with current counts
    ui->grassNumProgressBar->setValue(currentGrassNum);
    ui->shroomNumProgressBar->setValue(currentMushroomNum);
    ui->bunnyNumProgressBar->setValue(currentBunnyNum);
    ui->deerNumProgressBar->setValue(currentDeerNum);
    ui->foxNumProgressBar->setValue(currentFoxNum);
    ui->wolfNumProgressBar->setValue(currentWolfNum);

    // add entities number to series
    if (showGrassPlot) grassNumSeries->append(field.getStepNum(), currentGrassNum);
    if (showMushroomPlot) mushroomNumSeries->append(field.getStepNum(), currentMushroomNum);
    if (showBunnyPlot) bunnyNumSeries->append(field.getStepNum(), currentBunnyNum);
    if (showDeerPlot) deerNumSeries->append(field.getStepNum(), currentDeerNum);
    if (showFoxPlot) foxNumSeries->append(field.getStepNum(), currentFoxNum);
    if (showWolfPlot) wolfNumSeries->append(field.getStepNum(), currentWolfNum);

    updateChartDisplay();

    field.runSimulation();
    ui->simStepNumLabel->setText(QString::number(field.getStepNum()));

    // Update timer interval if speed changed
    if (simulationStepTime < 1) simulationStepTime = 1; // Ensure minimum delay
    simulationTimer->setInterval(simulationStepTime);
}

void MainWindow::on_pauseButton_clicked()
{
    if (simulationTimer->isActive() && running)
    {
        simulationTimer->stop();
        ui->pauseButton->setText("Continue");

        // disable add entities buttons
        ui->addGrassButton->setEnabled(false);
        ui->addMushroomButton->setEnabled(false);
        ui->addBunnyButton->setEnabled(false);
        ui->addDeerButton->setEnabled(false);
        ui->addFoxButton->setEnabled(false);
        ui->addWolfButton->setEnabled(false);
    }
    else if (!simulationTimer->isActive() && running)
    {
        simulationTimer->start(simulationStepTime);
        ui->pauseButton->setText("Pause simulation");

        // enable add entities buttons
        ui->addGrassButton->setEnabled(true);
        ui->addMushroomButton->setEnabled(true);
        ui->addBunnyButton->setEnabled(true);
        ui->addDeerButton->setEnabled(true);
        ui->addFoxButton->setEnabled(true);
        ui->addWolfButton->setEnabled(true);
    }
}

void MainWindow::on_finishButton_clicked()
{
    running = false;

    simulationTimer->stop();
    field.clearAll();
    scene->clear();

    // reset step count
    ui->simStepNumLabel->setText("0");

    // reset progress bars
    ui->grassNumProgressBar->setValue(0);
    ui->shroomNumProgressBar->setValue(0);
    ui->bunnyNumProgressBar->setValue(0);
    ui->deerNumProgressBar->setValue(0);
    ui->foxNumProgressBar->setValue(0);
    ui->wolfNumProgressBar->setValue(0);

    // disable add entities buttons
    ui->addGrassButton->setEnabled(false);
    ui->addMushroomButton->setEnabled(false);
    ui->addBunnyButton->setEnabled(false);
    ui->addDeerButton->setEnabled(false);
    ui->addFoxButton->setEnabled(false);
    ui->addWolfButton->setEnabled(false);

    // clear series
    grassNumSeries->clear();
    mushroomNumSeries->clear();
    bunnyNumSeries->clear();
    deerNumSeries->clear();
    foxNumSeries->clear();
    wolfNumSeries->clear();
}

void MainWindow::updateChartDisplay()
{
    if (!chart) return;

    // Get the current step number to set proper axis ranges
    int currentStep = field.getStepNum();

    // Only recreate axes if this is the first update or if we need to expand the range significantly
    if (chart->axes().isEmpty() || currentStep % 20 == 0) // Update axes every 20 steps
    {
        chart->createDefaultAxes();

        // set reasonable ranges for X
        if (!chart->axes(Qt::Horizontal).isEmpty())
        {
            chart->axes(Qt::Horizontal).first()->setRange(0, qMax(100, currentStep + 20));
        }

        // set reasonable ranges for Y
        if (!chart->axes(Qt::Vertical).isEmpty())
        {
            // Find the maximum value among all series to set Y-axis range
            int maxValue = 0;

            // Check all series for their maximum values
            for (auto series : chart->series())
            {
                QLineSeries* lineSeries = qobject_cast<QLineSeries*>(series);
                if (lineSeries && !lineSeries->points().isEmpty())
                {
                    for (const QPointF& point : lineSeries->points())
                    {
                        maxValue = qMax(maxValue, (int)point.y());
                    }
                }
            }

            chart->axes(Qt::Vertical).first()->setRange(0, qMax(100, maxValue + 20));
        }
    }

    ui->chartView->repaint();
}

void MainWindow::on_grassNumSpinBox_valueChanged(int arg1){gNum = arg1;}
void MainWindow::on_shroomNumSpinBox_valueChanged(int arg1){mNum = arg1;}
void MainWindow::on_bunnyNumSpinBox_valueChanged(int arg1){bNum = arg1;}
void MainWindow::on_deerNumSpinBox_valueChanged(int arg1){dNum = arg1;}
void MainWindow::on_foxNumSpinBox_valueChanged(int arg1){fNum = arg1;}
void MainWindow::on_wolfNumSpinBox_valueChanged(int arg1){wNum = arg1;}
void MainWindow::on_bunnyHungerSpinBox_valueChanged(int arg1){bHunger = arg1;}
void MainWindow::on_deerHungerSpinBox_valueChanged(int arg1){dHunger = arg1;}
void MainWindow::on_foxHungerSpinBox_valueChanged(int arg1){fHunger = arg1;}
void MainWindow::on_wolfHungerSpinBox_valueChanged(int arg1){wHunger = arg1;}
void MainWindow::on_grassReprChanceSpinBox_valueChanged(int arg1){gReprChance = arg1;}
void MainWindow::on_shroomReprChanceSpinBox_valueChanged(int arg1){mReprChance = arg1;}
void MainWindow::on_bunnyReprChanceSpinBox_valueChanged(int arg1){bReprChance = arg1;}
void MainWindow::on_deerReprChanceSpinBox_valueChanged(int arg1){dReprChance = arg1;}
void MainWindow::on_foxReprChanceSpinBox_valueChanged(int arg1){fReprChance = arg1;}
void MainWindow::on_wolfReprChanceSpinBox_valueChanged(int arg1){wReprChance = arg1;}
void MainWindow::on_bunnyFovSpinBox_valueChanged(int arg1){bFov = arg1;}
void MainWindow::on_deerFovSpinBox_valueChanged(int arg1){dFov = arg1;}
void MainWindow::on_foxFovSpinBox_valueChanged(int arg1){fFov = arg1;}
void MainWindow::on_wolfFovSpinBox_valueChanged(int arg1){wFov = arg1;}
void MainWindow::on_bunnyGetHungryAtSpinBox_valueChanged(int arg1){bGetHungryAt = arg1;}
void MainWindow::on_deerGetHungryAtSpinBox_valueChanged(int arg1){dGetHungryAt = arg1;}
void MainWindow::on_foxGetHungryAtSpinBox_valueChanged(int arg1){fGetHungryAt = arg1;}
void MainWindow::on_wolfGetHungryAtSpinBox_valueChanged(int arg1){wGetHungryAt = arg1;}
void MainWindow::on_bunnyReprAgeSpinBox_valueChanged(int arg1){bReprAge = arg1;}
void MainWindow::on_deerReprAgeSpinBox_valueChanged(int arg1){dReprAge = arg1;}
void MainWindow::on_foxReprAgeSpinBox_valueChanged(int arg1){fReprAge = arg1;}
void MainWindow::on_wolfReprAgeSpinBox_valueChanged(int arg1){wReprAge = arg1;}
void MainWindow::on_bunnyAgeSpinBox_valueChanged(int arg1){bAge = arg1;}
void MainWindow::on_deerAgeSpinBox_valueChanged(int arg1){dAge = arg1;}
void MainWindow::on_foxAgeSpinBox_valueChanged(int arg1){fAge = arg1;}
void MainWindow::on_wolfAgeSpinBox_valueChanged(int arg1){wAge = arg1;}
void MainWindow::on_deerValueSpinBox_valueChanged(int arg1){dValue = arg1;}
void MainWindow::on_bunnyValueSpinBox_valueChanged(int arg1){bValue = arg1;}
void MainWindow::on_shroomValueSpinBox_valueChanged(int arg1){mValue = arg1;}
void MainWindow::on_grassValueSpinBox_valueChanged(int arg1){gValue = arg1;}


void MainWindow::on_simSpeedhorizontalSlider_valueChanged(int value)
{
    simulationStepTime = value;
    // Update timer interval immediately if simulation is running
    if (simulationTimer->isActive()) {
        int delayMs = 200 / (float)simulationStepTime;
        if (delayMs < 1) delayMs = 1;
        simulationTimer->setInterval(delayMs);
    }
}

void MainWindow::on_bunnyDeathAgeSpinBox_valueChanged(int arg1)
{
    bDeathAge = arg1;
}

void MainWindow::on_deerDeathAgeSpinBox_valueChanged(int arg1)
{
    dDeathAge = arg1;
}

void MainWindow::on_foxDeathAgeSpinBox_valueChanged(int arg1)
{
    fDeathAge = arg1;
}

void MainWindow::on_wolfDeathAgeSpinBox_valueChanged(int arg1)
{
    wDeathAge = arg1;
}

void MainWindow::on_showStatsButton_clicked()
{
    if (statsWindow)
    {
        statsWindow->close();        // close the window
    }
    else
    {
        statsWindow = new StatsWindow(this, &field);
        statsWindow->setAttribute(Qt::WA_DeleteOnClose);

        // Track destruction to reset pointer
        connect(statsWindow, &QObject::destroyed, this, [this]() {
            statsWindow = nullptr;
        });

        statsWindow->show();
    }
}


void MainWindow::on_addGrassButton_clicked()
{
    field.createAnyPlants<Grass>(gValue, gReprChance, 1);
}


void MainWindow::on_addMushroomButton_clicked()
{
    field.createAnyPlants<Mushroom>(mValue, mReprChance, 1);
}


void MainWindow::on_addBunnyButton_clicked()
{
    field.createAnyPreys<Bunny>(bAge, bDeathAge, 10, bFov, bHunger, bValue, bReprAge, bReprChance,  bGetHungryAt, 1);
}


void MainWindow::on_addDeerButton_clicked()
{
    field.createAnyPreys<Deer>(dAge, dDeathAge,  10, dFov, dHunger, dValue, dReprAge, dReprChance, dGetHungryAt, 1);
}


void MainWindow::on_addFoxButton_clicked()
{
    field.createAnyPredators<Fox>(fAge, fDeathAge, 10, fFov, fHunger, 1, fReprAge, fReprChance, fGetHungryAt, 1);
}


void MainWindow::on_addWolfButton_clicked()
{
    field.createAnyPredators<Wolf>(wAge, wDeathAge, 10, wFov, wHunger, 1, wReprAge, wReprChance, wGetHungryAt, 1);
}



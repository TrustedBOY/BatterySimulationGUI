#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QFormLayout>
#include <QComboBox>
#include <QDebug>
#include <QDoubleSpinBox>

/**
 * @brief Constructor for MainWindow
 * @param parent The parent widget
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Initialize Logic
    pack = new BatteryPack(BatteryPack::SERIES);

    // --- UI Setup --- //
    QWidget *centralWidget = new QWidget;
    setCentralWidget(centralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Left Panel: Controls
    QVBoxLayout *controlsLayout = new QVBoxLayout();

    // 1. Add Battery Group
    QGroupBox *addGroup = new QGroupBox("Add Battery");
    QFormLayout *addLayout = new QFormLayout();
    voltageInput = new QLineEdit("3.7");
    capacityInput = new QLineEdit("2000");
    chargeInput = new QLineEdit("2000");
    QPushButton *btnAdd = new QPushButton("Add Battery");
    addLayout->addRow("Voltage:", voltageInput);
    addLayout->addRow("Capacity:", capacityInput);
    addLayout->addRow("Initial Charge:", chargeInput);
    addLayout->addRow(btnAdd);
    addGroup->setLayout(addLayout);

    // 2. Pack Configuration Group
    QGroupBox *configGroup = new QGroupBox("Pack Configuration");
    QVBoxLayout *configLayout = new QVBoxLayout();
    typeCombo = new QComboBox();
    typeCombo->addItem("Series (Vertical)");
    typeCombo->addItem("Parallel (Horizontal)");
    configLayout->addWidget(new QLabel("Connection Type:"));
    configLayout->addWidget(typeCombo);
    configGroup->setLayout(configLayout);

    // 3. Simulation Group
    QGroupBox *simGroup = new QGroupBox("Simulation");
    QVBoxLayout *simMainLayout = new QVBoxLayout();

    // Add the Hour Input
    QHBoxLayout *inputRow = new QHBoxLayout();
    inputRow->addWidget(new QLabel("Hours:"));
    hoursInput = new QDoubleSpinBox();
    hoursInput->setRange(0.1, 100.0);
    hoursInput->setValue(1.0); // Default value: 1 hour
    hoursInput->setSuffix(" hrs");
    inputRow->addWidget(hoursInput);

    // Add the Buttons
    QHBoxLayout *simButtonLayout = new QHBoxLayout();
    QPushButton *btnUse = new QPushButton("Use");
    QPushButton *btnCharge = new QPushButton("Recharge");
    simButtonLayout->addWidget(btnUse);
    simButtonLayout->addWidget(btnCharge);

    simMainLayout->addLayout(inputRow);
    simMainLayout->addLayout(simButtonLayout);
    simGroup->setLayout(simMainLayout);

    // 4. Stats Label
    statusLabel = new QLabel("Stats will appear here");
    statusLabel->setStyleSheet("font-weight: bold; margin-top: 10px;");

    controlsLayout->addWidget(addGroup);
    controlsLayout->addWidget(configGroup);
    controlsLayout->addWidget(simGroup);
    controlsLayout->addWidget(statusLabel);
    controlsLayout->addStretch();

    // Right Panel: Visualization
    canvas = new BatteryCanvas();
    canvas->setBatteryPack(pack);

    // Add to main layout
    mainLayout->addLayout(controlsLayout, 1);
    mainLayout->addWidget(canvas, 2);

    // --- Connections --- //
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::addBattery);
    connect(typeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(changePackType(int)));
    connect(btnUse, &QPushButton::clicked, this, &MainWindow::simulateUse);
    connect(btnCharge, &QPushButton::clicked, this, &MainWindow::simulateRecharge);

    // Initial update
    updateLabels();
    resize(900, 600);
}

MainWindow::~MainWindow()
{
    delete pack;
    // Clean up the batteries we created
    for (Battery *b : allBatteries)
    {
        delete b;
    }
}

/**
 * @brief Slot to handle adding a new battery
 */
void MainWindow::addBattery()
{
    bool ok1, ok2, ok3;
    double v = voltageInput->text().toDouble(&ok1);
    double c = capacityInput->text().toDouble(&ok2);
    double i = chargeInput->text().toDouble(&ok3);

    if (ok1 && ok2 && ok3)
    {
        Battery *b = new Battery(v, c, i);
        allBatteries.push_back(b); // Store to delete later
        pack->add(b);              // Add to current pack logic

        canvas->update(); // Redraw
        updateLabels();   // Update text stats
    }
}

/**
 * @brief Slot to handle changing the battery pack type
 * @param index The new index selected
 */
void MainWindow::changePackType(int index)
{
    // Because BatteryPack doesn't have a setType() method in the header provided,
    // we must recreate the pack and move the batteries over.

    BatteryPack::ConnectionType newType = (index == 0) ? BatteryPack::SERIES : BatteryPack::PARALLEL;

    // 1. Save the batteries from the old pack
    std::vector<Battery *> cells = pack->getCells();

    // 2. Delete old pack
    delete pack;

    // 3. Create new pack
    pack = new BatteryPack(newType);

    // 4. Re-add the batteries
    for (Battery *b : cells)
    {
        pack->add(b);
    }

    // 5. Update the canvas to point to the new pack
    canvas->setBatteryPack(pack);
    canvas->update();
    updateLabels();
}

/**
 * @brief Slot to simulate battery usage
 */
void MainWindow::simulateUse()
{
    double hours = hoursInput->value(); // Get the dynamic value from UI
    pack->use(hours);
    canvas->update();
    updateLabels();
}

/**
 * @brief Slot to simulate battery recharge
 */
void MainWindow::simulateRecharge()
{
    double hours = hoursInput->value(); // Get the dynamic value from UI
    pack->recharge(hours);
    canvas->update();
    updateLabels();
}

/**
 * @brief Updates the labels in the UI
 */
void MainWindow::updateLabels()
{
    QString text = QString("Pack Voltage: %1 V\nPack Capacity: %2\nPack Charge: %3")
                       .arg(pack->getVoltage())
                       .arg(pack->getCapacity())
                       .arg(pack->getCharge());
    statusLabel->setText(text);
}
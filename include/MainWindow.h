#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "BatteryPack.h"
#include "BatteryCanvas.h"

class QLineEdit;
class QLabel;
class QComboBox;
class QDoubleSpinBox;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for MainWindow
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for MainWindow
     */
    ~MainWindow();

private slots:

    /**
     * @brief Slot to handle adding a new battery
     */
    void addBattery();
    
    /**
     * @brief Slot to handle changing the battery pack type
     */
    void changePackType(int index);
    
    /**
     * @brief Slot to simulate battery usage
     */
    void simulateUse();
    
    /**
     * @brief Slot to simulate battery recharge
     */
    void simulateRecharge();

private:
    /**
     * @brief Updates the labels in the UI
     */
    void updateLabels();

    BatteryPack *pack;
    std::vector<Battery *> allBatteries;

    // UI Components //
    BatteryCanvas *canvas;
    QLineEdit *voltageInput;
    QLineEdit *capacityInput;
    QLineEdit *chargeInput;
    QDoubleSpinBox* hoursInput;
    QComboBox *typeCombo;
    QLabel *statusLabel;
};

#endif
#ifndef BATTERYCANVAS_H
#define BATTERYCANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include "BatteryPack.h"

class BatteryCanvas : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for BatteryCanvas
     */
    explicit BatteryCanvas(QWidget *parent = nullptr);
    /**
     * @brief Sets the BatteryPack to visualize
     */
    void setBatteryPack(BatteryPack *pack);

protected:
    /**
     * @brief Custom paint event to draw batteries
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Handle mouse clicks to remove batteries
     */
    void mousePressEvent(QMouseEvent *event) override;

private:
    /**
     * @brief The BatteryPack being visualized
     */
    BatteryPack *myPack = nullptr;

    /**
     * @brief Helper to calculate where a specific battery is drawn
     */
    QRect getBatteryRect(int index, int startX, int startY) const;
};

#endif
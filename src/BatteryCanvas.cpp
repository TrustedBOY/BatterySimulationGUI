#include "BatteryCanvas.h"
#include <QPainter>
#include <QDebug>

// Constants for drawing //
const int B_WIDTH_P = 50;
const int B_HEIGHT_P = 100;
const int B_WIDTH_S = 60;
const int B_HEIGHT_S = 30;

// These will be set dynamically based on pack type //
int B_WIDTH = 60;
int B_HEIGHT = 100;

const int SPACING = 20;
const int START_X = 50;
const int START_Y = 50;

BatteryCanvas::BatteryCanvas(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(400, 300);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::gray);
    setAutoFillBackground(true);
    setPalette(pal);
}

/**
 * @brief Sets the BatteryPack to visualize
 * @param pack The BatteryPack to visualize
 */
void BatteryCanvas::setBatteryPack(BatteryPack *pack)
{
    myPack = pack;
    update();
}

/**
 * @brief Calculates the rectangle for a battery based on its index and pack type
 * @param index The index of the battery in the pack
 * @param startX The starting X position
 * @param startY The starting Y position
 * @return QRect representing the battery's position and size
 */
QRect BatteryCanvas::getBatteryRect(int index, int startX, int startY) const
{
    if (!myPack)
        return QRect();

    if (myPack->getConnectionType() == BatteryPack::SERIES)
    {
        // Series: Index increases Y
        return QRect(startX, startY + (index * (B_HEIGHT_S + SPACING)), B_WIDTH_S, B_HEIGHT_S);
    }
    else
    {
        // Parallel: Index increases X
        return QRect(startX + (index * (B_WIDTH_S + SPACING)), startY, B_WIDTH_P, B_HEIGHT_P);
    }
}

/**
 * @brief Custom paint event to draw batteries
 * @param event The paint event
 */
void BatteryCanvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (!myPack)
        return;

    std::vector<Battery *> &cells = myPack->getCells();
    if (cells.empty())
    {
        painter.drawText(rect(), Qt::AlignCenter, "No Batteries - You can add Batteries using the left window!");
        return;
    }

    for (size_t i = 0; i < cells.size(); ++i)
    {
        B_HEIGHT = (myPack->getConnectionType() == BatteryPack::SERIES) ? B_HEIGHT_S : B_HEIGHT_P;
        B_WIDTH = (myPack->getConnectionType() == BatteryPack::SERIES) ? B_WIDTH_S : B_WIDTH_P;

        Battery *b = cells[i];

        // Get the position for this specific battery
        QRect bRect = getBatteryRect(i, START_X, START_Y);

        // --- Draw 1. Battery Body --- //
        painter.setPen(QPen(Qt::black, 2));
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(bRect);

        // Positive Terminal
        painter.setBrush(Qt::black);
        painter.drawRect(bRect.x() + (B_WIDTH / 4), bRect.y() - 6, (B_WIDTH / 2), 6);

        // --- Draw 2. Charge (Color) ---
        double pct = b->getPercent();
        QColor color = (pct > 50) ? Qt::green : (pct > 20 ? QColor("orange") : Qt::red);

        int fillHeight = static_cast<int>(B_HEIGHT * (pct / 100.0));
        // Clamp to avoid drawing errors
        if (fillHeight > B_HEIGHT)
            fillHeight = B_HEIGHT;
        if (fillHeight < 0)
            fillHeight = 0;

        QRect fillRect(bRect.x() + 1, bRect.y() + (B_HEIGHT - fillHeight), B_WIDTH - 2, fillHeight);
        painter.setBrush(color);
        painter.setPen(Qt::NoPen);
        painter.drawRect(fillRect);

        // ---  Draw 3. Text  ---
        painter.setPen(Qt::black);
        QString vText = QString::number(b->getVoltage()) + "V";
        QString pText = QString::number(pct, 'f', 0) + "%";

        if (myPack->getConnectionType() == BatteryPack::SERIES)
        {
            // SERIES MODE: Draw text to the RIGHT of the battery
            // This prevents it from being covered by the battery below
            painter.drawText(bRect.right() + 10, bRect.center().y() - 5, vText);
            painter.drawText(bRect.right() + 10, bRect.center().y() + 10, pText);
        }
        else
        {
            // PARALLEL MODE: Draw text UNDER the battery
            painter.drawText(bRect.x(), bRect.bottom() + 15, B_WIDTH, 15, Qt::AlignCenter, vText);
            painter.drawText(bRect.center().x() - 15, bRect.center().y(), pText);
        }
    }
}

/**
 * @brief Handle mouse clicks to remove batteries
 * @param event The mouse event
 */
void BatteryCanvas::mousePressEvent(QMouseEvent *event)
{
    if (!myPack)
        return;

    // Iterate through all batteries to see if one was clicked
    std::vector<Battery *> &cells = myPack->getCells();

    // We loop backwards so if elements overlap (unlikely here), top one catches click
    for (int i = cells.size() - 1; i >= 0; --i)
    {
        QRect rect = getBatteryRect(i, START_X, START_Y);

        if (rect.contains(event->pos()))
        {
            // Click detected! Remove the battery.
            myPack->deleteBattery(i);

            // Trigger a redraw immediately
            update();
            break;
        }
    }
}
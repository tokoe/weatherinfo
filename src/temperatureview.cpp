/*
    This file is part of WeatherInfo.

    Copyright (c) 2009 SW09-HTW-Team

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
    USA.
*/

#include "temperatureview.h"

#include "weathermodel.h"

#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QPainter>

TemperatureView::TemperatureView(QWidget *parent)
    : QWidget(parent), mModel(0), mCurrentLocation(0)
{
    setWindowTitle("Temperature View");

    QGridLayout *layout = new QGridLayout(this);
    mLocations = new QComboBox;

    layout->addWidget(mLocations, 1, 1);
    layout->setRowStretch(0, 1);
    layout->setColumnStretch(0, 1);

    connect(mLocations, SIGNAL(currentIndexChanged(int)), SLOT(setCurrentLocation(int)));

    resize(800, 400);
}

TemperatureView::~TemperatureView()
{
}

void TemperatureView::setModel(WeatherModel *model)
{
    mModel = model;
    connect(mModel, SIGNAL(layoutChanged()), SLOT(layoutChanged()));
    connect(mModel, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
            SLOT(dataChanged(const QModelIndex&, const QModelIndex&)));

    layoutChanged();
}

void TemperatureView::setCurrentLocation(int location)
{
    mCurrentLocation = location;
    update();
}

void TemperatureView::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    const int leftOffset = 20;
    const int topOffset = 20;

    p.drawLine(leftOffset, topOffset, leftOffset, height() - topOffset);
    p.drawLine(leftOffset, height() - topOffset, width() - leftOffset, height() - topOffset);

    if (!mModel)
      return;

    int minTemp = 1000;
    int maxTemp = -1000;
    for (int column = 0; column < mModel->columnCount(); ++column) {
        const QModelIndex index = mModel->index(mCurrentLocation, column);
        const int temperature = index.data(WeatherModel::TemperatureRole).toInt();
        minTemp = qMin(minTemp, temperature);
        maxTemp = qMax(maxTemp, temperature);
    }

    const int tempStep = (height() - 2*topOffset)/((maxTemp - minTemp) == 0 ? 1 : (maxTemp - minTemp));
    for (int i = 0; i <= (maxTemp-minTemp); i++) {
        p.drawLine(leftOffset/2, topOffset + i*tempStep, leftOffset, topOffset + i*tempStep);
        p.drawText(leftOffset/8, 13 + topOffset + i*tempStep, QString::number(maxTemp - i));
    }
    p.drawText(leftOffset/2, topOffset - 5, QString("°C"));

    const int dayStep = (width() - 2*leftOffset)/5;
    int previousX = 0;
    int previousY = 0;

    QTextOption option;
    option.setAlignment(Qt::AlignCenter);

    for (int column = 0; column < mModel->columnCount(); ++column) {
        const QModelIndex index = mModel->index(mCurrentLocation, column);
        const int temperature = index.data(WeatherModel::TemperatureRole).toInt();

        const int x = (leftOffset + column*dayStep);
        const int y = topOffset + (maxTemp - temperature)*tempStep;

        p.drawText(QRectF(x, 0, dayStep, topOffset), index.data(WeatherModel::WeekdayRole).toString(), option);

        if (column == 0)
            p.drawLine(x, y, x + dayStep/2, y);
        else
            p.drawLine(previousX + dayStep/2, previousY, x + dayStep/2, y);

        if (column == 4)
            p.drawLine(x + dayStep/2, y, x + dayStep, y);

        previousX = x;
        previousY = y;
    }

    QWidget::paintEvent(event);
}

void TemperatureView::layoutChanged()
{
    mLocations->clear();

    for (int row = 0; row < mModel->rowCount(); ++row)
        mLocations->addItem(mModel->headerData(row, Qt::Vertical, Qt::DisplayRole).toString());

    update();
}

void TemperatureView::dataChanged(const QModelIndex&, const QModelIndex&)
{
    update();
}

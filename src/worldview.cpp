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

#include "worldview.h"

#include "weathermodel.h"

#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QIcon>
#include <QtGui/QPainter>

WorldView::WorldView(QWidget *parent)
    : QWidget(parent), mModel(0), mCurrentDay(0)
{
    setWindowTitle("World View");

    mMap = QImage(":world.jpg");

    QGridLayout *layout = new QGridLayout(this);
    mWeekdays = new QComboBox;

    layout->addWidget(mWeekdays, 1, 1);
    layout->setRowStretch(0, 1);
    layout->setColumnStretch(0, 1);

    connect(mWeekdays, SIGNAL(currentIndexChanged(int)), SLOT(setCurrentDay(int)));

    resize(800, 400);
}

WorldView::~WorldView()
{
}

void WorldView::setModel(WeatherModel *model)
{
    mModel = model;
    connect(mModel, SIGNAL(layoutChanged()), SLOT(layoutChanged()));
    connect(mModel, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
            SLOT(dataChanged(const QModelIndex&, const QModelIndex&)));

    layoutChanged();
}

void WorldView::setCurrentDay(int day)
{
    mCurrentDay = day;
    update();
}

void WorldView::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawImage(QPoint(0, 0), mMap);

    if (!mModel)
      return;

    for (int row = 0; row < mModel->rowCount(); ++row) {
        const QModelIndex index = mModel->index(row, mCurrentDay);
        const QString name = index.data(WeatherModel::NameRole).toString();
        const double latitude = index.data(WeatherModel::LatitudeRole).toDouble();
        const double longitude = index.data(WeatherModel::LongitudeRole).toDouble();
        const QIcon icon = index.data(Qt::DecorationRole).value<QIcon>();
        const QPixmap pm = icon.pixmap(25, 25);

        double latMid = height() / 2;
        double longMid = width() / 2;

        double latOffset = (latitude * latMid) / 90;
        double longOffset = (longitude * longMid) / 180;

        int x = (int)(longMid + longOffset);
        int y = (int)(latMid - latOffset);
        p.drawPixmap(x - pm.width()/2, y - pm.height()/2, pm);
    }

    QWidget::paintEvent(event);
}

void WorldView::layoutChanged()
{
    mWeekdays->clear();

    for (int column = 0; column < mModel->columnCount(); ++column)
        mWeekdays->addItem(mModel->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString());

    update();
}

void WorldView::dataChanged(const QModelIndex&, const QModelIndex&)
{
    update();
}

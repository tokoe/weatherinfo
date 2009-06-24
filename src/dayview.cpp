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

#include "dayview.h"

#include "weathermodel.h"

#include <QtCore/QUrl>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QTextEdit>

DayView::DayView(QWidget *parent)
    : QWidget(parent), mModel(0)
{
    setWindowTitle("Day View");

    QGridLayout *layout = new QGridLayout(this);

    QLabel *label = new QLabel("Location:");
    layout->addWidget(label, 0, 0);

    mLocation = new QComboBox;
    layout->addWidget(mLocation, 0, 1);

    label = new QLabel("Day:");
    layout->addWidget(label, 0, 2);

    mCurrentDay = new QComboBox;
    layout->addWidget(mCurrentDay, 0, 3);

    mView = new QTextEdit;
    mView->setReadOnly(true);
    layout->addWidget(mView, 1, 0, 1, 4);

    connect(mLocation, SIGNAL(currentIndexChanged(int)), SLOT(updateView()));
    connect(mCurrentDay, SIGNAL(currentIndexChanged(int)), SLOT(updateView()));
}

DayView::~DayView()
{
}

void DayView::setModel(WeatherModel *model)
{
    mModel = model;
    connect(mModel, SIGNAL(layoutChanged()), SLOT(layoutChanged()));
    connect(mModel, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
            SLOT(dataChanged(const QModelIndex&, const QModelIndex&)));

    layoutChanged();
}

void DayView::layoutChanged()
{
    updateLocations();
    updateDays();
    updateView();
}

void DayView::dataChanged(const QModelIndex&, const QModelIndex&)
{
    updateView();
}

void DayView::updateView()
{
    if (!mModel)
        return;

    const int row = mLocation->currentIndex();
    const int column = mCurrentDay->currentIndex();

    const QModelIndex index = mModel->index(row, column);
    if (!index.isValid()) {
        mView->clear();
        return;
    }

    const QString name = index.data(WeatherModel::NameRole).toString();
    const QString temperature = index.data(Qt::DisplayRole).toString();
    const QIcon condition = index.data(Qt::DecorationRole).value<QIcon>();
    const QPixmap pm = condition.pixmap(32, 32);
    const QString windDirection = index.data(WeatherModel::WindDirectionRole).toString();
    const QString windSpeed = index.data(WeatherModel::WindSpeedRole).toString();

    QString html = QString("<html>"
                           " <body>"
                           " <center>"
                           "  <table width=\"100%\">"
                           "   <tr>"
                           "   <td align=\"right\" width=\"50%\"><img src=\"weather_cond\"></td><td><b>%1</b></td>"
                           "   </tr>"
                           "   <tr>"
                           "   <td colspan=\"2\">&nbsp;</td>"
                           "   </tr>"
                           "   <tr>"
                           "   <td align=\"right\">Temperature:</td><td>%2</td>"
                           "   </tr>"
                           "   <tr>"
                           "   <td align=\"right\">Wind direction:</td><td>%3</td>"
                           "   </tr>"
                           "   <tr>"
                           "   <td align=\"right\">Wind speed:</td><td>%4 mph</td>"
                           "   </tr>"
                           "  </table>"
                           " </center>"
                           " </body>"
                           "</html>")
                          .arg(name)
                          .arg(temperature)
                          .arg(windDirection)
                          .arg(windSpeed);

    mView->document()->addResource( QTextDocument::ImageResource, QUrl("weather_cond"), pm );
    mView->setHtml(html);
}

void DayView::updateLocations()
{
    mLocation->clear();

    if (!mModel)
        return;

    for (int row = 0; row < mModel->rowCount(); ++row)
        mLocation->addItem(mModel->headerData(row, Qt::Vertical, Qt::DisplayRole).toString());
}

void DayView::updateDays()
{
    mCurrentDay->clear();

    if (!mModel)
        return;

    for (int column = 0; column < mModel->columnCount(); ++column)
        mCurrentDay->addItem(mModel->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString());
}


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

#include "mainwidget.h"

#include "weathermodel.h"
#include "dayview.h"
#include "temperatureview.h"
#include "worldview.h"

#include <QtGui/QApplication>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent), mModel(new WeatherModel)
{
    setWindowTitle("Weather Information");

    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *button = 0;

    button = new QPushButton("Weather Table");
    layout->addWidget(button);
    connect(button, SIGNAL(clicked()), SLOT(showTableView()));

    button = new QPushButton("Day View");
    layout->addWidget(button);
    connect(button, SIGNAL(clicked()), SLOT(showDayView()));

    button = new QPushButton("Temperature View");
    layout->addWidget(button);
    connect(button, SIGNAL(clicked()), SLOT(showTemperatureView()));

    button = new QPushButton("World View");
    layout->addWidget(button);
    connect(button, SIGNAL(clicked()), SLOT(showWorldView()));

    button = new QPushButton("Quit");
    layout->addWidget(button);
    connect(button, SIGNAL(clicked()), qApp, SLOT(quit()));
}

MainWidget::~MainWidget()
{
}

void MainWidget::showTableView()
{
    QTableView *view = new QTableView;
    view->setModel(mModel);
    view->resize(685, 200);
    view->show();
}

void MainWidget::showDayView()
{
    DayView *view = new DayView;
    view->setModel(mModel);
    view->show();
}

void MainWidget::showTemperatureView()
{
    TemperatureView *view = new TemperatureView;
    view->setModel(mModel);
    view->show();
}

void MainWidget::showWorldView()
{
    WorldView *view = new WorldView;
    view->setModel(mModel);
    view->show();
}

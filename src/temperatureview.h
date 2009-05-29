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

#ifndef TEMPERATUREVIEW_H
#define TEMPERATUREVIEW_H

#include <QtGui/QImage>
#include <QtGui/QWidget>

class WeatherModel;

class QComboBox;

/**
 * @short A temperature view for weather information.
 *
 * This widget shows the temperature information from
 * a weather model for a given location.
 */
class TemperatureView : public QWidget
{
    Q_OBJECT

    public:
        /**
         * Creates a new temperature view.
         *
         * @param parent The parent widget.
         */
        TemperatureView(QWidget *parent = 0);

        /**
         * Destroys the temperature view.
         */
        ~TemperatureView();

        /**
         * Sets the weather @p model to show information from.
         */
        void setModel(WeatherModel *model);

    public Q_SLOTS:
        /**
         * Sets the @p location where the temperature shall be shown from.
         */
        void setCurrentLocation(int location);

    protected:
        virtual void paintEvent(QPaintEvent*);

    private Q_SLOTS:
        void layoutChanged();

    private:
        WeatherModel *mModel;
        int mCurrentLocation;
        QComboBox *mLocations;
};

#endif

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

#ifndef WORLDVIEW_H
#define WORLDVIEW_H

#include <QtGui/QImage>
#include <QtGui/QWidget>

class WeatherModel;

class QComboBox;
class QModelIndex;

/**
 * @short A world view for weather information.
 *
 * This widget shows the weather information from
 * a weather model on a world map.
 */
class WorldView : public QWidget
{
    Q_OBJECT

    public:
        /**
         * Creates a new world view.
         *
         * @param parent The parent widget.
         */
        WorldView(QWidget *parent = 0);

        /**
         * Destroys the world view.
         */
        ~WorldView();

        /**
         * Sets the weather @p model to show information from.
         */
        void setModel(WeatherModel *model);

    public Q_SLOTS:
        /**
         * Sets the @p day of the 5-day forecast, that shall be
         * shown.
         */
        void setCurrentDay(int day);

    protected:
        virtual void paintEvent(QPaintEvent*);

    private Q_SLOTS:
        void layoutChanged();
        void dataChanged(const QModelIndex&, const QModelIndex&);

    private:
        WeatherModel *mModel;
        QImage mMap;
        int mCurrentDay;
        QComboBox *mWeekdays;
};

#endif

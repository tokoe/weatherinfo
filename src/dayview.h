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

#ifndef DAYVIEW_H
#define DAYVIEW_H

#include <QtGui/QWidget>

class WeatherModel;
class QComboBox;
class QTextEdit;

/**
 * @short Displays the weather information for a single location and day.
 *
 * This view shows the weather information for a single location on a
 * given day that can be choosen by the user.
 */
class DayView : public QWidget
{
    Q_OBJECT

    public:
        /**
         * Creates a new day view.
         *
         * @param parent The parent widget.
         */
        DayView(QWidget *parent = 0);

        /**
         * Destroys the day view.
         */
        ~DayView();

        /**
         * Sets the weather @p model to use.
         */
        void setModel(WeatherModel *model);

    private Q_SLOTS:
        void layoutChanged();
        void updateView();

    private:
        void updateLocations();
        void updateDays();

        WeatherModel *mModel;
        QComboBox *mLocation;
        QComboBox *mCurrentDay;
        QTextEdit *mView;
};

#endif

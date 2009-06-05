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

#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QtGui/QWidget>

class LocationFilterProxy;
class WeatherModel;
class QLineEdit;
class QTableView;

/**
 * @short Displays the weather information in a table view.
 *
 * This view shows the weather information for multiple locations
 * for the next 5 days in a table view. The user can filter for
 * the names of the locations that shall be shown.
 */
class TableView : public QWidget
{
    Q_OBJECT

    public:
        /**
         * Creates a new table view.
         *
         * @param parent The parent widget.
         */
        TableView(QWidget *parent = 0);

        /**
         * Destroys the table view.
         */
        ~TableView();

        /**
         * Sets the weather @p model to use.
         */
        void setModel(WeatherModel *model);

    private:
        LocationFilterProxy *mModel;
        QLineEdit *mSearchEdit;
        QTableView *mView;
};

#endif

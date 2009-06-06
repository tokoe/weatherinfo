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

#ifndef WEATHERMODEL_H
#define WEATHERMODEL_H

#include <QtCore/QAbstractTableModel>

#include "weatherset.h"

class AbstractStorage;

/**
 * @short A table model that provides weather information.
 *
 * This class is a table model that provides the 5-day weather
 * forecast for multiple locations.
 * The days are listed in the columns and the locations as rows.
 */
class WeatherModel : public QAbstractTableModel
{
    Q_OBJECT

    public:
        /**
         * Describes the roles of the weather model.
         */
        enum Roles
        {
            LocationIdRole = Qt::UserRole + 1, ///< The id of the location.
            NameRole,                          ///< The name of the location.
            LatitudeRole,                      ///< The latitude of the location.
            LongitudeRole,                     ///< The longitude of the location.
            WeekdayRole,                       ///< The weekday.
            WeatherConditionRole,              ///< The weather condition.
            WindDirectionRole,                 ///< The wind direction.
            WindSpeedRole,                     ///< The wind speed.
            TemperatureRole,                   ///< The temperature.
        };

        /**
         * Creates a new weather model.
         */
        WeatherModel();

        /**
         * Destroys the weather model.
         */
        ~WeatherModel();

        /**
         * Returns the number of columns of the model.
         */
        virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

        /**
         * Returns the number of rows of the model.
         */
        virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

        /**
         * Returns the data for the given model @p index.
         */
        virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

        /**
         * Returns the header data for the given @p section.
         */
        virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

        /**
         * Returns the item flags for the given @p index.
         */
        virtual Qt::ItemFlags flags(const QModelIndex &index) const;

        /**
         * Sets the data for the given model @p index.
         */
        virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    private Q_SLOTS:
        void weatherSetAdded(const WeatherSet&);
        void weatherSetRemoved(const WeatherSet&);
        void weatherSetChanged(const WeatherSet&);

    private:
        AbstractStorage *mStorage;
        QVector<WeatherSet> mWeatherSets;
};

#endif

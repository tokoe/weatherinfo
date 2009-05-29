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

#ifndef ABSTRACTSTORAGE_H
#define ABSTRACTSTORAGE_H

#include <QtCore/QObject>

class WeatherSet;

/**
 * @short An abstract interface to the weather information storage backend.
 *
 * This class is an abstract interface that describes the functionality
 * of the weather information storage backend.
 */
class AbstractStorage : public QObject
{
    Q_OBJECT

    public:
        /**
         * Initializes the weather information storage and starts
         * populating the weather information via the weatherSetAdded() signal.
         */
        virtual bool startStorage() = 0;
 
        /**
         * Stops the weather information storage.
         *
         * This method can be used to do resource cleanups.
         */
        virtual bool stopStorage() = 0;

    Q_SIGNALS:
        /**
         * This signal is emitted whenever a new weather @p set
         * has been added to (or is loaded into) the storage.
         */
        void weatherSetAdded(const WeatherSet &set);

        /**
         * This signal is emitted whenever a weather @p set
         * has been removed from the storage.
         */
        void weatherSetRemoved(const WeatherSet &set);

        /**
         * This signal is emitted whenever a weather @p set
         * has been changed in the storage.
         */
        void weatherSetChanged(const WeatherSet &set);
};

#endif

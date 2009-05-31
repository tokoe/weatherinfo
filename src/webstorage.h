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

#ifndef WEBSTORAGE_H
#define WEBSTORAGE_H

#include "abstractstorage.h"
#include "weatherset.h"

#include <QtCore/QVector>

/**
 * @short A web storage backend for weather information.
 *
 * This class provides a backend for weather information
 * that loads the data from a web server.
 */
class WebStorage : public AbstractStorage
{
    public:
        /**
         * Initializes the weather information storage and starts
         * populating the weather information via the weatherSetAdded() signal.
         */
        virtual bool startStorage();
 
        /**
         * Stops the weather information storage.
         */
        virtual bool stopStorage();

    private:
        QVector<WeatherSet> mWeatherSets;
};

#endif

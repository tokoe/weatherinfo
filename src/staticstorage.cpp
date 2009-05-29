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

#include "staticstorage.h"

bool StaticStorage::startStorage()
{
    WeatherSet::Weekdays weekdays;
    weekdays << "Saturday" << "Sunday" << "Monday" << "Tuesday" << "Wednesday";

    {
        WeatherSet set;
        set.setId("4236");
        set.setName("Dresden International");
        set.setLatitude(51.05);
        set.setLongitude(13.75);
        set.setWeekdays(weekdays);

        WeatherSet::WeatherConditions conditions;
        conditions << WeatherSet::Rain
                   << WeatherSet::ClearDay
                   << WeatherSet::Rain
                   << WeatherSet::ClearDay
                   << WeatherSet::Showers;
        set.setWeatherConditions(conditions);

        WeatherSet::WindDirections directions;
        directions << WeatherSet::WNW
                   << WeatherSet::SSE
                   << WeatherSet::NW
                   << WeatherSet::ESE
                   << WeatherSet::W;
        set.setWindDirections(directions);

        WeatherSet::WindSpeed speed;
        speed << 12 << 9 << 8 << 4 << 5;
        set.setWindSpeed(speed);

        WeatherSet::Temperatures temperatures;
        temperatures << 17 << 22 << 18 << 21 << 23;
        set.setTemperatures(temperatures);

        mWeatherSets << set;
    }

    {
        WeatherSet set;
        set.setId("0032");
        set.setName("Oslo");
        set.setLatitude(59.55);
        set.setLongitude(10.45);
        set.setWeekdays(weekdays);

        WeatherSet::WeatherConditions conditions;
        conditions << WeatherSet::Overcast
                   << WeatherSet::ClearDay
                   << WeatherSet::Rain
                   << WeatherSet::Showers
                   << WeatherSet::ClearDay;
        set.setWeatherConditions(conditions);

        WeatherSet::WindDirections directions;
        directions << WeatherSet::E
                   << WeatherSet::ESE
                   << WeatherSet::E
                   << WeatherSet::SSW
                   << WeatherSet::SSW;
        set.setWindDirections(directions);

        WeatherSet::WindSpeed speed;
        speed << 7 << 6 << 9 << 13 << 11;
        set.setWindSpeed(speed);

        WeatherSet::Temperatures temperatures;
        temperatures << 15 << 16 << 10 << 12 << 13;
        set.setTemperatures(temperatures);

        mWeatherSets << set;
    }

    for (int i = 0; i < mWeatherSets.count(); ++i)
        emit weatherSetAdded(mWeatherSets.at(i));

    return true;
}

bool StaticStorage::stopStorage()
{
    return true;
}

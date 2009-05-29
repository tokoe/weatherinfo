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

#include "weatherset.h"

WeatherSet::WeatherSet()
    : mLatitude(0), mLongitude(0)
{
}

void WeatherSet::setId(const QString &id)
{
    mId = id;
}

QString WeatherSet::id() const
{
    return mId;
}

void WeatherSet::setName(const QString &name)
{
    mName = name;
}

QString WeatherSet::name() const
{
    return mName;
}

void WeatherSet::setLatitude(double latitude)
{
    mLatitude = latitude;
}

double WeatherSet::latitude() const
{
    return mLatitude;
}

void WeatherSet::setLongitude(double longitude)
{
    mLongitude = longitude;
}

double WeatherSet::longitude() const
{
    return mLongitude;
}

void WeatherSet::setWeekdays(const Weekdays &weekdays)
{
    mWeekdays = weekdays;
}

WeatherSet::Weekdays WeatherSet::weekdays() const
{
    return mWeekdays;
}

void WeatherSet::setWeatherConditions(const WeatherConditions &conditions)
{
    mWeatherConditions = conditions;
}

WeatherSet::WeatherConditions WeatherSet::weatherConditions() const
{
    return mWeatherConditions;
}

void WeatherSet::setWindDirections(const WindDirections &directions)
{
    mWindDirections = directions;
}

WeatherSet::WindDirections WeatherSet::windDirections() const
{
    return mWindDirections;
}

void WeatherSet::setWindSpeed(const WindSpeed &speed)
{
    mWindSpeed = speed;
}

WeatherSet::WindSpeed WeatherSet::windSpeed() const
{
    return mWindSpeed;
}

void WeatherSet::setTemperatures(const Temperatures &temperatures)
{
    mTemperatures = temperatures;
}

WeatherSet::Temperatures WeatherSet::temperatures() const
{
    return mTemperatures;
}


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

#include "weathermodel.h"

#include "staticstorage.h"
#include "webstorage.h"

#include <QtGui/QIcon>

static QIcon iconForCondition(const WeatherSet::WeatherCondition condition)
{
    switch (condition) {
        case WeatherSet::ClearDay:
            return QIcon(":weather-clear.png");
        case WeatherSet::FewCloudsDay:
            return QIcon(":weather-few-clouds.png");
        case WeatherSet::PartlyCloudyDay:
            return QIcon(":weather-clouds.png");
        case WeatherSet::Overcast:
            return QIcon(":weather-many-clouds.png");
        case WeatherSet::Rain:
            return QIcon(":weather-showers.png");
        case WeatherSet::LightRain:
            return QIcon(":weather-showers-scattered.png");
        case WeatherSet::Showers:
            return QIcon(":weather-showers-scattered.png");
        case WeatherSet::ChanceShowersDay:
            return QIcon(":weather-showers-scattered-day.png");
        case WeatherSet::ChanceShowersNight:
            return QIcon(":weather-showers-scattered-night.png");
        case WeatherSet::ChanceSnowDay:
            return QIcon(":weather-snow-scattered-day.png");
        case WeatherSet::ChanceSnowNight:
            return QIcon(":weather-snow-scattered-night.png");
        case WeatherSet::Thunderstorm:
            return QIcon(":weather-storm.png");
        case WeatherSet::Hail:
            return QIcon(":weather-hail.png");
        case WeatherSet::Snow:
            return QIcon(":weather-snow.png");
        case WeatherSet::LightSnow:
            return QIcon(":weather-snow-scattered.png");
        case WeatherSet::Flurries:
            return QIcon(":weather-snow-scattered.png");
        case WeatherSet::RainSnow:
            return QIcon(":weather-snow-rain.png");
        case WeatherSet::FewCloudsNight:
            return QIcon(":weather-few-clouds-night.png");
        case WeatherSet::PartlyCloudyNight:
            return QIcon(":weather-clouds-night.png");
        case WeatherSet::ClearNight:
            return QIcon(":weather-clear-night.png");
        case WeatherSet::Mist:
            return QIcon(":weather-mist.png");
        case WeatherSet::Haze:
            return QIcon(":weather-mist.png");
        case WeatherSet::FreezingRain:
            return QIcon(":weather-freezing-rain.png");
        case WeatherSet::FreezingDrizzle:
            return QIcon(":weather-freezing-rain.png");
        case WeatherSet::ChanceThunderstormDay:
            return QIcon(":weather-scattered-storms-day.png");
        case WeatherSet::ChanceThunderstormNight:
            return QIcon(":weather-scattered-storms-night.png");
        case WeatherSet::NotAvailable:
            return QIcon(":weather-none-available.png");
    }

    return QIcon(":weather-none-available.png");
}

static QString nameForWindDirection(const WeatherSet::WindDirection direction)
{
    switch (direction) {
        case WeatherSet::N:
            return "N";
        case WeatherSet::NNE:
            return "NNE";
        case WeatherSet::NE:
            return "NE";
        case WeatherSet::ENE:
            return "ENE";
        case WeatherSet::E:
            return "E";
        case WeatherSet::SSE:
            return "SSE";
        case WeatherSet::SE:
            return "SE";
        case WeatherSet::ESE:
            return "ESE";
        case WeatherSet::S:
            return "S";
        case WeatherSet::NNW:
            return "NNW";
        case WeatherSet::NW:
            return "NW";
        case WeatherSet::WNW:
            return "WNW";
        case WeatherSet::W:
            return "W";
        case WeatherSet::SSW:
            return "SSW";
        case WeatherSet::SW:
            return "SW";
        case WeatherSet::WSW:
            return "WSW";
        case WeatherSet::VR:
            return "N/A";
    }

    return "N/A";
}

WeatherModel::WeatherModel()
{
    mStorage = new StaticStorage();

    connect(mStorage, SIGNAL(weatherSetAdded(const WeatherSet&)), SLOT(weatherSetAdded(const WeatherSet&)));
    connect(mStorage, SIGNAL(weatherSetRemoved(const WeatherSet&)), SLOT(weatherSetRemoved(const WeatherSet&)));
    connect(mStorage, SIGNAL(weatherSetChanged(const WeatherSet&)), SLOT(weatherSetChanged(const WeatherSet&)));

    mStorage->startStorage();
}

WeatherModel::~WeatherModel()
{
}

int WeatherModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 5;
    else
        return 0;
}

int WeatherModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return mWeatherSets.count();
    else
        return 0;
}

QVariant WeatherModel::data(const QModelIndex &index, int role) const
{
    if (index.column() < 0 || index.column() >= 5)
        return QVariant();

    if (index.row() < 0 || index.row() >= mWeatherSets.count())
        return QVariant();

    const WeatherSet set = mWeatherSets.at(index.row());

    if (role == Qt::DisplayRole) {
        QString output;
        output.sprintf("%d °C", set.temperatures().at(index.column()));
        return output;
    } else if (role == Qt::DecorationRole || role == WeatherConditionRole) {
        return iconForCondition(set.weatherConditions().at(index.column()));
    } else if (role == LocationIdRole) {
        return set.id();
    } else if (role == NameRole) {
        return set.name();
    } else if (role == LatitudeRole) {
        return set.latitude();
    } else if (role == LongitudeRole) {
        return set.longitude();
    } else if (role == WeekdayRole) {
        return set.weekdays().at(index.column());
    } else if (role == WindDirectionRole) {
        return nameForWindDirection(set.windDirections().at(index.column()));
    } else if (role == WindSpeedRole) {
        return set.windSpeed().at(index.column());
    } else if (role == TemperatureRole) {
        return set.temperatures().at(index.column());
    }

    return QVariant();
}

QVariant WeatherModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (mWeatherSets.count() == 0)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section < 0 || section >= 5)
            return QVariant();

        const WeatherSet set = mWeatherSets.first();
        const WeatherSet::Weekdays weekdays = set.weekdays();

        return weekdays.at(section);
    }
    if (orientation == Qt::Vertical) {
        if (section < 0 || section >= mWeatherSets.count())
            return QVariant();

        const WeatherSet set = mWeatherSets.at(section);
        return set.name();
    }

    return QVariant();
}

void WeatherModel::weatherSetAdded(const WeatherSet &set)
{
    mWeatherSets.append(set);

    emit layoutChanged();
}

void WeatherModel::weatherSetRemoved(const WeatherSet &set)
{
    for (int i = 0; i < mWeatherSets.count(); ++i) {
        if (mWeatherSets.at(i).id() == set.id()) {
            mWeatherSets.remove(i);
            emit layoutChanged();
            return;
        }
    }
}

void WeatherModel::weatherSetChanged(const WeatherSet &set)
{
    for (int i = 0; i < mWeatherSets.count(); ++i) {
        if (mWeatherSets.at(i).id() == set.id()) {
            mWeatherSets[i] = set;
            emit layoutChanged();
            return;
        }
    }
}

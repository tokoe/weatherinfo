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

#include "webstorage.h"

#include <QtCore/QDebug>
#include <QtCore/QPointF>
#include <QtCore/QStringList>
#include <QtXmlPatterns/QXmlQuery>

static WeatherSet::WindDirection directionForString(const QString &direction)
{
    static QHash<QString, WeatherSet::WindDirection> hash;
    if (hash.isEmpty()) {
        hash["N"] = WeatherSet::N;
        hash["NNE"] = WeatherSet::NNE;
        hash["NE"] = WeatherSet::NE;
        hash["ENE"] = WeatherSet::ENE;
        hash["E"] = WeatherSet::E;
        hash["SSE"] = WeatherSet::SSE;
        hash["SE"] = WeatherSet::SE;
        hash["ESE"] = WeatherSet::ESE;
        hash["S"] = WeatherSet::S;
        hash["NNW"] = WeatherSet::NNW;
        hash["NW"] = WeatherSet::NW;
        hash["WNW"] = WeatherSet::WNW;
        hash["W"] = WeatherSet::W;
        hash["SSW"] = WeatherSet::SSW;
        hash["SW"] = WeatherSet::SW;
        hash["WSW"] = WeatherSet::WSW;
        hash["VR"] = WeatherSet::VR;
    }

    if (hash.contains(direction))
        return hash.value(direction);
    else
        return WeatherSet::VR;
}

static WeatherSet::WeatherCondition conditionForString(const QString &condition)
{
    static QHash<QString, WeatherSet::WeatherCondition> hash;
    if (hash.isEmpty()) {
        hash["sunny"] = WeatherSet::ClearDay;
        hash["clear"] = WeatherSet::ClearDay;
        hash["sunny intervals"] = WeatherSet::PartlyCloudyDay;
        hash["partly cloudy"] = WeatherSet::PartlyCloudyDay;
        hash["cloudy"] = WeatherSet::Overcast;
        hash["drizzle"] = WeatherSet::LightRain;
        hash["misty"] = WeatherSet::Mist;
        hash["mist"] = WeatherSet::Mist;
        hash["fog"] = WeatherSet::Mist;
        hash["foggy"] = WeatherSet::Mist;
        hash["tropical storm"] = WeatherSet::Thunderstorm;
        hash["hazy"] = WeatherSet::NotAvailable;
        hash["light shower"] = WeatherSet::Showers;
        hash["light rain shower"] = WeatherSet::Showers;
        hash["light showers"] = WeatherSet::Showers;
        hash["light rain"] = WeatherSet::Showers;
        hash["heavy rain"] = WeatherSet::Rain;
        hash["heavy showers"] = WeatherSet::Rain;
        hash["heavy shower"] = WeatherSet::Rain;
        hash["thundery shower"] = WeatherSet::Thunderstorm;
        hash["thunderstorm"] = WeatherSet::Thunderstorm;
        hash["cloudy with sleet"] = WeatherSet::RainSnow;
        hash["sleet shower"] = WeatherSet::RainSnow;
        hash["sleet showers"] = WeatherSet::RainSnow;
        hash["sleet"] = WeatherSet::RainSnow;
        hash["cloudy with hail"] = WeatherSet::Hail;
        hash["hail shower"] = WeatherSet::Hail;
        hash["hail showers"] = WeatherSet::Hail;
        hash["hail"] = WeatherSet::Hail;
        hash["light snow"] = WeatherSet::LightSnow;
        hash["light snow shower"] = WeatherSet::Flurries;
        hash["light snow showers"] = WeatherSet::Flurries;
        hash["cloudy with light snow"] = WeatherSet::LightSnow;
        hash["heavy snow"] = WeatherSet::Snow;
        hash["heavy snow shower"] = WeatherSet::Snow;
        hash["heavy snow showers"] = WeatherSet::Snow;
        hash["cloudy with heavy snow"] = WeatherSet::Snow;
        hash["na"] = WeatherSet::NotAvailable;
    }

    if (hash.contains(condition))
        return hash.value(condition);
    else
        return WeatherSet::NotAvailable;
}

static WeatherSet fetchWeatherSet(const QString &id)
{
    WeatherSet set;
    set.setId(id);

    {
        const QString locationNameQueryUrl = QString("doc(concat('http://www.bbc.co.uk/weather/mobile/5day.wml?world=', $id))/wml/card/p[2]/b[1]/text()");

        QString locationName;
        QXmlQuery query;
        query.bindVariable("id", QVariant(id));
        query.setQuery(locationNameQueryUrl);
        query.evaluateTo(&locationName);
        set.setName(locationName.trimmed());
    }

    {
        WeatherSet::Weekdays weekdays;
        for (int i = 0; i < 5; ++i) {
            const QString dayNameQueryUrl = QString("doc(concat('http://www.bbc.co.uk/weather/mobile/5day.wml?world=', $id))/wml/card/p[2]/b[$day]/text()");

            QString dayName;
            QXmlQuery query;
            query.bindVariable("id", QVariant(id));
            query.bindVariable("day", QVariant(2+i));
            query.setQuery(dayNameQueryUrl);
            query.evaluateTo(&dayName);
            weekdays.append(dayName.trimmed());
        }

        set.setWeekdays(weekdays);
    }

    const QString dataQueryUrl = QString("doc(concat('http://www.bbc.co.uk/weather/mobile/5day.wml?world=', $id))/wml/card/p[2]/text()");
    QString data;
    QXmlQuery query;
    query.bindVariable("id", QVariant(id));
    query.setQuery(dataQueryUrl);
    query.evaluateTo(&data);

    const QStringList dataList = data.split('\n', QString::SkipEmptyParts);

    WeatherSet::WeatherConditions conditions;
    WeatherSet::WindDirections directions;
    WeatherSet::WindSpeed speed;
    WeatherSet::Temperatures temperatures;
    for (int i = 0; i < 20; i += 4) {
        const QString conditionString = dataList.at(i);
        const QString temperatureString = dataList.at(i+1).mid(4);

        QStringList wind = dataList.at(i+3).split(' ');
        wind[1].remove("mph");
        wind[2].remove("(");
        wind[2].remove(")");

        conditions.append(conditionForString(conditionString));
        directions.append(directionForString(wind[2]));
        speed.append(wind[1].toInt());
        temperatures.append(temperatureString.toInt());
    }

    set.setWeatherConditions(conditions);
    set.setWindDirections(directions);
    set.setWindSpeed(speed);
    set.setTemperatures(temperatures);

    static QHash<QString, QPointF> coordinates;
    if (coordinates.isEmpty()) {
        coordinates["0032"] = QPointF(59.55, 10.45);
        coordinates["4236"] = QPointF(51.05, 13.75);
        coordinates["1450"] = QPointF(12.37, -1.52);
        coordinates["0498"] = QPointF(37.215, -93.298);
        coordinates["2253"] = QPointF(52.266, 104.333);
        coordinates["0101"] = QPointF(42.149, -74.938);
        coordinates["0080"] = QPointF(30.064, 31.249);
        coordinates["6632"] = QPointF(-33.883, 151.216);
        coordinates["0302"] = QPointF(-34.858, -56.170);
        coordinates["0087"] = QPointF(35.685, 139.751);
    }

    if (coordinates.contains(id)) {
        set.setLatitude(coordinates.value(id).x());
        set.setLongitude(coordinates.value(id).y());
    }

    return set;
}

bool WebStorage::startStorage()
{
    mWeatherSets.append(fetchWeatherSet("0032"));
    mWeatherSets.append(fetchWeatherSet("4236"));
    mWeatherSets.append(fetchWeatherSet("1450"));
    mWeatherSets.append(fetchWeatherSet("0498"));
    mWeatherSets.append(fetchWeatherSet("2253"));
    mWeatherSets.append(fetchWeatherSet("0101"));
    mWeatherSets.append(fetchWeatherSet("0080"));
    mWeatherSets.append(fetchWeatherSet("6632"));
    mWeatherSets.append(fetchWeatherSet("0302"));
    mWeatherSets.append(fetchWeatherSet("0087"));

    for (int i = 0; i < mWeatherSets.count(); ++i)
        emit weatherSetAdded(mWeatherSets.at(i));


    return true;
}

bool WebStorage::stopStorage()
{
    return true;
}

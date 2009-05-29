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

#ifndef WEATHERSET_H
#define WEATHERSET_H

#include <QtCore/QString>
#include <QtCore/QVector>

/**
 * @short Contains all weather information for location.
 *
 * This class contains information about a location and
 * the weather forecast for the next 5 days. It is used
 * to feed the WeatherModel with data from the different
 * backends.
 */
class WeatherSet
{
    public:
        /**
         * Describes the weather condition at one location.
         */
        enum WeatherCondition
        {
            ClearDay = 1,
            FewCloudsDay,
            PartlyCloudyDay,
            Overcast,
            Rain,
            LightRain,
            Showers,
            ChanceShowersDay,
            Thunderstorm,
            Hail,
            Snow,
            LightSnow,
            Flurries,
            FewCloudsNight,
            ChanceShowersNight,
            PartlyCloudyNight,
            ClearNight,
            Mist,
            Haze,
            FreezingRain,
            RainSnow,
            FreezingDrizzle,
            ChanceThunderstormDay,
            ChanceThunderstormNight,
            ChanceSnowDay,
            ChanceSnowNight,
            NotAvailable
        };

        /**
         * Describes the wind direction at one location.
         */
        enum WindDirection
        {
            N,   ///< North
            NNE, ///< North-Northeast
            NE,  ///< Northeast
            ENE, ///< East-Northeast
            E,   ///< East
            SSE, ///< South-Southeast
            SE,  ///< Southeast
            ESE, ///< East-Southeast
            S,   ///< South
            NNW, ///< North-Northwest
            NW,  ///< Northwest
            WNW, ///< West-Northwest
            W,   ///< West
            SSW, ///< South-Southwest
            SW,  ///< Southwest
            WSW, ///< West-Southwest
            VR   ///< Various directions
        };

        typedef QVector<QString> Weekdays;
        typedef QVector<WeatherCondition> WeatherConditions;
        typedef QVector<WindDirection> WindDirections;
        typedef QVector<int> WindSpeed;
        typedef QVector<int> Temperatures;

        /**
         * Creates an empty weather set.
         */
        WeatherSet();

        /**
         * Sets the @p id for the weather set.
         */
        void setId(const QString &id);

        /**
         * Returns the id for the weather set.
         */
        QString id() const;

        /**
         * Sets the @p name for the location.
         */
        void setName(const QString &name);

        /**
         * Returns the name of the location.
         */
        QString name() const;

        /**
         * Sets the @p latitude of the location.
         */
        void setLatitude(double latitude);

        /**
         * Returns the latitude of the location.
         */
        double latitude() const;

        /**
         * Sets the longitude of the location.
         */
        void setLongitude(double longitude);

        /**
         * Returns the longitude of the location.
         */
        double longitude() const;

        /**
         * Sets the names of the next 5 @p weekdays.
         */
        void setWeekdays(const Weekdays &weekdays);

        /**
         * Returns the names of the next 5 weekdays.
         */
        Weekdays weekdays() const;

        /**
         * Sets the weather @p conditions for the next 5 days.
         */
        void setWeatherConditions(const WeatherConditions &conditions);

        /**
         * Returns the weather conditions for the next 5 days.
         */
        WeatherConditions weatherConditions() const;

        /**
         * Sets the wind @p directions for the next 5 days.
         */
        void setWindDirections(const WindDirections &directions);

        /**
         * Returns the wind directions for the next 5 days.
         */
        WindDirections windDirections() const;

        /**
         * Sets the wind @p speed for the next 5 days.
         */
        void setWindSpeed(const WindSpeed &speed);

        /**
         * Returns the wind speed for the next 5 days.
         */
        WindSpeed windSpeed() const;

        /**
         * Sets the @p temperatures for the next 5 days.
         */
        void setTemperatures(const Temperatures &temperatures);

        /**
         * Returns the temperatures for the next 5 days.
         */
        Temperatures temperatures() const;

    private:
        QString mId;
        QString mName;
        double mLatitude;
        double mLongitude;
        Weekdays mWeekdays;
        WeatherConditions mWeatherConditions;
        WindDirections mWindDirections;
        WindSpeed mWindSpeed;
        Temperatures mTemperatures;
};

#endif

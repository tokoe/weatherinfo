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

#include "tableview.h"

#include "weathermodel.h"

#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSortFilterProxyModel>
#include <QtGui/QTableView>

class LocationFilterProxy : public QSortFilterProxyModel
{
    public:
        LocationFilterProxy(QLineEdit *lineEdit, QObject *parent)
            : QSortFilterProxyModel(parent), mLineEdit(lineEdit)
        {
        }

    protected:
        virtual bool filterAcceptsRow(int row, const QModelIndex &parent) const
        {
            Q_UNUSED(parent);

            const QModelIndex index = sourceModel()->index(row, 0);
            const QString location = index.data(WeatherModel::NameRole).toString();

            if (mLineEdit->text().isEmpty())
                return true;
            else
                return location.toLower().contains(mLineEdit->text().toLower());
        }

    private:
        QLineEdit *mLineEdit;
};

TableView::TableView(QWidget *parent)
    : QWidget(parent), mModel(0)
{
    QGridLayout *layout = new QGridLayout(this);

    QLabel *label = new QLabel("Location:");
    layout->addWidget(label, 1, 0);

    mSearchEdit = new QLineEdit;
    layout->addWidget(mSearchEdit, 1, 1);

    mView = new QTableView;
    layout->addWidget(mView, 0, 0, 1, 2);

    mModel = new LocationFilterProxy(mSearchEdit, this);
    mView->setModel(mModel);

    connect(mSearchEdit, SIGNAL(textChanged(const QString&)),
            mModel, SLOT(invalidate()));

    resize(685, 200);
}

TableView::~TableView()
{
}

void TableView::setModel(WeatherModel *model)
{
    mModel->setSourceModel(model);
}

#include "listmodel.h"
#include "filterproxymodel.h"
#include <QDebug>

FilterProxyModel::FilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}


QString FilterProxyModel::getTargetString() const
{
    return target_string;
}

void FilterProxyModel::setTargetString(const QString &newString)
{
    if (target_string == newString)
        return;

    target_string = newString;
    emit targetStringChanged();

    invalidateFilter();
}


void FilterProxyModel::setSortOrder(bool checked)
{
    if(checked)
        this->sort(0, Qt::DescendingOrder);
    else
        this->sort(0, Qt::AscendingOrder);

    invalidateFilter(); // mandatory for custom filtering
}

QStringList FilterProxyModel::getRoleNamesList() const
{
    QHash<int, QByteArray> hash = roleNames();

    QStringList namesList;
    for(QByteArray x: hash.values()){
        namesList<<QString::fromUtf8(x);
    }

    return namesList;
}

int FilterProxyModel::getRoleCodeFromName(const QString roleName) const
{

    QHash<int, QByteArray> hash = roleNames();

    for(int key: hash.keys()){
        if( QString::fromUtf8( hash.value(key) ) == roleName )
            return key;
    }

    return -1; // unknown role
}

void FilterProxyModel::setFilterRole(int role)
{
    QSortFilterProxyModel::setFilterRole(role);
}

void FilterProxyModel::setSortRole(int role)
{
    QSortFilterProxyModel::setSortRole(role);

}


bool FilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (target_string.isEmpty())
        return true;

    const int requestedRole = filterRole();

    // apply the same kind of filter for name or email
    if(requestedRole == CustomListModel::NameRole || requestedRole == CustomListModel::EmailRole){
        const QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
        const QString stringValue = index.data( requestedRole ).toString();

        if ( stringValue.isEmpty() ||
                stringValue.contains(target_string, Qt::CaseInsensitive) ){
            return true;
        }
        else{
            return false;
        }
    }


    return true; // default behaviour (this is return when the unknown roles.)
}

bool FilterProxyModel::lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const
{
    const int requestedRole = sortRole();
    QString leftData;
    QString rightData;

    if(requestedRole == CustomListModel::NameRole){
         leftData = sourceLeft.data( CustomListModel::NameRole ).toString();
         rightData = sourceRight.data( CustomListModel::NameRole ).toString();
    }

    if(requestedRole == CustomListModel::EmailRole){
         leftData = sourceLeft.data( CustomListModel::EmailRole ).toString();
         rightData = sourceRight.data( CustomListModel::EmailRole ).toString();
    }

    return leftData.toUpper() < rightData.toUpper();

}

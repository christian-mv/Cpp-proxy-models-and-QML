#include "listmodel.h"
#include <QDebug>

CustomListModel::CustomListModel()
{

}

CustomListModel::~CustomListModel()
{

}

void CustomListModel::addData(const QString &name, const QString &email)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    CustomObject myObj(name, email);
    m_names.append(myObj);
    endInsertRows();
}

int CustomListModel::rowCount(const QModelIndex &parent) const
{    
    return parent.isValid() ? 0 : m_names.count();
}

QVariant CustomListModel::data(const QModelIndex &index, int role) const
{

    if (index.row() < 0 || index.row() >= m_names.count()){
        return QVariant();
    }


    const CustomObject customObj = m_names.at(index.row());

    switch (role) {
    case NameRole:
        return customObj.getName();
    case EmailRole:
        return customObj.getEmail();
    default:
        return QVariant();
    }

}

QHash<int, QByteArray> CustomListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name_role";
    roles[EmailRole] = "email_role";
    return roles;
}

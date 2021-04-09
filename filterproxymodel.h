#ifndef FILTERPROXYMODEL_H
#define FILTERPROXYMODEL_H

#include <QObject>
#include<QSortFilterProxyModel>

// this is a more general example of the code at:
// https://arunpkqt.wordpress.com/2016/12/08/qml-list-view-sort-and-filter/

class FilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(QString getTargetString READ getTargetString WRITE setTargetString NOTIFY targetStringChanged)

public:

    FilterProxyModel(QObject* parent = nullptr);

    Q_INVOKABLE void setSortOrder(bool checked);

    Q_INVOKABLE QStringList  getRoleNamesList() const;

    Q_INVOKABLE int  getRoleCodeFromName(const QString roleName) const;

    Q_INVOKABLE void setFilterRole(int role);

    Q_INVOKABLE void setSortRole(int role);



    QString getTargetString() const;

public slots:
    void setTargetString(const QString &newString);

signals:
    void targetStringChanged();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const override;

private:
    QString target_string;
};
#endif // FILTERPROXYMODEL_H

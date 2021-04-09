#ifndef CUSTOM_LIST_MODEL_H
#define CUSTOM_LIST_MODEL_H

#include <QAbstractListModel>
#include <QList>




class CustomObject {
public:
    CustomObject(const QString &newName, const QString &newEmail)
        : name(newName), email(newEmail) { }
    inline QString getName() const { return name; }
    inline QString getEmail() const { return email; }

private:
    QString name;
    QString email;
};

//List Model
class CustomListModel : public QAbstractListModel
{
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        EmailRole
    };

    CustomListModel();
    ~CustomListModel() override;

    void addData(const QString &name, const QString &email);

    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<CustomObject> m_names;
};

#endif

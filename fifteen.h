#ifndef FIFTEEN_H
#define FIFTEEN_H

#include <QObject>
#include <QQuickItem>
#include <QAbstractListModel>

class Fifteen : public QAbstractListModel
{
    Q_OBJECT
public:
    Fifteen(QObject *parent = 0);
    enum Roles {
            Number = Qt::UserRole + 1
    };
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    friend std::ostream& operator<< (std::ostream &out, const Fifteen &fifteen);

private:
    bool checkLoss();

public slots:
    void move(int index);
    void mixNumbers();

signals:
    void win();
    void reloadModel();

private:
    QList<int> m_numbers;
};

#endif // FIFTEEN_H

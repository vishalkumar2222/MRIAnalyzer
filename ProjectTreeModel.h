#ifndef PROJECTTREEMODEL_H
#define PROJECTTREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class TreeItem;

class ProjectTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ProjectTreeModel(QObject *parent = 0);
    ~ProjectTreeModel();

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;


    void SetRootEntity(TreeItem *parent);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);


signals:
    void VisibilityChanged(const QString&name, bool visibility);
private:
    TreeItem *rootItem;
};


#endif // PROJECTTREEMODEL_H

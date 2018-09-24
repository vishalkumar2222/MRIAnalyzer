
#include "TreeItem.h"
#include "ProjectTreeModel.h"

#include <QStringList>

ProjectTreeModel::ProjectTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{

}

ProjectTreeModel::~ProjectTreeModel()
{

}

int ProjectTreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

void ProjectTreeModel::SetRootEntity(TreeItem *parent)
{
    beginResetModel();
    rootItem = parent;
    endResetModel();
}

QVariant ProjectTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::CheckStateRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    if(role == Qt::DisplayRole)
    {
        return item->data();
    }
    else
    {
        if(item->childCount() == 0 && item->IsMesh())
        {
            if(item->GetChecked())
                return Qt::Checked;
            else
                return Qt::Unchecked;
        }
        else
        {
            return QVariant();
        }
    }
}


Qt::ItemFlags
ProjectTreeModel::flags(const QModelIndex& index) const {
    Qt::ItemFlags flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    if(item->childCount() == 0 && item->IsMesh())
    {
        flags |= Qt::ItemIsUserCheckable;
    }
    return flags;
}


bool
ProjectTreeModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (index.isValid() && role == Qt::CheckStateRole) {

        TreeItem* item = reinterpret_cast<TreeItem*>(index.internalPointer());
        item->SetChecked(value.toBool());
        emit dataChanged(index, index, QVector<int>({Qt::CheckStateRole}));
        emit VisibilityChanged(item->data().toString(), value.toBool());
        return true;
    }
    return false;
}

QModelIndex ProjectTreeModel::index(int row, int column, const QModelIndex &parent)
const
{
    if (parent.isValid())
    {
        TreeItem *parentItem = static_cast<TreeItem*>(parent.internalPointer());

        TreeItem *childItem = parentItem->child(row);
        if (childItem)
            return createIndex(row, column, childItem);
        else
            return QModelIndex();
    }
    else
    {
        return createIndex(row, column, rootItem);
    }

    return QModelIndex();
}

QModelIndex ProjectTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == nullptr)
    {
        return QModelIndex();
    }
    else
    {
        if(parentItem->parentItem() == nullptr)
        {
            return createIndex(0, 0, parentItem);
        }
        else
        {
            return createIndex(parentItem->row(), 0, parentItem);
        }
    }
}

int ProjectTreeModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        if (rootItem != nullptr) {
            return 1;
        } else {
            return 0;
        }
    }

    TreeItem *parentItem = static_cast<TreeItem*>(parent.internalPointer());
    return parentItem->childCount();

    return 0;
}


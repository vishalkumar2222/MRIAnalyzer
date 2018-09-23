
#include "TreeItem.h"

TreeItem::TreeItem(const QString &data, TreeItem *parent, bool is_mesh)
{
    m_parentItem = parent;
    name_ = data;
    checked_ = true;
    is_mesh_ = is_mesh;
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
    m_childItems.append(item);
}

TreeItem *TreeItem::child(int row)
{
    return m_childItems.value(row);
}

int TreeItem::childCount() const
{
    return m_childItems.count();
}

int TreeItem::columnCount() const
{
    return 1;
}

QVariant TreeItem::data() const
{
    return QVariant(name_);
}

TreeItem *TreeItem::parentItem()
{
    return m_parentItem;
}

bool TreeItem::GetChecked() const
{
    return checked_;
}

void TreeItem::SetChecked(bool checked)
{
    checked_ = checked;
}

bool TreeItem::IsMesh() const
{
    return is_mesh_;
}

int TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}


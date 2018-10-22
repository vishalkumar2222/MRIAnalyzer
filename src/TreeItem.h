#ifndef __TREEITEM_H__
#define __TREEITEM_H__

#include <QList>
#include <QVariant>


class TreeItem
{
public:
    explicit TreeItem(const QString &data,TreeItem *parentItem = 0, bool is_mesh =false);
    ~TreeItem();

    void appendChild(TreeItem *child);

    void removeAllChild();

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data() const;
    int row() const;
    TreeItem *parentItem();

    bool GetChecked() const;
    void SetChecked(bool checked);

    bool IsMesh() const;

    QString GetName() const;

private:
    QList<TreeItem*> m_childItems;
    QString name_;
    bool checked_;
    bool is_mesh_;
    TreeItem *m_parentItem;
};


#endif // TREEITEM_H

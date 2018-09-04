#include "ComboBoxDelegate.h"

ComboBoxDelegate::ComboBoxDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{

}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    QComboBox *combobox = new QComboBox(parent);
    combobox->setFrame(false);
    combobox->addItems(QStringList()<<"Image Stack" << "Mesh" <<"Activation Time");
    return combobox;
}

void ComboBoxDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();

    QComboBox *combobox = static_cast<QComboBox*>(editor);
    combobox->setCurrentText(value);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QComboBox *combobox = static_cast<QComboBox*>(editor);

    QString value = combobox->currentText();

    model->setData(index, value, Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}


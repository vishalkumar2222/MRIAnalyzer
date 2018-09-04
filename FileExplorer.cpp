#include "FileExplorer.h"

FileExplorer::FileExplorer(QObject *parent)
    : QAbstractTableModel(parent)
{

}

QVariant FileExplorer::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if(section == 0)
            return QString("File Name");
        else if(section == 1)
            return QString("Type");
    }
    else if (role == Qt::DisplayRole)
        return QString::number(section);

    return QAbstractItemModel::headerData(section, orientation, role);
}

int FileExplorer::rowCount(const QModelIndex &parent) const
{

    Q_UNUSED(parent)

    return information.size();

}

int FileExplorer::columnCount(const QModelIndex &parent) const
{

    Q_UNUSED(parent)

    return 2;

}

QVariant FileExplorer::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole && index.column() == 0)
    {
        return QString(information.keys().at(index.row()));
    }

    if(role == Qt::DisplayRole && index.column() == 1)
    {
        if(information.value(QString(information.keys().at(index.row()))) == FileType::ACTIVATION_TIME)
        {
            return QString("Activation Time");
        }
        else if(information.value(QString(information.keys().at(index.row()))) == FileType::MESH)
        {
            return QString("Mesh");
        }
        else if(information.value(QString(information.keys().at(index.row()))) == FileType::IMAGE_STACK)
        {
            return QString("Image Stack");
        }
    }

    return QVariant();
}

void FileExplorer::AddFileName(const QString &file_name)
{
    beginResetModel();

    QFileInfo info(file_name);

    if(info.suffix() == "vtk")
    {
        information.insert(file_name, FileType::MESH);
    }
    else if(info.suffix() == "nii")
    {
       information.insert(file_name, FileType::IMAGE_STACK);
    }

    endResetModel();
}

QMap<QString, FileExplorer::FileType> FileExplorer::GetInformation() const
{
    return information;
}

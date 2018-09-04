#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <QAbstractTableModel>
#include <QFileInfo>


class FileExplorer : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit FileExplorer(QObject *parent = 0);

    enum FileType{
        IMAGE_STACK = 1,
        MESH,
        ACTIVATION_TIME
    };

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void AddFileName(const QString& file_name);

    QMap<QString, FileExplorer::FileType> GetInformation() const;

private:
    QMap<QString,FileExplorer::FileType> information;
};

#endif // FILEEXPLORER_H

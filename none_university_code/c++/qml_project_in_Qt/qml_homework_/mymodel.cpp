#include "mymodel.h"

#include <QFileDialog>

MyModel::MyModel(QObject *parent)
    : QAbstractListModel(parent)
{

    const QString folderPath = QFileDialog::getExistingDirectory( nullptr, "Image folder");
    if(!folderPath.isEmpty())
    {
        QDir dir(folderPath);
        QStringList filter;
        filter << QLatin1String("*.jpeg");
        filter << QLatin1String("*.jpg");
        filter << QLatin1String("*.png");
        dir.setNameFilters(filter);
        QFileInfoList filelistinfo = dir.entryInfoList();
        QStringList fileList;
        foreach (const QFileInfo &fileinfo, filelistinfo) {
            m_data.push_back(fileinfo.absoluteFilePath());
         }
    }
}

QVariant MyModel::data(const QModelIndex& index, int role) const
{
    const size_t row = static_cast<size_t>(index.row());
    if ( !index.isValid() || index.row() < 0 || row >= m_data.size() )
    {
        return QVariant();
    }
    const QString& modelEntry = m_data[row];
    if (role == Role1)
    {
        return modelEntry;
    }
    return QVariant();
}

int MyModel::rowCount(const QModelIndex& /*parent*/) const
{
    return static_cast<int>(m_data.size());
}

QHash<int, QByteArray> MyModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Role1] = "role1";
    return roles;
}


#ifndef PROCFSMODEL_H
#define PROCFSMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QFileInfo>
#include "procfs.h"
#include <QIcon>

class ProcFsIcons;

class ProcFsModel : public QAbstractItemModel {
    Q_OBJECT
public:
    explicit ProcFsModel (QObject* parent = 0);
    ~ProcFsModel ();

    QVariant data (const QModelIndex& index, int role) const;
    Qt::ItemFlags flags (const QModelIndex& index) const;
    QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index (int row, int column, const QModelIndex& parent = QModelIndex ()) const;
    QModelIndex index (QString& path) const;
    QModelIndex parent (const QModelIndex& index) const;
    int rowCount (const QModelIndex& parent = QModelIndex ()) const;
    int columnCount (const QModelIndex& parent = QModelIndex ()) const;
    QFileInfo fileInfo (const QModelIndex& index) const;
    QIcon fileIcon (const QModelIndex& index) const;

    Direntry* at (const QModelIndex& index);
    QModelIndex rootIndex ();

    ProcFs* getFs () { return m_proc_fs; }

    void update (Direntry *entry);

public slots:

private:
    ProcFs* m_proc_fs;
    ProcFsIcons* m_icons;

    bool addOrRemoveEntry (Direntry* entry);
};

#endif // PROCFSMODEL_H

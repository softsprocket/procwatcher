#include "procfsmodel.h"

#include <QObject>
#include <QModelIndex>
#include <iostream>
#include <QFileIconProvider>
#include <QPixmap>
#include <dirent.h>

#include "procfsicons.h"


ProcFsModel::ProcFsModel (QObject* parent) :
    QAbstractItemModel (parent) {
    m_proc_fs = new ProcFs;
    m_icons = new ProcFsIcons;

}

ProcFsModel::~ProcFsModel () {
    delete m_icons;
    delete m_proc_fs;
}

QVariant ProcFsModel::data (const QModelIndex& index, int role) const {

    if (!index.isValid ())
        return QVariant ();

    if (role == Qt::DecorationRole) {
        return fileIcon (index);
    }

    Direntry* entry = static_cast<Direntry*> (index.internalPointer ());

    if (role != Qt::DisplayRole)
        return QVariant ();


    return entry->name ();
}

Qt::ItemFlags ProcFsModel::flags (const QModelIndex& index) const {

    if (!index.isValid ()) {
        return 0;
    }

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ProcFsModel::headerData (int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return QVariant ("Name");

    return QVariant ();
}

QModelIndex ProcFsModel::index (int row, int column, const QModelIndex& parent) const {

    if (row < 0 || column < 0 || row >= rowCount (parent) || column >= columnCount (parent))
        return QModelIndex ();

    Direntry* parent_entry;

    if (!parent.internalPointer ()) {
        parent_entry = m_proc_fs->entries ();
    } else {
        parent_entry = static_cast<Direntry*> (parent.internalPointer ());
    }

    Direntry* child_entry = parent_entry->at (row);

    if (child_entry) {
        return createIndex (row, column, child_entry);
    }

    return QModelIndex ();
}

QModelIndex ProcFsModel::index (QString& path) const {
    return QModelIndex ();
}

QModelIndex ProcFsModel::parent (const QModelIndex& index) const {

    if (!index.isValid ())
        return QModelIndex ();

    Direntry* index_entry = static_cast<Direntry*> (index.internalPointer ());
    Direntry* parent_entry = index_entry ? index_entry->parent () : 0;

    if (!parent_entry || parent_entry == m_proc_fs->entries ())
        return QModelIndex ();

    return createIndex (parent_entry->row (), 0, parent_entry);
}

int ProcFsModel::rowCount (const QModelIndex& parent) const {
    Direntry* parent_entry;
    if (parent.column () > 0) {
        return 0;
    }

    if (!parent.isValid ()) {
        parent_entry = m_proc_fs->entries ();
    } else {
        parent_entry = static_cast<Direntry*> (parent.internalPointer ());
    }

    return parent_entry->count ();
}

int ProcFsModel::columnCount (const QModelIndex& parent) const {
    return (parent.column () > 0) ? 0 : 1;
}

QFileInfo ProcFsModel::fileInfo (const QModelIndex& index) const {
    Direntry* index_entry = static_cast<Direntry*> (index.internalPointer ());
    return QFileInfo (index_entry->pathName ());
}

QIcon ProcFsModel::fileIcon (const QModelIndex& index) const {

    Direntry* index_entry = static_cast<Direntry*> (index.internalPointer ());

    QIcon* ico = m_icons->get (index_entry->type ());

    if (ico) {
        return *ico;
    }

    QFileIconProvider ip;
    if (index_entry->isDir ()) {
        return ip.icon (ip.Folder);
    }

    return ip.icon (ip.File);
}

QModelIndex ProcFsModel::rootIndex () {
    return createIndex (0, 0, m_proc_fs->entries ());
}

Direntry* ProcFsModel::at (const QModelIndex& index) {
    if (!index.isValid ())
        return 0;

    return static_cast<Direntry*> (index.internalPointer ());
}

bool ProcFsModel::addOrRemoveEntry (Direntry* entry) {
    Direntry* data_store = m_proc_fs->entries ();

    int i = 0;
    std::vector<Direntry*>::iterator data_store_iter = data_store->begin ();
    std::vector<Direntry*>::iterator entry_iter = entry->begin ();

    for (; entry_iter < entry->end (); ++entry_iter) {

        if (! (data_store_iter < data_store->end ())) {

            Direntry* copy = (*entry_iter)->copy (m_proc_fs->entries ());

            beginInsertRows (rootIndex (), i, i);

            data_store->push_back (copy);

            endInsertRows ();

        } else {
            std::string name_in_store = (*data_store_iter)->name ();
            std::string name_in_entry = (*entry_iter)->name ();

            if (name_in_store != name_in_entry) {
                if (Direntry::compare_dirent ((*data_store_iter), (*entry_iter))) {

                    beginRemoveRows (rootIndex (), i, i);

                    delete (*data_store_iter);
                    data_store_iter = data_store->erase (data_store_iter);

                    endRemoveRows ();

                    return false;
                } else {

                    Direntry* copy = (*entry_iter)->copy (m_proc_fs->entries ());

                    beginInsertRows (rootIndex (), i, i);

                    data_store_iter = data_store->insert (copy, data_store_iter);

                    endInsertRows ();

                }
            }
        }

        ++i;
        ++data_store_iter;
    }

    return true;
}

void ProcFsModel::update (Direntry* entry) {
    bool done;
    do {
        done = addOrRemoveEntry (entry);
    } while (!done);

    delete entry;
}


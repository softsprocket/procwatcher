#include "procfs.h"

#include <dirent.h>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstdlib>

const static char* const PROCFS_PATH_SEPARATOR = "/";

Direntry::Direntry (struct dirent* de, Direntry* parent) :
    m_parent (parent) {

    m_pathName = 0;

    m_de = new struct dirent;
    memcpy (m_de, de, sizeof (*de));

    if (parent) {
        m_path = parent->path ();
        if (m_path != PROCFS_PATH_SEPARATOR) {
            m_path.append (PROCFS_PATH_SEPARATOR);
        }
        m_path.append (parent->name ());
    } else {
        m_path = PROCFS_PATH_SEPARATOR;
    }

}

Direntry::~Direntry () {
    delete m_de;

    for (std::vector<Direntry*>::iterator it = m_column.begin () ; it != m_column.end (); ++it) {
        delete *it;
    }

    if (m_pathName) {
        delete [] m_pathName;
    }
}


Direntry* Direntry::copy (Direntry* parent) {

    struct dirent de;
    memcpy (&de, m_de, sizeof (*m_de));

    Direntry* cpy = new Direntry (&de, parent);

    for (std::vector<Direntry*>::iterator it = m_column.begin (); it < m_column.end (); ++it) {
        cpy->push_back ((*it)->copy (cpy));
    }

    return cpy;
}

bool Direntry::isDir () {
    return DT_DIR == m_de->d_type;
}

int Direntry::type () {
    return m_de->d_type;
}

char* Direntry::name () {
    return m_de->d_name;
}

const char* Direntry::path () {
    return m_path.c_str ();
}

const char* Direntry::pathName () {
    static const char* sep = "/";

    if (m_pathName == 0) {
        int plen = strlen (path ());
        int nlen = strlen (m_de->d_name);

        m_pathName = new char [plen + nlen + 2];
        char* ppn = m_pathName;

        memcpy (ppn, path (), plen);

        ppn += plen;
        if (plen != 1) {
            memcpy (ppn, sep, 1);
            ++ppn;
        }

        memcpy (ppn, m_de->d_name, nlen);

        ppn += nlen;
        *ppn = '\0';
    }

    return m_pathName;
}

Direntry* Direntry::parent () {
    return m_parent;
}

Direntry* Direntry::at (int pos) {

    if (pos >= m_column.size ()) {
        return 0;
    }

    return m_column[pos];
}

int Direntry::row () {
    int pos = 0;

    if (m_parent) {
        for (std::vector<Direntry*>::iterator it = m_parent->begin (); it != m_parent->end (); ++it) {
            if ((*it) == this) {
                break;
            }
            ++pos;
        }
    }

    return pos;
}

int Direntry::count () {
    return m_column.size ();
}

bool Direntry::compare_dirent (Direntry* lhd, Direntry* rhd) {
    if (lhd->isDir () && !rhd->isDir ()) {
        return true;
    }

    if (rhd->isDir () && !lhd->isDir ()) {
        return false;
    }

    if (isdigit (lhd->name ()[0])) {
        if (!isdigit (rhd->name ()[0])) {
            return true;
        }

        int l = strtol (lhd->name (), 0, 10);
        int r = strtol (rhd->name (), 0, 10);

        return l < r;
    }

    return strcmp (lhd->name (), rhd->name ()) < 0;
}

void Direntry::sort () {
    std::sort (m_column.begin (), m_column.end (), compare_dirent);
}

std::vector<Direntry*>::iterator Direntry::insert (Direntry* entry, std::vector<Direntry*>::iterator iter) {
    return m_column.insert (iter, entry);
}

std::vector<Direntry*>::iterator  Direntry::erase (std::vector<Direntry*>::iterator iter) {
    return m_column.erase (iter);
}

ProcFs::ProcFs ()
    : m_de (0), m_last_err (0), m_last_error_level (PFE_NONE) {
    m_dirp = opendir ("/proc");

    if (m_dirp == 0) {
        error (strerror (errno), PFE_FATAL);
    } else {
        struct dirent de;
        strcpy (de.d_name, "proc");
        de.d_type = DT_DIR;

        m_de = new Direntry (&de);

        readDir (m_dirp, m_de, true);

        m_de->sort ();
    }
}


ProcFs::~ProcFs () {

    if (m_de) {
        delete m_de;
    }

    if (m_dirp) {
        closedir (m_dirp);
    }
}

void ProcFs::error (char* err, ProcFsError level) {
    if (m_last_err) {
        delete m_last_err;
    }

    m_last_err = new char[strlen (err) + 1];
    strcpy (m_last_err, err);
    m_last_error_level = level;
}

void ProcFs::readDir (DIR* dir, Direntry* parent, bool close) {
    struct dirent* nxt;

    while ((nxt = readdir (dir))) {

        if ((strcmp (nxt->d_name, ".") == 0) || (strcmp (nxt->d_name, "..") == 0)) continue;

        Direntry* de = new Direntry (nxt, parent);
        de->sort ();

        parent->push_back (de);

        if (de->isDir ()) {
            std::string dp = parent->pathName ();
            if (dp != PROCFS_PATH_SEPARATOR) {
                dp.append (PROCFS_PATH_SEPARATOR);
            }

            dp.append (de->name ());

            DIR* d = opendir (dp.c_str ());

            if (d) {
                readDir (d, de, true);

                if (close) {
                    closedir (d);
                }
            }
        }
    }
}


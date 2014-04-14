#ifndef PROCFS_H
#define PROCFS_H

#include <dirent.h>
#include <vector>
#include <cerrno>
#include <string>
#include <QMetaType>

enum ProcFsError {
    PFE_WARNING,
    PFE_ERROR,
    PFE_FATAL,
    PFE_NONE
};

class Direntry {
    struct dirent* m_de;
    std::string m_path;
    std::vector<Direntry*> m_column;
    Direntry* m_parent;
    char* m_pathName;
public:
    Direntry (struct dirent* de, Direntry* parent = 0);

    ~Direntry ();

    Direntry* copy (Direntry* parent);
    bool isDir ();
    char* name ();
    const char* path ();
    const char* pathName ();

    Direntry* at (int pos);
    Direntry* parent ();
    int row ();
    int count ();
    int type ();

    void push_back (Direntry* de) { m_column.push_back (de); }

    std::vector<Direntry*>::iterator begin () { return m_column.begin (); }
    std::vector<Direntry*>::iterator end () { return m_column.end (); }

    void sort ();
    std::vector<Direntry*>::iterator insert (Direntry* entry, std::vector<Direntry*>::iterator iter);
    std::vector<Direntry*>::iterator  erase (std::vector<Direntry*>::iterator iter);

    static bool compare_dirent (Direntry* lhd, Direntry* rhd);

};

class ProcFs {
    DIR* m_dirp;
    Direntry* m_de;

    char* m_last_err;
    ProcFsError m_last_error_level;


public:
    ProcFs ();
    ~ProcFs ();

    Direntry* entries () { return m_de; }
    void error (char* err, ProcFsError level);
    char* lastError () { return m_last_err; }
    ProcFsError lastErrorLevel () { return m_last_error_level; }

    static void readDir (DIR* dir, Direntry* parent, bool close);
};



#endif // PROCFS_H

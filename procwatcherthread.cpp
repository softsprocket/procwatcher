#include "procwatcherthread.h"

#include <iostream>
#include "procfs.h"


void ProcWatcherThread::init (ProcFs* pfs) {
    m_pfs = pfs;
    m_interval = 1000;
    m_running = false;

    m_pause = false;

}

void ProcWatcherThread::stop () {
    m_running = false;
    wait (1000);
}

void ProcWatcherThread::run () {
    m_running = true;

    while (m_running) {
        msleep (m_interval);

        m_sync.lock ();
        if (m_pause) {
            m_pauseCond.wait (&m_sync);
        }
        m_sync.unlock ();

        if (!m_running) break;

        if (m_pfs) {
            Direntry* old_entry = m_pfs->entries ();

            DIR* dirp = opendir ("/proc");
            if (!dirp) {
                std::cerr << "Unable to open Directory /proc in thread" << std::endl;
                break;
            }

            struct dirent de;
            strcpy (de.d_name, "proc");
            de.d_type = DT_DIR;
            Direntry* new_entry = new Direntry (&de);
            ProcFs::readDir (dirp, new_entry, true);
            new_entry->sort ();
            closedir (dirp);

            if (!m_running) {
                delete new_entry;
                break;
            }

            if (new_entry && old_entry) {

                if (new_entry->count () != old_entry->count ()) {
                    emit modelChanged (new_entry);
                } else {
                    delete new_entry;
                }
            } else {
                if (new_entry == 0) {
                    std::cerr << "new entry not the valid" << std::endl;
                } else {
                    std::cerr << "old entry not the valid" << std::endl;
                    delete new_entry;
                }
            }
        }

    }

}

void ProcWatcherThread::resume () {
    m_sync.lock ();
    m_pause = false;
    m_sync.unlock ();
    m_pauseCond.wakeAll ();
}

void ProcWatcherThread::pause () {
    m_sync.lock ();
    m_pause = true;
    m_sync.unlock ();
}


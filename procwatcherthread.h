#ifndef PROCWATCHERTHREAD_H
#define PROCWATCHERTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <procfs.h>

class ProcWatcherThread : public QThread {
    Q_OBJECT
private:
    ProcFs* m_pfs;
    bool m_running;
    int m_interval;
    QMutex m_sync;
    QWaitCondition m_pauseCond;
    bool m_pause;
public:

    void init (ProcFs* pfs);
    void stop ();
    void run ();

    void resume ();
    void pause ();

signals:
    void modelChanged (Direntry*);
};

#endif // PROCWATCHERTHREAD_H

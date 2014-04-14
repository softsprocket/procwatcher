#ifndef PROCWATCHER_H
#define PROCWATCHER_H

#include <QMainWindow>
#include <QFileInfo>
#include <QFile>
#include <QTimer>
#include <QKeyEvent>

#include "procfsmodel.h"

namespace Ui {
    class ProcWatcher;
}

class ProcWatcherThread;
class Direntry;

class ProcWatcher : public QMainWindow {
    Q_OBJECT

public:
    explicit ProcWatcher (QWidget* parent = 0);
    ~ProcWatcher ();

    void initTree ();

private slots:
    void on_procTreeView_doubleClicked (const QModelIndex& index);
    void onTimer ();
    void saveHorizontalScrollBarValue (int value);
    void saveVerticalScrollBarValue (int value);
    void on_actionStop_triggered ();
    void on_actionSet_Interval_triggered ();
    void on_actionFind_Process_ID_triggered ();
    void treeExpanded (const QModelIndex& index);
    void on_actionAbout_triggered ();
    void setTimerState ();
    void updateModel (Direntry*);
    void whenActivated (const QModelIndex& index);
    void contextMenuEvent (const QPoint& pos);
private:
    Ui::ProcWatcher* ui;

    ProcFsModel* procModel;
    ProcWatcherThread* watcherThread;

    QFile* current_file;
    QTimer* timer;
    int lastVerticalScrollBarPos;
    int lastHorizontalScrollBarPos;
    int timer_interval;
    bool timer_state;
    int m_activated_row;

    void writeInfo (QFileInfo& info, bool clear = true);
    void searchForProc (QString name);
    void setTimer (bool on);

protected:

};

#endif // PROCWATCHER_H

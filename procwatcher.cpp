#include "procwatcher.h"
#include "ui_procwatcher.h"

#include <QDir>
#include <QFileSystemModel>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>
#include <QScrollBar>
#include <QInputDialog>
#include <dirent.h>
#include <cstring>
#include <sstream>

#include "procfs.h"
#include "procfsmodel.h"
#include "procwatcherthread.h"

ProcWatcher::ProcWatcher (QWidget* parent) :
    QMainWindow (parent),
    ui (new Ui::ProcWatcher),
    current_file (0),
    lastVerticalScrollBarPos (0),
    lastHorizontalScrollBarPos (0),
    timer_interval (100),
    timer_state (false),
    m_activated_row (0) {

    ui->setupUi (this);

    procModel = new ProcFsModel;
    watcherThread = new ProcWatcherThread;
    watcherThread->init (procModel->getFs ());
    watcherThread->start ();

    timer = new QTimer;

    connect (timer, SIGNAL (timeout ()), this, SLOT (onTimer ()));

    ui->procText->verticalScrollBar ()->connect (
        ui->procText->verticalScrollBar (), SIGNAL (valueChanged (int)),
        this, SLOT (saveVerticalScrollBarValue (int)));

    ui->procText->horizontalScrollBar ()->connect (
        ui->procText->horizontalScrollBar (), SIGNAL (valueChanged (int)),
        this, SLOT (saveHorizontalScrollBarValue (int)));

    ui->procText->setContextMenuPolicy (Qt::CustomContextMenu);
    connect (ui->procTreeView, SIGNAL (expanded (const QModelIndex&)), this, SLOT (treeExpanded (const QModelIndex&)));
    connect (ui->procTreeView, SIGNAL (activated (const QModelIndex&)), this, SLOT (whenActivated (const QModelIndex&)));
    connect (ui->procText, SIGNAL (customContextMenuRequested (const QPoint&)), this, SLOT (contextMenuEvent (const QPoint&)));
    connect (watcherThread, SIGNAL (modelChanged (Direntry*)), this, SLOT (updateModel (Direntry*)));
}

void ProcWatcher::initTree () {
    QString procDir ("/proc");

    ui->procTreeView->setModel (procModel);
    ui->procTreeView->setRootIndex (procModel->rootIndex ());
}

ProcWatcher::~ProcWatcher () {
    if (current_file) {
        setTimer (false);
        current_file->close ();
        delete current_file;
    }

    watcherThread->resume ();
    watcherThread->stop ();

    delete watcherThread;
    delete procModel;
    delete timer;

    delete ui;
}

void ProcWatcher::whenActivated (const QModelIndex& index) {
    //std::cout << "activated " << index.row () << std::endl;
    m_activated_row = index.row ();
}

void ProcWatcher::updateModel (Direntry* entry) {
    watcherThread->pause ();
    procModel->update (entry);
    watcherThread->resume ();
}

void ProcWatcher::on_procTreeView_doubleClicked (const QModelIndex& index) {
    setTimer (false);

    QFileInfo fi = procModel->fileInfo (index);
    writeInfo (fi);

    if (fi.isFile () && fi.isReadable ()) {
        if (current_file) {
            current_file->close ();
            delete current_file;
        }

        current_file = new QFile (fi.filePath ());
        if (!current_file->open (QIODevice::ReadOnly)) {
            QMessageBox::critical (this, tr ("Error"), tr ("Could not open file"));
            return;
        }

        QTextStream in (current_file);
        ui->procText->setPlainText (in.readAll ());

        setTimer (true);
        ui->actionStop->setEnabled (true);

    } else {
        ui->procText->setPlainText ("");
        if (!fi.isReadable ()) {
            ui->fileInfoText->appendPlainText (tr ("File Not Readable"));
        } else {
            ui->fileInfoText->appendPlainText (tr ("Not Regular File"));
        }
    }
}

void ProcWatcher::writeInfo (QFileInfo& info, bool clear) {
    if (clear) {
        ui->fileInfoText->setPlainText ("*****************" + info.filePath () + "*****************");
    }

    QFile::Permissions perms = info.permissions ();
    QString permstr;

    if (perms & QFile::ReadOwner) {
        permstr += "r";
    } else {
        permstr += "-";
    }

    if (perms & QFile::WriteOwner) {
        permstr += "w";
    } else {
        permstr += "-";
    }

    if (perms & QFile::ExeOwner) {
        permstr += "x";
    } else {
        permstr += "-";
    }

    if (perms & QFile::ReadGroup) {
        permstr += "r";
    } else {
        permstr += "-";
    }

    if (perms & QFile::WriteGroup) {
        permstr += "w";
    } else {
        permstr += "-";
    }

    if (perms & QFile::ExeGroup) {
        permstr += "x";
    } else {
        permstr += "-";
    }

    if (perms & QFile::ReadOther) {
        permstr += "r";
    } else {
        permstr += "-";
    }

    if (perms & QFile::WriteOther) {
        permstr += "w";
    } else {
        permstr += "-";
    }

    if (perms & QFile::ExeOther) {
        permstr += "x";
    } else {
        permstr += "-";
    }


    ui->fileInfoText->appendPlainText ("Permissions  : " + permstr);

}

void ProcWatcher::onTimer () {
    current_file->seek (0);
    int tmpvs = lastVerticalScrollBarPos;
    int tmphs = lastHorizontalScrollBarPos;

    QTextStream in (current_file);
    ui->procText->setPlainText (in.readAll ());
    ui->procText->verticalScrollBar ()->setValue (tmpvs);
    ui->procText->horizontalScrollBar ()->setValue (tmphs);
}

void ProcWatcher::saveVerticalScrollBarValue (int value) {
    lastVerticalScrollBarPos = ui->procText->verticalScrollBar ()->value ();
}

void ProcWatcher::saveHorizontalScrollBarValue (int value) {
    lastHorizontalScrollBarPos = ui->procText->horizontalScrollBar ()->value ();
}

void ProcWatcher::on_actionStop_triggered () {
    QString txt = ui->actionStop->text ();
    if (txt == "Start") {
        setTimer (true);
    } else {
        setTimer (false);
    }
}


void ProcWatcher::on_actionSet_Interval_triggered () {
    bool ok;
    int val = QInputDialog::getInt (this, tr ("Update Interval"),
                                    tr ("Interval (ms):"), timer_interval, 100, 10000, 100, &ok);
    if (ok) {
        timer_interval = val;
    }
}

void ProcWatcher::on_actionFind_Process_ID_triggered () {
    bool ok;
    QString text = QInputDialog::getText (this, tr ("Find Process Id"),
                                          tr ("Process name:"), QLineEdit::Normal,
                                          "", &ok);
    if (ok && !text.isEmpty ()) {
        searchForProc (text);
    }
}

void ProcWatcher::treeExpanded (const QModelIndex& index) {
    QFileInfo fi = procModel->fileInfo (index);

    if (!fi.isReadable ()) {
        writeInfo (fi, false);
        ui->fileInfoText->appendPlainText (tr ("Directory \"") + fi.filePath () + tr ("\" Not Readable"));
    }
}

void ProcWatcher::searchForProc (QString name) {
    DIR* dirp = opendir ("/proc");

    if (dirp == 0) {
        ui->fileInfoText->appendPlainText ("Unexpected error couldn't open /proc");
    }

    struct dirent* direntry;

    ui->fileInfoText->appendPlainText ("********* Searching for " + name);
    bool not_found = true;
    while ((direntry = readdir (dirp)) != 0) {
        if (direntry->d_type == DT_DIR && (strcmp (direntry->d_name, ".") != 0)) {

            QString process ("/proc/");
            process.append (direntry->d_name);
            QString stat (process);
            stat.append ("/stat");

            QFile f (stat);
            if (f.open (QIODevice::ReadOnly)) {
                QString line = f.readLine ();

                if (line.contains (name)) {
                    not_found = false;
                    ui->fileInfoText->appendPlainText ("Found: " + process);
                    QModelIndex ind = procModel->index (process);
                    ui->procTreeView->setExpanded (ind, true);
                }
            }

            f.close ();
        }
    }

    if (not_found) {
        ui->fileInfoText->appendPlainText ("Not found");
    }

    closedir (dirp);
}

void ProcWatcher::on_actionAbout_triggered () {
    QMessageBox::about (this, "About ProcWatcher" , "Copyright G.Martin 2014\nSoftSprocket\nhttp://www.softsprocket.com");
}

void ProcWatcher::contextMenuEvent (const QPoint& pos) {
    QMenu* menu = ui->procText->createStandardContextMenu ();
    menu->addAction (ui->actionStop);
    menu->exec (ui->procText->mapToGlobal (pos));
    delete menu;
}

void ProcWatcher::setTimerState () {
    if (timer_state) {
        setTimer (false);
    } else {
        setTimer (true);
    }
}

void ProcWatcher::setTimer (bool on) {
    if (on) {
        timer->start (timer_interval);
        timer_state = true;
        ui->actionStop->setText ("Stop");

        std::ostringstream s;
        s << "Running Interval: " << timer_interval << " ms.";

        ui->statusBar->showMessage (s.str ().c_str ());
    } else {
        timer->stop ();
        timer_state = false;
        ui->actionStop->setText ("Start");
        ui->statusBar->showMessage ("Stopped");
    }
}


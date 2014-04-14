#ifndef PROCFSICONS_H
#define PROCFSICONS_H

class QIcon;

class ProcFsIcons {
    QIcon* m_character;
    QIcon* m_socket;
    QIcon* m_fifo;
    QIcon* m_block;
    QIcon* m_link;
    QIcon* m_unknown;
public:
    ProcFsIcons ();
    ~ProcFsIcons ();

    QIcon* get (int type);
};

#endif // PROCFSICONS_H

#include "procfsicons.h"

#include <QIcon>
#include <QPixmap>
#include <dirent.h>

/* <width/cols> <height/rows> <colors> <char on pixel>*/
static const char* cd_icon[] = {
    "16 16 8 1",
    "    c None s None",
    ".   c #808080",
    "X   c #FFFF00",
    "o   c #c0c0c0",
    "O   c black",
    "+   c #00FFFF",
    "@   c #00FF00",
    "#   c white",
    "     .....      ",
    "   ..XXoooOO    ",
    "  .+XXXoooooO   ",
    " .@++XXoooo#oO  ",
    " .@@+XXooo#ooO  ",
    ".oo@@+Xoo#ooooO ",
    ".ooo@+.O.oooooO ",
    ".oooo@O#OoooooO ",
    ".oooo#.O.+ooooO ",
    ".ooo#oo#@X+oooO ",
    " .o#oooo@X++oO  ",
    " .#ooooo@XX++O  ",
    "  .ooooo@@XXO   ",
    "   ..ooo@@OO    ",
    "     ..OOO      ",
    "                "
};

static const char* unknown_icon[] = {
    "16 16 2 1",
    "    c None s None",
    "0   c black",
    "     000000     ",
    "   0000  000    ",
    "  000     000   ",
    " 000       000  ",
    "           000  ",
    "           000  ",
    "          000   ",
    "         000    ",
    "        000     ",
    "       000      ",
    "      000       ",
    "      000       ",
    "                ",
    "      000       ",
    "      000       ",
    "                "
};

static const char* link_icon[] = {
    "16 16 2 1",
    "    c None s None",
    "0   c black",
    "                ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   00000000000  ",
    "   00000000000  ",
    "   00000000000  ",
    "                "
};

static const char* block_icon[] = {
    "16 16 2 1",
    "    c None s None",
    "0   c black",
    "   00000000     ",
    "   000000000    ",
    "   000    000   ",
    "   000    0000  ",
    "   000    0000  ",
    "   000    000   ",
    "   0000000      ",
    "   000    000   ",
    "   000     000  ",
    "   000     000  ",
    "   000     000  ",
    "   000     000   ",
    "   00000000000  ",
    "   00000000000  ",
    "   000000000    ",
    "                "
};

static const char* fifo_icon[] = {
    "16 16 2 1",
    "    c None s None",
    "0   c black",
    "                ",
    "   00000000000  ",
    "   00000000000  ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   000000       ",
    "   000000       ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   000          ",
    "                "
};

static const char* sock_icon[] = {
    "16 16 2 1",
    "    c None s None",
    "0   c black",
    "                ",
    "     00000000   ",
    "    0000000000  ",
    "   0000    000  ",
    "   000          ",
    "   000          ",
    "    000         ",
    "     000        ",
    "      000       ",
    "        000     ",
    "          000   ",
    "           000  ",
    "   0000    000  ",
    "    0000000000  ",
    "     00000000   ",
    "                "
};

static const char* chr_icon[] = {
    "16 16 2 1",
    "    c None s None",
    "0   c black",
    "                ",
    "     00000000   ",
    "    0000000000  ",
    "   0000    000  ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   000          ",
    "   0000    000  ",
    "    0000000000  ",
    "     00000000   ",
    "                "
};

ProcFsIcons::ProcFsIcons () {
    m_character = new QIcon (QPixmap (chr_icon));
    m_socket = new QIcon (QPixmap (sock_icon));
    m_fifo = new QIcon (QPixmap (fifo_icon));
    m_block = new QIcon (QPixmap (block_icon));
    m_link = new QIcon (QPixmap (link_icon));
    m_unknown = new QIcon (QPixmap (unknown_icon));
}

ProcFsIcons::~ProcFsIcons () {
    delete m_character;
    delete m_socket;
    delete m_fifo;
    delete m_block;
    delete m_link;
    delete m_unknown;
}

QIcon* ProcFsIcons::get (int type) {
    switch (type) {
        case DT_BLK:
            return m_block;
        case DT_CHR:
            return m_character;
        case DT_FIFO:
            return m_fifo;
        case DT_LNK:
            return m_link;
        case DT_SOCK:
            return m_socket;
        case DT_UNKNOWN:
            return m_unknown;
        default:
            return NULL;
    };
}


#ifndef  filedialog_INC
#define  filedialog_INC

#include <Magick++.h>
#include <QString>
#include <QStringList>


class LoadFormats
{
 public:
    LoadFormats();
    QString readFilter;
    QStringList readFmts;
    QStringList writeFmts;
};

#endif   /* ----- #ifndef filedialog_INC  ----- */

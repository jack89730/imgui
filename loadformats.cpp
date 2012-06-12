#include "loadformats.h"
using namespace std;
using namespace Magick;

LoadFormats::LoadFormats()
{
    QString readableExts;
    list<CoderInfo> coderList;
    coderInfoList(&coderList,
                  CoderInfo::TrueMatch,
                  CoderInfo::AnyMatch,
                  CoderInfo::AnyMatch);

    list<CoderInfo>::iterator entry = coderList.begin();

    while (entry != coderList.end()) {
        // TODO: Mettere una lista con tutti i formati!!!

        if (entry->isReadable()) {
            readFilter += QString(";;%3 [*.%1] (*.%1 *.%2 )")
                          .arg(QString::fromStdString(entry->name()).toLower())   // Lower and upper filters for gnome compatibility (?)
                          .arg(QString::fromStdString(entry->name()))
                          .arg(QString::fromStdString(entry->description()));

            QString origFmts = QString("*.%1").arg(QString::fromStdString(entry->name()));
            readFmts << origFmts;

            readableExts += QString("*.%1 *.%2 ")
                            .arg(QString::fromStdString(entry->name()).toLower())
                            .arg(QString::fromStdString(entry->name()));
        }

        if (entry->isWritable())
            writeFmts << QString("%1 - (%2)")
                      .arg(QString::fromStdString(entry->name()))
                      .arg(QString::fromStdString(entry->description()));
        entry++;
    }
    readFilter.prepend(QString("All Supported Formats (%1)").arg(readableExts));
}

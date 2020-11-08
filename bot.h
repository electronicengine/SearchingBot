#ifndef BOT_H
#define BOT_H

#include <QString>
#include <vector>


#include "logview.h"

class Bot
{
public:
    Bot(LogView *Log);
    void searchPrefix(QString &Content, QString &Prefix, QString &BanPrefix);

private:
    LogView *Log_;
    std::vector<std::pair<QString, QString>> Begin_End_Prefixes;
    std::vector<std::pair<QString, char>> Prefix_Pieces;
    QString Ban_Prefix;

    int parsePrefix(QString &Prefix);
    int makeBeginPrefix(QString &Content);
    int makeEndPrefix(QString &Content);
    int deleteBanPrefix(QString &Content);
    QString findInvalidPrefixText(int Index, QString &Content);
    QString findCloserPrefix(const char &Prefix);



};


#endif // BOT_H
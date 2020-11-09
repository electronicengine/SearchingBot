#ifndef BOT_H
#define BOT_H

#include <QString>
#include <vector>


#include "logview.h"

class Bot
{
public:
    Bot();
    void searchPrefix(QString &Content, QString &Prefix, QString &BanPrefix, QStringList &ResultList);
    int searchText(QString &Content, std::vector<QString> &Prefixes, std::vector<QString> &Ban_Prefix,
                    std::vector<QStringList> &ResultList);

private:
    std::vector<std::pair<QString, char>> Prefix_Pieces;
    QString Ban_Prefix;

    int parsePrefix(QString &Prefix);
    int makeBeginPrefix(QString &Content);
    int makeEndPrefix(QString &Content);
    int deleteBanPrefix(QString &Content);
    QString findInvalidPrefixText(int Index, QString &Content);
    QString findCloserPrefix(const char &Prefix);
    QStringList *Founded_Words;


   /*********************************************************************************/
    QString Current_Search_Text;
    QStringList Complete_Search_Texts;
    std::vector<QString> New_Created_Prefixes;
    std::vector<QString> Variable_Prefixes;
    std::vector<QStringList> Variable_Texts;
    int Current_Prefix_Number;


    int defineTextVariables(std::vector<QString>Search_Prefixes);
    void searchCompleteText();
    void makeMainPrefixSearch(QString &Content, QString &Main_Prefix, QString &BanPrefix, QStringList &ResultList);
};


#endif // BOT_H

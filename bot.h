#ifndef BOT_H
#define BOT_H

#include <QString>
#include <vector>


#include "logview.h"

enum SearchMod
{

    variable_search,
    constant_search

};

class Bot
{
public:
    Bot();
    void searchPrefix(QString &Content, QString &Prefix, QStringList &ResultList);
    int searchText(QString &Content, QStringList &Prefixes, QStringList &BanPrefix,
                   std::vector<QStringList> &ResultList);

private:
    std::vector<QString> Variable_Prefixes;
    std::vector<std::pair<QString, char>> Prefix_Pieces;

    QStringList Ban_Prefixes;
    QStringList *Founded_Words;
    QStringList Complete_Search_Texts;
    QString Current_Search_Text;
    int Current_Prefix_Number;
    SearchMod Mode_;

    int defineTextVariables(QStringList Search_Prefixes);
    void makeMainPrefixSearch(QString &Content, QString &Main_Prefix, QStringList &ResultList);
    int parsePrefix(QString &Prefix);
    int makeBeginPrefix(QString &Content);
    int makeEndPrefix(QString &Content);
    int deleteBanPrefix(QString &Content);
    int makeConstantSearch(QString &Content);
    QString findInvalidPrefixText(const QString &Begin, const QString &End, QString &Content);

};


#endif // BOT_H

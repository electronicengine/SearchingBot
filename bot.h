#ifndef BOT_H
#define BOT_H

#include <QString>
#include <vector>


#include "logview.h"

static const QChar INVALID_PREFIX = '*';
static const QChar VALID_PREFIX = '#';
static const QChar SPERATE_PREFIX_OPEN = '{';
static const QChar SPERATE_PREFIX_CLOSE = '}';



enum SearchMod
{

    variable_search,
    constant_search

};



class Bot
{

    public:
        Bot();
        int searchText(QString &Content, QStringList &Prefixes, QStringList &BanPrefix,
                       std::vector<QStringList> &ResultList);

    private:
        QString Open_Sperate_Prefix;
        QString Close_Sperate_Prefix;

        std::vector<QString> Variable_Prefixes;
        std::vector<std::pair<QString, QChar>> Prefix_Pieces;

        QStringList Ban_Prefixes;
        QStringList *Founded_Words;
        QStringList Complete_Search_Texts;
        QString Current_Search_Text;
        int Current_Prefix_Number;
        SearchMod Mode_;

        void searchPrefix(QString &Content, QString &Prefix, QStringList &ResultList);
        int defineTextVariables(QStringList Search_Prefixes);
        void makeMainPrefixSearch(QString &Content, QString &Main_Prefix, QStringList &ResultList);
        int parsePrefix(QString &Prefix, std::vector<std::pair<QString, QChar> > &Parsed);
        void checkSperatePrefix(QStringList &Prefix, QString  &Content);
        void cutContentFromOpenSperate(QString &OpenSperatePrefix, QString  &Content);
        void cutContentFromCloseSperate(QString &CloseSperatePrefix, QString  &Content);
        QString complateSearchPrefix(QStringList &PrefixPieces, QString &Content);
        int makeBeginPrefix(QString &Content);
        int makeEndPrefix(QString &BeginPrefix, QString &Content);
        int deleteBanPrefix(QString &Content);
        int makeConstantSearch(QString &Content);
        QString findInvalidPrefixText(const QString &Begin, const QString &End, QString &Content);

};


#endif // BOT_H

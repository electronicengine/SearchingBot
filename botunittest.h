#ifndef BOTUNITTEST_H
#define BOTUNITTEST_H


#include "bot.h"

class BotUnitTest
{


    QString readInputTest();

    QStringList Test_Results;

public:
    BotUnitTest();

    int checkTestResult(std::vector<QStringList> AnswersKeys, std::vector<QStringList> ResultList);
    void createTestCase(QStringList &&SearchPrefixes, QStringList &&BanList, std::vector<QStringList> &&AnswerKey);
    void printTotalResults();
    void testOldCases();

};

#endif // BOTUNITTEST_H

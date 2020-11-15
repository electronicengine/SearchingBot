#include "botunittest.h"
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <iostream>
#include <loging.h>


BotUnitTest::BotUnitTest()
{

    testOldCases();
    printTotalResults();

}



int BotUnitTest::checkTestResult(std::vector<QStringList> AnswersKeys, std::vector<QStringList> ResultList)
{

    if(ResultList.size() != AnswersKeys.size())
    {
        Loging::printAll(Loging::red, "Test Failed");
        Test_Results.push_back("Test Failed");
        return -1;
    }

    for(int i=0; i<(int)AnswersKeys.size(); i++)
    {
        if(AnswersKeys[i].size() != ResultList[i].size())
        {
            Loging::printAll(Loging::red, "Test Failed");
            Test_Results.push_back("Test Failed");

            return -1;
        }

        for(int k = 0; k<AnswersKeys[i].size(); k++)
        {

            if(AnswersKeys[i].at(k) != ResultList[i].at(k))
            {
                Loging::printAll(Loging::red, "Test Failed");
                Test_Results.push_back("Test Failed");

                return -1;
            }

        }
    }

    Loging::printAll(Loging::green, "Test Passed");
    Test_Results.push_back("Test Passed");

    return 0;

}



void BotUnitTest::createTestCase(QStringList &&SearchPrefixes, QStringList &&BanList, std::vector<QStringList> &&AnswerKey)
{

    Bot bot;

    QString test_content;
    std::vector<QStringList> result_list;

    test_content = readInputTest();

    Loging::printAll(Loging::white, test_content.toStdString());

    foreach (QString Prefix, SearchPrefixes)
    {
        result_list.push_back(QStringList());
    }


    bot.searchText(test_content, SearchPrefixes, BanList, result_list);
    checkTestResult(AnswerKey, result_list);

    Loging::printAll(Loging::magenta, "Total Result Table: ");

    for(int k = 0; k < (int)result_list[0].size(); k++)
    {
        for(int i = 0; i< (int) result_list.size(); i++)
        {
            if(result_list.at(i).size() >= k)
                Loging::printAll(Loging::magenta, result_list.at(i).at(k).toStdString() + "\t||\t");
        }
        Loging::printAll(Loging::magenta,  "\n");
    }
}



void BotUnitTest::printTotalResults()
{

    Loging::printAll(Loging::white, "Overal Test Result");

    foreach (QString result, Test_Results)
    {
        if(result == "Test Passed")
            Loging::printAll(Loging::green, "Test Passed");
        else
            Loging::printAll(Loging::red, "Test Failed");

    }
}



void BotUnitTest::testOldCases()
{

    Loging::disableLogs();

    createTestCase({"ac*sis"}, {"<span*</span>"}, {{"acanthosis"}});
    createTestCase({"*antho*"},{"<span*</span>"},
                   {{"href=\"https://www.mayoclinic.org/diseases-conditions/acanthosis-nigricans/symptoms-causes/syc-20368983\">Acanthosis"}});

    createTestCase({"sis*"}, {"<span*</span>"}, {{"sis-nigricans/symptoms-causes/syc-20368983\">Acanthosis"}});
    createTestCase({"<a href=\"https://www.mayoclinic.org/diseases-conditions*syc*>#1</a>"},
                   {"<span*</span>"},
                   {{"Separated shoulder",
                    "Acanthosis nigricans",
                    "Achalasia",
                    "Achilles tendinitis",
                    "Achilles tendon rupture"}});

    createTestCase({"<a href=\"https://www.mayoclinic.org/diseases-conditions*syc*>#1</a>"},
                   {"<span*myc*</span>"},
                   {{"Separated shoulder",
                    "Acanthosis nigricans",
                    "Achalasia",
                    "Achilles tendinitis",
                    "Achilles tendon rupture"}});

    createTestCase({"<a href=\"https://www.mayoclinic.org/diseases-conditions*syc*>#1</a>"},
                   {"<span*myc*joint*</*>"},
                   {{"Separated shoulder",
                    "Acanthosis nigricans",
                    "Achalasia",
                    "Achilles tendinitis",
                    "Achilles tendon rupture"}});

    createTestCase({"<a href=\"https://www.mayoclinic.org/diseases-conditions*syc*>#1</a>"},
                   {"*visual*"},
                   {{"<span joint separation, also known as</span>Separated shoulder",
                    "Acanthosis nigricans",
                    "Achalasia",
                    "Achilles tendinitis",
                    "Achilles tendon rupture"}});

    createTestCase({"*a href=\"https://www.mayoclinic.org/diseases-conditions*syc*>#1</a*"},
                   {"<span*</span>"},
                   {{"Separated shoulder",
                    "Acanthosis nigricans",
                    "Achalasia",
                    "Achilles tendinitis",
                    "Achilles tendon rupture"}});


    createTestCase({"*a href=\"https://www.mayoclinic.org/diseases-conditions*syc*>#1</a*",
                   "<a href=\"#2>#1</a>"},
                   {"<span*</span>"},
                   {{"Separated shoulder",
                     "Acanthosis nigricans",
                     "Achalasia",
                     "Achilles tendinitis",
                     "Achilles tendon rupture"},

                    {"https://www.mayoclinic.org/diseases-conditions/separated-shoulder/symptoms-causes/syc-20354049\"",
                     "https://www.mayoclinic.org/diseases-conditions/acanthosis-nigricans/symptoms-causes/syc-20368983\"",
                     "https://www.mayoclinic.org/diseases-conditions/achalasia/symptoms-causes/syc-20352850\"",
                     "https://www.mayoclinic.org/diseases-conditions/achilles-tendinitis/symptoms-causes/syc-20369020\"",
                     "https://www.mayoclinic.org/diseases-conditions/achilles-tendon-rupture/symptoms-causes/syc-20353234\""}});


    createTestCase({"*a href=\"https://www.mayoclinic.org/diseases-conditions*syc*>#1</a*",
                   "<a href=\"#2>#1</a>",
                   "<a#3=\"#2>#1</a>"},
                   {"<span*</span>"},
                   {{"Separated shoulder",
                     "Acanthosis nigricans",
                     "Achalasia",
                     "Achilles tendinitis",
                     "Achilles tendon rupture"},

                    {"https://www.mayoclinic.org/diseases-conditions/separated-shoulder/symptoms-causes/syc-20354049\"",
                     "https://www.mayoclinic.org/diseases-conditions/acanthosis-nigricans/symptoms-causes/syc-20368983\"",
                     "https://www.mayoclinic.org/diseases-conditions/achalasia/symptoms-causes/syc-20352850\"",
                     "https://www.mayoclinic.org/diseases-conditions/achilles-tendinitis/symptoms-causes/syc-20369020\"",
                     "https://www.mayoclinic.org/diseases-conditions/achilles-tendon-rupture/symptoms-causes/syc-20353234\""},

                   {" href",
                    " href",
                    " href",
                    " href",
                    " href"}});

    createTestCase({"<a href=\"https://*/diseases-conditions/achalasia/symptoms-causes/syc-20352850\">#1"},
                   {"<span*</span>"},
                   {{"Achalasia</a>"}});

    createTestCase({"#1 href=\"https://*/diseases-conditions/achalasia/symptoms-causes/syc-20352850\">Achalasia</a>"},
                   {"<span*</span>"},
                   {{"<a"}});

    createTestCase({"*a href=\"https://www.mayoclinic.org/diseases-conditions*syc*>#1<*>"},
                   {"<span*</span>"},
                   {{"Acanthosis nigricans",
                     "Achalasia",
                     "Achilles tendinitis",
                     "Achilles tendon rupture"}});

    createTestCase({"*n Sperate Prefix{<a href=\"https://www.mayoclinic.org/diseases-conditions*syc*>#1</a>}Close Sperate *"},
                   {"<span*myc*</span>"},
                   {{"Acanthosis nigricans",
                    "Achalasia",
                    "Achilles tendinitis"}});

    createTestCase({"Open*Prefix{<a href=\"https://www.mayoclinic.org/diseases-conditions*syc*>#1</a>}Close Sperate Prefix"},
                   {"<span*myc*</span>"},
                   {{"Acanthosis nigricans",
                    "Achalasia",
                    "Achilles tendinitis"}});

    createTestCase({"Open Sperate Prefix{<a href=\"https://www.mayoclinic.org/diseases-conditions*syc*>#1</a>}Close Sperate Prefix"},
                   {"<span*myc*</span>"},
                   {{"Acanthosis nigricans",
                    "Achalasia",
                    "Achilles tendinitis"}});

    createTestCase({"Open Sperate Prefix{<a href=\"https://www.mayoclinic.org/diseases-conditions*syc*>#1</a>}Close Sperate Prefix"},
                   {"<span*myc*</span>"},
                   {{"Acanthosis nigricans",
                    "Achalasia",
                    "Achilles tendinitis"}});

    createTestCase({"Open Sperate Prefix{<a href=\"https://www.mayoclinic.org/diseases-conditions*syc*>#1</a>"},
                   {"<span*myc*</span>"},
                   {{"Acanthosis nigricans",
                    "Achalasia",
                    "Achilles tendinitis",
                    "Achilles tendon rupture"}});

    createTestCase({"<a href=\"https://www.mayoclinic.org/diseases-conditions*syc*>#1</a>}Close Sperate Prefix"},
                   {"<span*myc*</span>"},
                   {{"Separated shoulder",
                     "Acanthosis nigricans",
                     "Achalasia",
                     "Achilles tendinitis"}});

    Loging::enableLogs();
}



QString BotUnitTest::readInputTest()
{

    QString writable = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    Loging::printAll(Loging::red,"test path" ,writable.toStdString() +"/SearchingBot/test");

    QFile inputFile(writable + "/SearchingBot/test");
    QString test_input;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          test_input.append(in.readLine());
       }
       inputFile.close();
    }

    return test_input;

}

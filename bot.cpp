#include "bot.h"
#include "loging.h"
#include <iostream>

Bot::Bot(){}



void Bot::searchPrefix(QString &Content, QString &Prefix, QStringList &ResultList)
{

    Founded_Words = &ResultList;

    parsePrefix(Prefix, Prefix_Pieces);

    Mode_ = constant_search;

    Loging::printAll(Loging::yellow, "Prefix Pieces:");

    for(int i=0; i<(int)Prefix_Pieces.size(); i++)
    {
        if(Prefix_Pieces[i].second == VALID_PREFIX)
            Mode_ = variable_search;

        Loging::printAll(Loging::yellow, i, ": ", Prefix_Pieces[i].first.toStdString());

    }

    if(Mode_ == variable_search)
        Loging::printAll(Loging::magenta, "This search is variable_search");
    else
        Loging::printAll(Loging::magenta, "This search is constant_search");


    if(Mode_ == variable_search)
        makeBeginPrefix(Content);
    else
        makeConstantSearch(Content);

}



int Bot::searchText(QString &Content, QStringList &Prefixes, QStringList &BanPrefix,
                     std::vector<QStringList> &ResultList)
{

    int res;

    if(Prefixes.size() <= 0) return -1;

    checkSperatePrefix(Prefixes, Content);

    QString main_prefix = Prefixes[0];

    res = defineTextVariables(Prefixes);
    if(res < 0) return -1;

    Ban_Prefixes = BanPrefix;

    Current_Prefix_Number = 0;
    makeMainPrefixSearch(Content, main_prefix, ResultList[Current_Prefix_Number]);

    Current_Prefix_Number++;
    Loging::printAll(Loging::white, "Prefix Number: ", Prefixes.size());


    if((int)Prefixes.size() <= 1)
        return 0;

    for(int i=1; i<(int)Prefixes.size(); i++)
    {
        QString temp_prefix = Prefixes[i];
        if(temp_prefix.size() <= 2)
            return -1;


        for(int l=0; l < ResultList[0].size(); l++)
        {

            for(int k=0; k < i; k++)
            {
                temp_prefix.replace(Variable_Prefixes[k], ResultList[k].at(l));
                if(Current_Prefix_Number > k+1)
                    temp_prefix.replace(Variable_Prefixes[k+1], ResultList[k+1].at(l));
                else
                    temp_prefix.replace(Variable_Prefixes[k+1], VALID_PREFIX);
            }

            Loging::printAll(Loging::red, "new_prefix: ", temp_prefix.toStdString());

            QString temp_content = Complete_Search_Texts.at(l);

            Prefix_Pieces.clear();
            searchPrefix(temp_content, temp_prefix, ResultList[Current_Prefix_Number]);

            Loging::printAll(Loging::white, "Size: ", ResultList[Current_Prefix_Number].size(), " "
                             ,l);

            if(ResultList[Current_Prefix_Number].size() < (l+1))
            {
                for(int m = 0; m <  (l+1) - ResultList[Current_Prefix_Number].size(); m++)
                {
                    ResultList[Current_Prefix_Number].push_back(QString(""));
                }
            }

            Loging::printAll(Loging::green, "newresult: ", ResultList[Current_Prefix_Number].at(l).toStdString());

            temp_prefix = Prefixes[i];

        }

        Loging::printAll(Loging::green, "new_search results: ");

        foreach (QString var, ResultList[Current_Prefix_Number])
        {
            Loging::printAll(Loging::green, var.toStdString());
        }

        Current_Prefix_Number++;
    }

    return 0;
}



int Bot::parsePrefix(QString &Prefix, std::vector<std::pair<QString, QChar>> &Parsed)
{
    Loging::printAll(Loging::yellow, "parsePrefix");
    int invalid_prefix_index = 0;
    int valid_prefix_index = 0;
    int index = 0;

    if(Prefix.size() <= 1)
        return -1;

    //divide prefixes into an pair array to examine pieces
    while(1)
    {
        invalid_prefix_index = Prefix.indexOf(INVALID_PREFIX);
        valid_prefix_index = Prefix.indexOf(VALID_PREFIX);

        if(valid_prefix_index >= 0 || invalid_prefix_index >= 0)
        {

            if(valid_prefix_index < invalid_prefix_index)
            {
                if(valid_prefix_index >= 0)
                    index = valid_prefix_index;
                else
                    index = invalid_prefix_index;
            }
            else if(invalid_prefix_index < valid_prefix_index)
            {
                if(invalid_prefix_index >= 0)
                    index = invalid_prefix_index;
                else
                    index = valid_prefix_index;
            }
            else
            {
                break;
            }

            Loging::printAll(Loging::yellow, "piece: " , Prefix.left(index).toStdString());
            if(index == valid_prefix_index)
            {

                if(index == 0) // if there is nothing before #
                {
                    Loging::printAll(Loging::yellow, "there is nothing before # ");

                    Parsed.push_back(std::make_pair(" ", VALID_PREFIX));
                }
                else if(index == Prefix.size() - 1) // if there is nothing after #
                {
                    Loging::printAll(Loging::yellow, "there is nothing after #");
                    Parsed.push_back(std::make_pair(Prefix.left(index), VALID_PREFIX));

                    Parsed.push_back(std::make_pair(" ", VALID_PREFIX));
                    break;
                }else
                {
                    Parsed.push_back(std::make_pair(Prefix.left(index), VALID_PREFIX));
                }

            }
            if(index == invalid_prefix_index)
            {
                if(index == 0) // if there is nothing before *
                {
                    Loging::printAll(Loging::yellow, "there is nothing before * ");

                    Parsed.push_back(std::make_pair(" ", INVALID_PREFIX));
                }
                else if(index == Prefix.size() -1) // if there is nothing affter *
                {
                    Loging::printAll(Loging::yellow, "there is nothing after *");
                    Parsed.push_back(std::make_pair(Prefix.left(index), INVALID_PREFIX));

                    Parsed.push_back(std::make_pair(" ", '-'));
                    break;
                }
                else
                {
                    Parsed.push_back(std::make_pair(Prefix.left(index), INVALID_PREFIX));
                }

            }

            Prefix = Prefix.mid(index + 1);

        }
        else
        {
            Parsed.push_back(std::make_pair(Prefix, '-'));

            Loging::printAll(Loging::yellow, "last: " , Prefix.toStdString());
            break;
        }
    }



    return 0;

}



void Bot::checkSperatePrefix(QStringList &Prefix, QString  &Content)
{

    for(int i=0; i<Prefix.size(); i++)
    {
        int open_sperated_prefix_index = Prefix[i].indexOf(SPERATE_PREFIX_OPEN);
        int close_sperated_prefix_index = Prefix[i].indexOf(SPERATE_PREFIX_CLOSE);

        if(open_sperated_prefix_index >= 0)
        {
            Open_Sperate_Prefix = Prefix[i].left(open_sperated_prefix_index);

            cutContentFromOpenSperate(Open_Sperate_Prefix, Content);

            Prefix[i].replace(Open_Sperate_Prefix + SPERATE_PREFIX_OPEN, "");
            close_sperated_prefix_index = close_sperated_prefix_index - Open_Sperate_Prefix.size() - 1;

        }

        if(close_sperated_prefix_index >= 0)
        {
            Close_Sperate_Prefix = Prefix[i].mid(close_sperated_prefix_index + 1);

            cutContentFromCloseSperate(Close_Sperate_Prefix, Content);

            Prefix[i].replace(SPERATE_PREFIX_CLOSE + Close_Sperate_Prefix, "");

        }
    }




}



void Bot::cutContentFromOpenSperate(QString &OpenSperatePrefix, QString &Content)
{
    if(OpenSperatePrefix.indexOf(INVALID_PREFIX) >= 0)
    {
        QStringList pieces = OpenSperatePrefix.split(INVALID_PREFIX);
        QString complate_prefix = complateSearchPrefix(pieces, Content);

        int index = Content.indexOf(complate_prefix);

        if(index >= 0)
        {
            Content = Content.mid(index + complate_prefix.size());

        }
    }
    else
    {
        int index = Content.indexOf(OpenSperatePrefix);

        if(index >= 0)
        {
           Content = Content.mid(index + OpenSperatePrefix.size());
        }
    }

}



void Bot::cutContentFromCloseSperate(QString &CloseSperatePrefix, QString &Content)
{
    if(CloseSperatePrefix.indexOf(INVALID_PREFIX) >= 0)
    {
        QStringList pieces = CloseSperatePrefix.split(INVALID_PREFIX);
        QString complate_prefix = complateSearchPrefix(pieces, Content);

        int index = Content.indexOf(complate_prefix);

        if(index >= 0)
        {
            Content = Content.left(index);

        }
    }
    else
    {
        int index = Content.indexOf(CloseSperatePrefix);

        if(index >= 0)
        {
           Content = Content.left(index);
        }
    }
}



QString Bot::complateSearchPrefix(QStringList &PrefixPieces, QString &Content)
{

    QString complete_text;

    complete_text += PrefixPieces.at(0);

    for(int i = 0; i<PrefixPieces.size() - 1; i++)
    {
        QString begin_prefix = PrefixPieces.at(i);
        if(begin_prefix == "")
            begin_prefix = " ";

        QString end_prefix = PrefixPieces.at(i+1);
        if(end_prefix == "")
            end_prefix = " ";

        complete_text += findInvalidPrefixText(begin_prefix, end_prefix, Content);

    }

    return complete_text;


}



int Bot::makeBeginPrefix(QString &Content)
{
    QString begin_prefix;
    int begin_prefix_index;
    int initial_search_index;

    if(Prefix_Pieces.size() <= 0)
        return -1;

    while(1)
    {


        //search first prefix
        initial_search_index = Content.indexOf(Prefix_Pieces[0].first);
        if(initial_search_index < 0)
            return 0;

        // add first piece of prefix to begin prefix
        begin_prefix += Prefix_Pieces[0].first;

        for(int i=0; i< (int)Prefix_Pieces.size(); i++)
        {
            //create begin prefix until variable prefix
             if(Prefix_Pieces[i].second == INVALID_PREFIX)
             {
                 begin_prefix += findInvalidPrefixText(Prefix_Pieces[i].first, Prefix_Pieces[i+1].first, Content);
                 Loging::printAll(Loging::cyan, "Begin Piece: " , begin_prefix.toStdString());
             }
             else if(Prefix_Pieces[i].second == VALID_PREFIX)
             {
                break;
             }
        }

        //if begin prefix is empty
        if(!(Prefix_Pieces[0].second == VALID_PREFIX && Prefix_Pieces[0].first == " "))
        {
            if(begin_prefix == " " || begin_prefix == "")
            {
                break;
            }
        }

        if(Prefix_Pieces[Prefix_Pieces.size() - 1].second == VALID_PREFIX && begin_prefix == Prefix_Pieces[0].first)
            break;


        Loging::printAll(Loging::cyan, " ************************");
        Loging::printAll(Loging::cyan, "Begin Prefix: " , begin_prefix.toStdString());
        Loging::printAll(Loging::cyan, " ************************");
        Current_Search_Text = begin_prefix;

        //cut off content until known valid begin prefix
        begin_prefix_index = Content.indexOf(begin_prefix);
        Content = Content.mid(begin_prefix_index + begin_prefix.size());

        Loging::printAll(Loging::white, "Cont: " , Content.toStdString());


        bool correct_prefix = true;


        //check if begin prefix is including all prefix pieces
        for(int i=0; i<(int)Prefix_Pieces.size(); i++)
        {
            if(Prefix_Pieces[i].second == VALID_PREFIX)
                break;

            if(begin_prefix.indexOf(Prefix_Pieces[i].first) < 0 &&
                    !(begin_prefix == " " || begin_prefix == ""))
            {
                correct_prefix = false;
            }
        }

        if(correct_prefix == false)
            break;

        //find the end prefix
        makeEndPrefix(begin_prefix, Content);

        begin_prefix.clear();

    }

    return 0;
}



int Bot::makeEndPrefix(QString &BeginPrefix, QString &Content)
{

    QString searched_text;
    QString end_prefix;
    int initial_search_index;

    Loging::printAll(Loging::blue, "Last Prefix Piece: ", Prefix_Pieces[Prefix_Pieces.size() - 1].first.toStdString());
    //find the last piece of prefix
    initial_search_index = Content.indexOf(Prefix_Pieces[Prefix_Pieces.size() - 1].first); // last piece of prefix

    if(initial_search_index < 0)
        return 0;

    for(int i=Prefix_Pieces.size() - 1; i >= 0; i--)
    {

        //create end prefix until variable prefix with reverse of prefixes
         if(Prefix_Pieces[i].second == INVALID_PREFIX)
         {
             end_prefix += Prefix_Pieces[i].first;
             end_prefix += findInvalidPrefixText(Prefix_Pieces[i].first, Prefix_Pieces[i+1].first, Content);

         }
         else if(Prefix_Pieces[i].second == VALID_PREFIX)
         {
             if(i == (int)Prefix_Pieces.size() - 1) // if there is no * after #, include the last known prefix to the end prefix
             {
                 if(Prefix_Pieces[Prefix_Pieces.size() - 1].first == "")
                     Prefix_Pieces[Prefix_Pieces.size() - 1].first = " ";

                 end_prefix = Prefix_Pieces[Prefix_Pieces.size() - 1].first;

             }
             break;
         }
    }

    // add last piece of prefix to the end of end prefix
    if(end_prefix.indexOf(Prefix_Pieces[Prefix_Pieces.size() - 1].first) < 0)
        end_prefix += Prefix_Pieces[Prefix_Pieces.size() - 1].first;

    Loging::printAll(Loging::cyan, " -----------------------");
    Loging::printAll(Loging::cyan, "End Prefix: " , end_prefix.toStdString());
    Loging::printAll(Loging::cyan, " -----------------------");

    if(Prefix_Pieces[0].first == " " && Prefix_Pieces[0].second == VALID_PREFIX)
    {
        searched_text = findInvalidPrefixText(BeginPrefix, end_prefix, Content);
        searched_text = searched_text.left(searched_text.indexOf(end_prefix));
    }
    else
    {
        searched_text = Content.left(Content.indexOf(end_prefix));
    }


    //check all prefix pieces is including
    for(int i=Prefix_Pieces.size() - 1; i >= 0; i--)
    {
        if(Prefix_Pieces[i].second == VALID_PREFIX)
            break;

        if(end_prefix.indexOf(Prefix_Pieces[i].first) < 0 &&
                !(end_prefix == " " || end_prefix == ""))
        {
            return -1;
        }
    }


    if(!Ban_Prefixes.empty())
        deleteBanPrefix(searched_text);

    Current_Search_Text += searched_text;
    Current_Search_Text += end_prefix;

    //cut the content
    Content = Content.mid(Content.indexOf(end_prefix) +  + end_prefix.size());
    Loging::printAll(Loging::cyan, "Last Content: ", Content.toStdString());


    if(Current_Prefix_Number == 0)
        Complete_Search_Texts.push_back(Current_Search_Text);


    if(Prefix_Pieces[Prefix_Pieces.size() - 1].first == " ")
        searched_text = searched_text.simplified();

    if(!(searched_text == " " || searched_text == ""))
        Founded_Words->append(searched_text);

    return 0;
}



int Bot::deleteBanPrefix(QString &Content)
{

    printAll(Loging::red, "Dirty Content: ",Content.toStdString());

    for(int i = 0; i<(int)Ban_Prefixes.size(); i++)
    {
        int prefix_piece = Ban_Prefixes[i].indexOf(INVALID_PREFIX);

        if(prefix_piece < 0)
        {
            QString prefix = Ban_Prefixes[i];

            int prefix_index = Content.indexOf(prefix);

            if(prefix_index >= 0)
                Content = Content.replace(prefix, QString(""));

        }
        else
        {
            QStringList prefix_pieces = Ban_Prefixes[i].split(INVALID_PREFIX);

            QString complete_ban_text = complateSearchPrefix(prefix_pieces, Content);

            Loging::printAll(Loging::red, "Complete Ban Text: ", complete_ban_text.toStdString());

            if(Content.indexOf(complete_ban_text) >= 0 )
                Content.replace(complete_ban_text, "");


            Loging::printAll(Loging::yellow, "Cleared Content: ", Content.toStdString());

        }
    }
    return 0;
}



int Bot::makeConstantSearch(QString &Content)
{
    QString searched_text;
    int initial_search_index;

    if(Prefix_Pieces.size() <= 0)
        return -1;

    while(1)
    {
        //search first prefix


        initial_search_index = Content.indexOf(Prefix_Pieces[0].first);
        if(initial_search_index < 0)
            return 0;


        QStringList pieces_list;

        for(int i=0; i< (int)Prefix_Pieces.size(); i++)
        {
            pieces_list.append(Prefix_Pieces[i].first);
        }

        searched_text = complateSearchPrefix(pieces_list, Content);


        //if begin prefix is empty
        if(searched_text == " " || searched_text == "" || searched_text == Prefix_Pieces[0].first ||
                searched_text == Prefix_Pieces[0].first + " ")
        {
            break;
        }

        Loging::printAll(Loging::cyan, " ************************");
        Loging::printAll(Loging::cyan, "Founded Prefix: " , searched_text.toStdString());
        Loging::printAll(Loging::cyan, " ************************");

        //cut off content until known valid begin prefix
        Content = Content.mid(Content.indexOf(searched_text) + searched_text.size());

        if(!Ban_Prefixes.empty())
        {
            deleteBanPrefix(searched_text);
        }

        Loging::printAll(Loging::cyan, "Last Content: ", Content.toStdString());

        if(Current_Prefix_Number == 0)
            Complete_Search_Texts.push_back(searched_text);

        if(Prefix_Pieces[Prefix_Pieces.size() - 1].first == " ")
            searched_text = searched_text.simplified();

        Founded_Words->append(searched_text);

        searched_text.clear();
    }

    return 0;


}



QString Bot::findInvalidPrefixText(const QString &Search_Begin, const QString &Search_End, QString &Content)
{

    QString temp_search_end;
    QString temp_search_begin;
    int search_end_index;
    int search_begin_index;
    temp_search_end = Content;

    int content_search_end_index = 0;

    while(1)
    {
        Loging::printAll(Loging::blue, "search begin: " , Search_Begin.toStdString());
        Loging::printAll(Loging::blue, "search end: " , Search_End.toStdString());

        //find the next valid prefix pos
        search_end_index = temp_search_end.indexOf(Search_End);

        if(search_end_index < 0)
            return QString("");

        //cut the content from end prefix
        temp_search_begin = temp_search_end;

        temp_search_end = temp_search_end.left(search_end_index + Search_End.size());
        Loging::printAll(Loging::white, "temp_search_end: " , temp_search_end.toStdString());
        content_search_end_index += search_end_index + Search_End.size();

        //find the begin prefix in cutted content
        search_begin_index = temp_search_end.indexOf(Search_Begin);

        //if there is no begin prefix, then cut all off
        if(search_begin_index < 0)
        {
            Loging::printAll(Loging::yellow, "Can't find the search begin of end prefix");
            temp_search_end = Content.mid(content_search_end_index);
            Loging::printAll(Loging::white, "cut temp_search_end: " , temp_search_end.toStdString());

            continue;
        }

        // check if there is begin prefix witout end prefix
        int search_begin_size = Search_Begin.size();
        int temp_index;
        QString last_temp;

        last_temp = temp_search_end.mid(search_begin_index + search_begin_size);

        do
        {


            if(temp_search_end.indexOf(Search_End) <= search_begin_index)
                break;

            temp_search_end = temp_search_end.mid(search_begin_index + search_begin_size);

            Loging::printAll(Loging::white, "search_end: " , temp_search_end.toStdString());

            temp_index = temp_search_end.indexOf(Search_Begin);
            if(temp_index >= 0)
            {
                search_begin_index = temp_index;
            }
            else
            {
            }

        }while(temp_index >= 0);


        //check if there is any same end prefix at the total

        if(Search_Begin == " " || Search_End == " ")
            temp_search_end = temp_search_end.simplified();

        int a = last_temp.indexOf(temp_search_end, 0);
        if(a == 0)
            temp_search_end = last_temp.mid(temp_index);



        //extract valid prefix with begin and end prefix
        Loging::printAll(Loging::white, "search_end: " , temp_search_end.toStdString());
        Loging::printAll(Loging::white, "Last-temp: " , last_temp.toStdString());

        return temp_search_end;

    }
}



int Bot::defineTextVariables(QStringList Search_Prefixes)
{

    for(int i = 0; i< (int)Search_Prefixes.size(); i++)
    {
        QString temp_prefix = Search_Prefixes[i];

        for(int k = 0; k<9; k++)
        {
            int index = temp_prefix.indexOf(VALID_PREFIX);
            if(index < 0)
                break;

            if(QString("0123456789").indexOf(QString(temp_prefix[index + 1])) < 0)
            {
                Loging::printAll(Loging::red, "Invalid Prefix!");
                return -1;
            }

            bool exist = false;
            foreach(QString var, Variable_Prefixes)
            {
                if(QString(VALID_PREFIX + temp_prefix[index + 1]) == var)
                    exist = true;
            }

            if(exist == false)
                Variable_Prefixes.push_back(VALID_PREFIX + temp_prefix[index + 1]);

            temp_prefix = temp_prefix.mid(QString(temp_prefix[index + 1]).toInt()+1);

        }
    }


    Loging::printAll(Loging::green, "Variables; ");

    foreach (QString var, Variable_Prefixes)
    {
        Loging::printAll(Loging::green, var.toStdString() );

    }

    return 0;
}



void Bot::makeMainPrefixSearch(QString &Content, QString &Main_Prefix,QStringList &ResultList)
{

    if(Main_Prefix.indexOf(VALID_PREFIX) < 0)
        Mode_ = constant_search;
    else
        Main_Prefix.replace(Variable_Prefixes[0], VALID_PREFIX);

    Loging::printAll(Loging::yellow, "Main Prefix: " , Main_Prefix.toStdString());
    Loging::printAll(Loging::green, "Content : " , Content.toStdString());

    searchPrefix(Content, Main_Prefix, ResultList);

    Loging::printAll(Loging::green, "ResultList : " );

    foreach (QString var, ResultList) {Loging::printAll(Loging::green, var.toStdString());}

    Loging::printAll(Loging::green, "\nComplete_Search_Texts : ");

    foreach (QString var, Complete_Search_Texts){Loging::printAll(Loging::green, var.toStdString());}

}

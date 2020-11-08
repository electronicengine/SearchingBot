#include "bot.h"
#include <iostream>

Bot::Bot()
{
}



void Bot::searchPrefix(QString &Content, QString &Prefix, QString &BanPrefix, QStringList &ResultList)
{

    Founded_Words = &ResultList;

    Ban_Prefix = BanPrefix;

    parsePrefix(Prefix);
    makeBeginPrefix(Content);


}



int Bot::parsePrefix(QString &Prefix)
{
    std::cout << "parsePrefix" << std::endl;
    int invalid_prefix_index = 0;
    int valid_prefix_index = 0;
    int index = 0;


    while(1)
    {
        invalid_prefix_index = Prefix.indexOf('*');
        valid_prefix_index = Prefix.indexOf('#');

        if(valid_prefix_index > 0 || invalid_prefix_index > 0)
        {

            if(valid_prefix_index < invalid_prefix_index)
            {
                if(valid_prefix_index > 0)
                    index = valid_prefix_index;
                else
                    index = invalid_prefix_index;
            }
            else if(invalid_prefix_index < valid_prefix_index)
            {
                if(invalid_prefix_index > 0)
                    index = invalid_prefix_index;
                else
                    index = valid_prefix_index;
            }
            else
            {
                break;
            }

            std::cout << "piece: " << Prefix.left(index).toStdString() << std::endl;
            if(index == valid_prefix_index)
                Prefix_Pieces.push_back(std::make_pair(Prefix.left(index), '#'));
            if(index == invalid_prefix_index)
                Prefix_Pieces.push_back(std::make_pair(Prefix.left(index), '*'));

            Prefix = Prefix.mid(index + 1);

        }
        else
        {
            Prefix_Pieces.push_back(std::make_pair(Prefix, '-'));

            std::cout << "last: " << Prefix.toStdString() << std::endl;
            break;
        }

    }
    return 0;

}



int Bot::makeBeginPrefix(QString &Content)
{
    QString begin_prefix;
    int begin_prefix_index;
    int initial_search_index;

    while(1)
    {

        initial_search_index = Content.indexOf(Prefix_Pieces[0].first);
        if(initial_search_index < 0)
            return 0;

        for(int i=0; i< (int)Prefix_Pieces.size(); i++)
        {
             if(Prefix_Pieces[i].second == '*')
             {
                begin_prefix += Prefix_Pieces[i].first;
                begin_prefix += findInvalidPrefixText(i, Content);

                if(Prefix_Pieces[i + 1].second == '#')
                {
                    begin_prefix += Prefix_Pieces[i + 1].first;
                }
             }
             else if(Prefix_Pieces[i].second == '#')
             {
                if(i == 0) // if there is no * before #
                {
                    begin_prefix = Prefix_Pieces[0].first;

                }

                break;

             }
        }

        std::cout << " ************************" << std::endl;
        std::cout << "Begin Prefix: " << begin_prefix.toStdString() << std::endl;
        std::cout << " ************************" << std::endl;


        begin_prefix_index = Content.indexOf(begin_prefix);
        Content = Content.mid(begin_prefix_index + begin_prefix.size());

        std::cout << "Cont: " << Content.toStdString() << std::endl << std::endl;

        makeEndPrefix(Content);

        begin_prefix.clear();

    }

    return 0;
}



int Bot::makeEndPrefix(QString &Content)
{

    QString searched_text;
    QString end_prefix;
    int initial_search_index;

    initial_search_index = Content.indexOf(Prefix_Pieces[Prefix_Pieces.size() - 1].first); // last piece of prefix

    if(initial_search_index < 0)
        return 0;

    for(int i=Prefix_Pieces.size() - 1; i >= 0; i--)
    {
         if(Prefix_Pieces[i].second == '*')
         {
             end_prefix += Prefix_Pieces[i].first;
             end_prefix += findInvalidPrefixText(i, Content);
         }
         else if(Prefix_Pieces[i].second == '#')
         {

             break;
         }
    }

    end_prefix += Prefix_Pieces[Prefix_Pieces.size() - 1].first;

    std::cout << " -----------------------" << std::endl;
    std::cout << "End Prefix: " << end_prefix.toStdString() << std::endl;
    std::cout << " -----------------------" << std::endl;

    searched_text = Content.left(Content.indexOf(end_prefix));

    if(!Ban_Prefix.isEmpty())
        deleteBanPrefix(searched_text);

    Founded_Words->append(searched_text);

    return 0;
}



int Bot::deleteBanPrefix(QString &Content)
{
    QStringList prefixes = Ban_Prefix.split("*");

    if(prefixes.size() <= 2)
    {

        QString end_prefix = prefixes.at(prefixes.size() - 1);

        int end_index = Content.indexOf(end_prefix);
        if(end_index >= 0)
        {
            Content = Content.mid(end_index + end_prefix.size());
        }
    }


    return 0;
}



QString Bot::findInvalidPrefixText(int Index, QString &Content)
{

    QString temp_search_end;
    QString search_end = Prefix_Pieces[Index+1].first;
    QString search_begin = Prefix_Pieces[Index].first;
    int search_end_index;
    int search_begin_index;

    while(1)
    {
        std::cout << "search begin: " << search_begin.toStdString() << std::endl;
        std::cout << "search end: " << search_end.toStdString() << std::endl;

        search_end_index = Content.indexOf(search_end);

        if(search_end_index < 0)
            return QString("");

        temp_search_end = Content.left(search_end_index);
        std::cout << "temp_search_end: " << temp_search_end.toStdString() << std::endl;

        search_begin_index = temp_search_end.indexOf(search_begin);

        if(search_begin_index < 0)
        {
            std::cout << "search_begin_index < 0!!! "<< std::endl;

            Content = Content.mid(search_end_index + search_end.size());
            continue;
        }

        search_end = temp_search_end.mid(search_begin_index + search_begin.size());
        std::cout << "search_end: " << search_end.toStdString() << std::endl;

        return search_end;

    }

}

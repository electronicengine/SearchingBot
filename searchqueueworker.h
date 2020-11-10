#ifndef SEARCHQUEUEWORKER_H
#define SEARCHQUEUEWORKER_H

#include <QThread>
#include <QRunnable>

#include "searchengine.h"

class SearchQueueWorker : public QRunnable
{

    int Queue_Number;
    SearchEngine Search_Engine;
    std::vector<QStringList> Search_;
    std::vector<QStringList> Search_Result;
    SearchWindow *Return_Object;

public:
    SearchQueueWorker(int QueueNumber, std::vector<QStringList> &Search, SearchWindow *ReturnObj);

    void run();
};

#endif // SEARCHQUEUEWORKER_H

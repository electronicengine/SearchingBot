#ifndef SEARCHQUEUEWORKER_H
#define SEARCHQUEUEWORKER_H

#include <QThread>
#include <QRunnable>

#include "httprequest.h"

class SearchQueueWorker : public QRunnable
{

    int Queue_Number;
    HttpRequest Http_Request;
    std::vector<QString> Search_;
    QStringList Search_Result;
    SearchWindow *Return_Object;

public:
    SearchQueueWorker(int QueueNumber, std::vector<QString> &Search, SearchWindow *ReturnObj);

    void run();
};

#endif // SEARCHQUEUEWORKER_H

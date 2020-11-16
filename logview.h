#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <QMainWindow>

namespace Ui {
class LogView;
}

class LogView : public QWidget
{
    Q_OBJECT

public:
    explicit LogView(QWidget *parent = nullptr);
    ~LogView();

    void appendText(const QString &Txt);
    QString getAllText();
    void openFileCallBack(const QString &Content);
    void clearText();

public slots:
    void databaseButtonClicked();
    void saveButtonClicked();
    void openButtonClicked();
    void clearButtonClicked();
    void appendSlot(const QString &Txt);

signals:
    void appendTextQueue(QString Txt);
    void appendSignal(const QString &Txt);

private:
    Ui::LogView *ui;
};

#endif // LOGVIEW_H

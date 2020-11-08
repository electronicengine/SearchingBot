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
    void saveButtonClicked();
    void openButtonClicked();

private:
    Ui::LogView *ui;
};

#endif // LOGVIEW_H

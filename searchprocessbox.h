#ifndef SEARCHPROCESSBOX_H
#define SEARCHPROCESSBOX_H

#include <QDialog>

namespace Ui {
class SearchProcessBox;
}

class SearchProcessBox : public QDialog
{
    Q_OBJECT

public:
    explicit SearchProcessBox(QWidget *parent = nullptr);
    ~SearchProcessBox();
    void setPersentage(double Persentage);

private:
    Ui::SearchProcessBox *ui;
};

#endif // SEARCHPROCESSBOX_H

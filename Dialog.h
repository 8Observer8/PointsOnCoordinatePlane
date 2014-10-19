#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void slotDrawPlot( const QModelIndex &index1 = QModelIndex(),
                       const QModelIndex &index2 = QModelIndex() );

private:
    Ui::Dialog *ui;
    const int m_nrows;
    const int m_ncols;
    QStandardItemModel m_model;
};

#endif // DIALOG_H

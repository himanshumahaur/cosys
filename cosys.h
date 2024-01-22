#ifndef COSYS_H
#define COSYS_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class cosys; }
QT_END_NAMESPACE

class cosys : public QMainWindow
{
    Q_OBJECT

public:
    cosys(QWidget *parent = nullptr);
    ~cosys();

signals:
    void recvRes(QString cmd);

public slots:
    void onCmd(QString cmd);
    void updatePrg();

private slots:
    void on_BtnExe_clicked();

private:
    Ui::cosys *ui;
    QTimer *timer;
    bool processing;
};
#endif // COSYS_H

#include "cosys.h"
#include "ui_cosys.h"

#include <QRandomGenerator>

cosys::cosys(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cosys)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    processing = false;
    connect(timer, &QTimer::timeout, this, &cosys::updatePrg);
}

cosys::~cosys()
{
    delete ui;
}

void cosys::onCmd(QString cmd)
{
    if(!processing) {
        if(!cmd.size()) {
            emit(recvRes("Invalid!"));
            return;
        }

        processing = true;
        ui->BtnExe->setEnabled(false);

        ui->boxCmd->setText(cmd);
        ui->boxRes->clear();

        ui->barPrg->setValue(0);
        timer->start(100);
    }

}

void cosys::updatePrg()
{
    int cur = ui->barPrg->value();
    int nex = cur + 1;

    if (nex <= 100)
    {
        ui->barPrg->setValue(nex);
    }
    else
    {
        QString res;

        if(QRandomGenerator::global()->generate()%2) {
            res = "Status Ok!";
        }
        else {
            res = "System Error!";
        }
        ui->boxRes->setText(res);

        timer->stop();
        ui->BtnExe->setEnabled(true);
        processing = false;

        emit(recvRes(res));
    }
}

void cosys::on_BtnExe_clicked()
{
    onCmd(ui->lineCmd->text());
    ui->lineCmd->clear();
}


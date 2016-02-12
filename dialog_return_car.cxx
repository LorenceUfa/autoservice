#include "dialog_return_car.hxx"
#include "ui_dialog_return_car.h"

Dialog_Return_Car::Dialog_Return_Car(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog_Return_Car)
{
  ui->setupUi(this);

  QValidator *doubler = new QDoubleValidator(0);

  /* set line "Coast" for only double variables */
  ui->lineCoast->setValidator(doubler);

  /* set lines as non edit */
  ui->lineSurname->setReadOnly(true);
  ui->lineName->setReadOnly(true);
  ui->lineMidName->setReadOnly(true);

  ui->lineBrand->setReadOnly(true);
  ui->lineModel->setReadOnly(true);


  /* set button "OK' enabled if only text is not empty */
  ui->buttonOk->setEnabled(false);

  connect(ui->buttonOk, SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(ui->buttonCancel, SIGNAL(clicked(bool)), this, SLOT(close()));

  connect(ui->lineCoast, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
  connect(ui->lineDescr, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
}

Dialog_Return_Car::~Dialog_Return_Car()
{
  delete ui;
}

void Dialog_Return_Car::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}

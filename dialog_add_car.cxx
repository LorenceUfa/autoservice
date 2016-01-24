#include "dialog_add_car.hxx"
#include "ui_dialog_add_car.h"

Dialog_Add_Car::Dialog_Add_Car(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog_add_car)
{
  ui->setupUi(this);

  QValidator *doubler = new QDoubleValidator(0);

  /* set line "Coast" for only double variables */
  ui->lineCoast->setValidator(doubler);

  /* set button "OK' enabled if only text is not empty */
  ui->buttonOk->setEnabled(false);

  connect(ui->buttonOk, SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(ui->buttonCancel, SIGNAL(clicked(bool)), this, SLOT(close()));

//  connect(ui->comboBox_surname, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
//  connect(ui->comboBox_name, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
//  connect(ui->comboBox_mid_name, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
  connect(ui->lineBrand, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
  connect(ui->lineModel, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
  connect(ui->lineCoast, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
  connect(ui->lineDescr, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));

}

Dialog_Add_Car::~Dialog_Add_Car()
{
  delete ui;
}

void Dialog_Add_Car::changeEvent(QEvent *e)
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

void Dialog_Add_Car::enableButtonOk()
{
  if(/*(!ui->lineSurname->text().isEmpty()) &&
     (!ui->lineName->text().isEmpty()) &&
     (!ui->lineMiddleName->text().isEmpty()) &&*/
     (!ui->lineBrand->text().isEmpty()) &&
     (!ui->lineModel->text().isEmpty()) &&
     (!ui->lineCoast->text().isEmpty()) &&
     (!ui->lineDescr->text().isEmpty())
     )
  {
    ui->buttonOk->setEnabled(true);
  }
  else
  {
    ui->buttonOk->setEnabled(false);
  }
}

#include "dialog_add_owner.hxx"
#include "ui_dialog_add_owner.h"

Dialog_Add_Owner::Dialog_Add_Owner(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog_Add_Owner)
{
  ui->setupUi(this);

  setWindowTitle("Add new owner");

  QValidator *doubler = new QDoubleValidator(0);

  /* set line "Coast" for only double variables */
  ui->lineCoast->setValidator(doubler);

  /* set button "OK' enabled if only text is not empty */
  ui->buttonOk->setEnabled(false);

  connect(ui->buttonOk, SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(ui->buttonCancel, SIGNAL(clicked(bool)), this, SLOT(close()));

  connect(ui->lineSurname, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
  connect(ui->lineName, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
  connect(ui->lineMiddleName, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
  connect(ui->lineBrand, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
  connect(ui->lineModel, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
  connect(ui->lineCoast, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
  connect(ui->lineDescr, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
}

Dialog_Add_Owner::~Dialog_Add_Owner()
{
  delete ui;
}

void Dialog_Add_Owner::changeEvent(QEvent *e)
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

std::string Dialog_Add_Owner::get_surname() const
{
  return ui->lineSurname->text().toStdString();
}

std::string Dialog_Add_Owner::get_name() const
{
  return ui->lineName->text().toStdString();
}

std::string Dialog_Add_Owner::get_mid_name() const
{
  return ui->lineMiddleName->text().toStdString();
}

std::string Dialog_Add_Owner::get_brand() const
{
  return ui->lineBrand->text().toStdString();
}

std::string Dialog_Add_Owner::get_model() const
{
  return ui->lineModel->text().toStdString();
}

QDate Dialog_Add_Owner::get_date_in() const
{
  return ui->dateIn->date();
}

double Dialog_Add_Owner::get_coast() const
{
  return ui->lineCoast->text().toDouble();
}

std::string Dialog_Add_Owner::get_descr() const
{
  return ui->lineDescr->text().toStdString();
}

void Dialog_Add_Owner::enableButtonOk()
{
  if((!ui->lineSurname->text().isEmpty()) &&
     (!ui->lineName->text().isEmpty()) &&
     (!ui->lineMiddleName->text().isEmpty()) &&
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

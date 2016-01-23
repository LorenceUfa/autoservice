#include "dialog_add_owner.hxx"
#include "ui_dialog_add_owner.h"

Dialog_Add_Owner::Dialog_Add_Owner(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog_Add_Owner)
{
  ui->setupUi(this);

  QValidator *doubler = new QDoubleValidator(0);
  ui->lineCoast->setValidator(doubler);

  connect(ui->buttonOk, SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(ui->buttonCancel, SIGNAL(clicked(bool)), this, SLOT(close()));
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

QDate Dialog_Add_Owner::get_date_out() const
{
  return ui->dateOut->date();
}

double Dialog_Add_Owner::get_coast() const
{
  return ui->lineCoast->text().toDouble();
}

std::string Dialog_Add_Owner::get_descr() const
{
  return ui->lineDescr->text().toStdString();
}

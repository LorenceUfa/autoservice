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

  /* set lines "Surname", "Name" and "Middle name" as non edit */
  ui->lineSurname->setReadOnly(true);
  ui->lineName->setReadOnly(true);
  ui->lineMidName->setReadOnly(true);


  /* set button "OK' enabled if only text is not empty */
  ui->buttonOk->setEnabled(false);

  connect(ui->buttonOk, SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(ui->buttonCancel, SIGNAL(clicked(bool)), this, SLOT(close()));

  connect(ui->lineBrand, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
  connect(ui->lineModel, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
  connect(ui->lineCoast, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
  connect(ui->lineDescr, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));

}

void Dialog_Add_Car::setID(const QString &id)
{
  owner_id = id.toUInt();
}

void Dialog_Add_Car::setSurname(const QString &surname)
{
  ui->lineSurname->setText(surname);
}

void Dialog_Add_Car::setName(const QString &name)
{
  ui->lineName->setText(name);
}

void Dialog_Add_Car::setMidName(const QString &mid_name)
{
  ui->lineMidName->setText(mid_name);
}

uint Dialog_Add_Car::get_owner_id() const
{
  return owner_id;
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

std::string Dialog_Add_Car::get_surname() const
{
  return ui->lineSurname->text().toStdString();
}

std::string Dialog_Add_Car::get_name() const
{
  return ui->lineName->text().toStdString();
}

std::string Dialog_Add_Car::get_mid_name() const
{
  return ui->lineMidName->text().toStdString();
}

std::string Dialog_Add_Car::get_brand() const
{
  return ui->lineBrand->text().toStdString();
}

std::string Dialog_Add_Car::get_model() const
{
  return ui->lineModel->text().toStdString();
}

QDate Dialog_Add_Car::get_date_in() const
{
  return ui->dateIn->date();
}

QDate Dialog_Add_Car::get_date_out() const
{
  return ui->dateOut->date();
}

double Dialog_Add_Car::get_coast() const
{
  return ui->lineCoast->text().toDouble();
}

std::string Dialog_Add_Car::get_descr() const
{
  return ui->lineDescr->text().toStdString();
}

void Dialog_Add_Car::enableButtonOk()
{
  if((!ui->lineBrand->text().isEmpty()) &&
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

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

  ui->dateIn->setReadOnly(true);
  ui->lineCoast->setReadOnly(true);
  ui->lineDescr->setReadOnly(true);

  /* set button "OK' enabled if only text is not empty */
  ui->buttonOk->setEnabled(false);

  ui->dateOut->setMinimumDate(ui->dateIn->date());

  connect(ui->buttonOk, SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(ui->buttonCancel, SIGNAL(clicked(bool)), this, SLOT(close()));

  connect(ui->dateOut, SIGNAL(dateChanged(QDate)), this, SLOT(enableButtonOk()));
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

void Dialog_Return_Car::setOwnerID(const QString &id)
{
  owner_id = id.toUInt();
}

void Dialog_Return_Car::setSurname(const QString &surname)
{
  ui->lineSurname->setText(surname);
}

void Dialog_Return_Car::setName(const QString &name)
{
  ui->lineName->setText(name);
}

void Dialog_Return_Car::setMidName(const QString &mid_name)
{
  ui->lineMidName->setText(mid_name);
}

void Dialog_Return_Car::setCarID(const QString& id)
{
  car_id = id.toUInt();
}

void Dialog_Return_Car::setBrand(const QString& brand)
{
  ui->lineBrand->setText(brand);
}

void Dialog_Return_Car::setModel(const QString& model)
{
  ui->lineModel->setText(model);
}

void Dialog_Return_Car::setDateIn(const QString &date_in)
{
  ui->dateIn->setDate(QDate::fromString(date_in, "dd/MM/yyyy"));
}

void Dialog_Return_Car::setCoast(const QString &coast)
{
  ui->lineCoast->setText(coast);
}

void Dialog_Return_Car::setDescription(const QString &description)
{
  ui->lineDescr->setText(description);
}

uint Dialog_Return_Car::get_owner_id() const
{
  return owner_id;
}

uint Dialog_Return_Car::get_car_id() const
{
  return car_id;
}

uint Dialog_Return_Car::get_serv_id() const
{
  return serv_id;
}

std::string Dialog_Return_Car::get_surname() const
{
  return ui->lineSurname->text().toStdString();
}

std::string Dialog_Return_Car::get_name() const
{
  return ui->lineName->text().toStdString();
}

std::string Dialog_Return_Car::get_mid_name() const
{
  return ui->lineMidName->text().toStdString();
}

std::string Dialog_Return_Car::get_brand() const
{
  return ui->lineBrand->text().toStdString();
}

std::string Dialog_Return_Car::get_model() const
{
  return ui->lineModel->text().toStdString();
}

QDate Dialog_Return_Car::get_date_in() const
{
  return ui->dateIn->date();
}

QDate Dialog_Return_Car::get_date_out() const
{
  return ui->dateOut->date();
}

double Dialog_Return_Car::get_coast() const
{
  return ui->lineCoast->text().toDouble();
}

std::string Dialog_Return_Car::get_descr() const
{
  return ui->lineDescr->text().toStdString();
}

void Dialog_Return_Car::enableButtonOk()
{
  if(!(ui->dateOut->date() < ui->dateIn->date()))
  {
    ui->buttonOk->setEnabled(true);
  }
  else
  {
    ui->buttonOk->setEnabled(false);
  }
}

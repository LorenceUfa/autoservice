#include "dialog_add_service.hxx"
#include "ui_dialog_add_service.h"

Dialog_Add_Service::Dialog_Add_Service(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog_Add_Service)
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

Dialog_Add_Service::~Dialog_Add_Service()
{
  delete ui;
}

void Dialog_Add_Service::changeEvent(QEvent *e)
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

void Dialog_Add_Service::setOwnerID(const QString &id)
{
  owner_id = id.toUInt();
}

void Dialog_Add_Service::setSurname(const QString &surname)
{
  ui->lineSurname->setText(surname);
}

void Dialog_Add_Service::setName(const QString &name)
{
  ui->lineName->setText(name);
}

void Dialog_Add_Service::setMidName(const QString &mid_name)
{
  ui->lineMidName->setText(mid_name);
}

void Dialog_Add_Service::setCarID(const QString& id)
{
  car_id = id.toUInt();
}

void Dialog_Add_Service::setBrand(const QString& brand)
{
  ui->lineBrand->setText(brand);
}

void Dialog_Add_Service::setModel(const QString& model)
{
  ui->lineModel->setText(model);
}

uint Dialog_Add_Service::get_owner_id() const
{
  return owner_id;
}

uint Dialog_Add_Service::get_car_id() const
{
  return car_id;
}

std::string Dialog_Add_Service::get_surname() const
{
  return ui->lineSurname->text().toStdString();
}

std::string Dialog_Add_Service::get_name() const
{
  return ui->lineName->text().toStdString();
}

std::string Dialog_Add_Service::get_mid_name() const
{
  return ui->lineMidName->text().toStdString();
}

std::string Dialog_Add_Service::get_brand() const
{
  return ui->lineBrand->text().toStdString();
}

std::string Dialog_Add_Service::get_model() const
{
  return ui->lineModel->text().toStdString();
}

QDate Dialog_Add_Service::get_date_in() const
{
  return ui->dateIn->date();
}

double Dialog_Add_Service::get_coast() const
{
  return ui->lineCoast->text().toDouble();
}

std::string Dialog_Add_Service::get_descr() const
{
  return ui->lineDescr->text().toStdString();
}

void Dialog_Add_Service::enableButtonOk()
{
  if((!ui->lineCoast->text().isEmpty()) &&
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

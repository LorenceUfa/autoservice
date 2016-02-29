#include "dialog_edit.hxx"
#include "ui_dialog_edit.h"

Dialog_Edit::Dialog_Edit(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog_Edit)
{
  ui->setupUi(this);

  QValidator *doubler = new QDoubleValidator(0);

  /* set line "Coast" for only double variables */
  ui->lineCoast->setValidator(doubler);

  /* set button "OK' enabled if only text is not empty */
  ui->buttonOk->setEnabled(false);

  ui->dateOut->setMinimumDate(ui->dateIn->date());

  connect(ui->buttonOk, SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(ui->buttonCancel, SIGNAL(clicked(bool)), this, SLOT(close()));

  connect(ui->lineSurname, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
  connect(ui->lineName, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
  connect(ui->lineMidName, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));

  connect(ui->lineBrand, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
  connect(ui->lineModel, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));

  connect(ui->dateIn, SIGNAL(editingFinished()), this, SLOT(enableButtonOk()));
  connect(ui->dateOut, SIGNAL(editingFinished()), this, SLOT(enableButtonOk()));
  connect(ui->lineCoast, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
  connect(ui->lineDescr, SIGNAL(textChanged(QString)), this, SLOT(enableButtonOk()));
}

Dialog_Edit::~Dialog_Edit()
{
  delete ui;
}

void Dialog_Edit::changeEvent(QEvent *e)
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

void Dialog_Edit::setOwnerID(const QString &id)
{
  owner_id = id.toUInt();
}

void Dialog_Edit::setSurname(const QString &surname)
{
  ui->lineSurname->setText(surname);
}

void Dialog_Edit::setName(const QString &name)
{
  ui->lineName->setText(name);
}

void Dialog_Edit::setMidName(const QString &mid_name)
{
  ui->lineMidName->setText(mid_name);
}

void Dialog_Edit::setCarID(const QString& id)
{
  car_id = id.toUInt();
}

void Dialog_Edit::setBrand(const QString& brand)
{
  ui->lineBrand->setText(brand);
}

void Dialog_Edit::setModel(const QString& model)
{
  ui->lineModel->setText(model);
}

void Dialog_Edit::setDateIn(const QString &date_in)
{
  ui->dateIn->setDate(QDate::fromString(date_in, "dd/MM/yyyy"));
}

void Dialog_Edit::setDateOut(const QString &date_out)
{
  if (!date_out.isNull())
    ui->dateOut->setDate(QDate::fromString(date_out, "dd/MM/yyyy"));
  else
    ui->dateOut->setDisabled(true);
}

void Dialog_Edit::setCoast(const QString &coast)
{
  ui->lineCoast->setText(coast);
}

void Dialog_Edit::setDescription(const QString &description)
{
  ui->lineDescr->setText(description);
}

uint Dialog_Edit::get_owner_id() const
{
  return owner_id;
}

uint Dialog_Edit::get_car_id() const
{
  return car_id;
}

uint Dialog_Edit::get_serv_id() const
{
  return serv_id;
}

std::string Dialog_Edit::get_surname() const
{
  return ui->lineSurname->text().toStdString();
}

std::string Dialog_Edit::get_name() const
{
  return ui->lineName->text().toStdString();
}

std::string Dialog_Edit::get_mid_name() const
{
  return ui->lineMidName->text().toStdString();
}

std::string Dialog_Edit::get_brand() const
{
  return ui->lineBrand->text().toStdString();
}

std::string Dialog_Edit::get_model() const
{
  return ui->lineModel->text().toStdString();
}

QDate Dialog_Edit::get_date_in() const
{
  return ui->dateIn->date();
}

QDate Dialog_Edit::get_date_out() const
{
  return ui->dateOut->date();
}

double Dialog_Edit::get_coast() const
{
  return ui->lineCoast->text().toDouble();
}

std::string Dialog_Edit::get_descr() const
{
  return ui->lineDescr->text().toStdString();
}

void Dialog_Edit::enableButtonOk()
{
  if(ui->lineSurname->isModified() ||
     ui->lineName->isModified() ||
     ui->lineMidName->isModified() ||
     ui->lineBrand->isModified() ||
     ui->lineModel->isModified() ||
     ui->lineCoast->isModified() ||
     ui->lineDescr->isModified())
  {
    ui->buttonOk->setEnabled(true);
  }
  else
  {
    ui->buttonOk->setEnabled(false);
  }
}

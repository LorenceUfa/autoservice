#include "dialog_add_owner.hxx"
#include "ui_dialog_add_owner.h"

Dialog_Add_Owner::Dialog_Add_Owner(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog_Add_Owner)
{
  ui->setupUi(this);
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

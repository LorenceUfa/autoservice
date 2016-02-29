#include "mainwindow.hxx"
#include "ui_mainwindow.h"
#include "dialog_add_owner.hxx"
#include "dialog_add_car.hxx"
#include "dialog_add_service.hxx"
#include "dialog_return_car.hxx"
#include "dialog_edit.hxx"
#include <typeinfo>


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  connect(ui->button_add_car, SIGNAL(clicked(bool)), this, SLOT(button_add_car()));
  connect(ui->button_add_owner, SIGNAL(clicked(bool)), this, SLOT(button_add_owner()));
  connect(ui->button_add_service, SIGNAL(clicked(bool)), this, SLOT(button_add_service()));
  connect(ui->button_delete, SIGNAL(clicked(bool)), this, SLOT(button_delete()));
  connect(ui->button_edit, SIGNAL(clicked(bool)), this, SLOT(button_edit()));
  connect(ui->button_exit, SIGNAL(clicked(bool)), this, SLOT(button_exit()));
  connect(ui->button_return_car, SIGNAL(clicked(bool)), this, SLOT(button_return_car()));

  /* Column resize to content */
  ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  /* Do not edit contents */
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

  ui->tableWidget->setColumnWidth(0, 50);
  ui->tableWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);

  ui->tableWidget->setColumnWidth(4, 50);
  ui->tableWidget->horizontalHeader()->setResizeMode(4, QHeaderView::Fixed);

  ui->tableWidget->setColumnWidth(7, 50);
  ui->tableWidget->horizontalHeader()->setResizeMode(7, QHeaderView::Fixed);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
  QMainWindow::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}

template <typename T>
void MainWindow::dialog_func(const T& dialog, Owner& own, Car& car, Service& serv)
{
  own.set_surname(dialog.get_surname());
  own.set_name(dialog.get_name());
  own.set_sec_name(dialog.get_mid_name());

  car.set_brand(dialog.get_brand());
  car.set_model(dialog.get_model());

  serv.set_date_in(dialog.get_date_in());
  serv.set_coast(dialog.get_coast());
  serv.set_description(dialog.get_descr());
}

void MainWindow::button_add_owner()
{
  Owner own;
  Car car;
  Service serv;

  Dialog_Add_Owner dialog;
  if(dialog.exec() == QDialog::Accepted)
  {
    uint own_id, car_id;

    dialog_func<Dialog_Add_Owner>(dialog, own, car, serv);
    own_id = db.add_data(own);

    car.set_owner_id(own_id);
    car_id = db.add_data(car);

    serv.set_owner_id(own_id);
    serv.set_car_id(car_id);
    db.add_data(serv);

    add_column(&own, &car, &serv);
  }
}

void MainWindow::button_add_car()
{
  Dialog_Add_Car dialog;
  Owner own;
  Car car;
  Service serv;
  int row = ui->tableWidget->currentRow();
  if (row < 0)
    return;

  /* set owner information from selected row in table widget */
  dialog.setID(ui->tableWidget->item(row, owner_id_e)->text());
  dialog.setSurname(ui->tableWidget->item(row, surname_e)->text());
  dialog.setName(ui->tableWidget->item(row, name_e)->text());
  dialog.setMidName(ui->tableWidget->item(row, mid_name_e)->text());

  if(dialog.exec() == QDialog::Accepted)
  {
    uint own_id, car_id;

    dialog_func<Dialog_Add_Car>(dialog, own, car, serv);

    own_id = dialog.get_owner_id();
    own.set_id(own_id);

    car.set_owner_id(own_id);
    car_id = db.add_data(car);

    serv.set_owner_id(own_id);
    serv.set_car_id(car_id);
    db.add_data(serv);

    add_column(&own, &car, &serv);
  }

}



void MainWindow::button_add_service()
{
  Dialog_Add_Service dialog;
  Owner own;
  Car car;
  Service serv;
  int row = ui->tableWidget->currentRow();
  if (row < 0)
    return;

  /* set owner information from selected row in table widget */
  dialog.setOwnerID(ui->tableWidget->item(row, owner_id_e)->text());
  dialog.setSurname(ui->tableWidget->item(row, surname_e)->text());
  dialog.setName(ui->tableWidget->item(row, name_e)->text());
  dialog.setMidName(ui->tableWidget->item(row, mid_name_e)->text());

  dialog.setCarID(ui->tableWidget->item(row, car_id_e)->text());
  dialog.setBrand(ui->tableWidget->item(row, brand_e)->text());
  dialog.setModel(ui->tableWidget->item(row, model_e)->text());

  if(dialog.exec() == QDialog::Accepted)
  {
    uint own_id, car_id;

    dialog_func<Dialog_Add_Service>(dialog, own, car, serv);

    own_id = dialog.get_owner_id();
    own.set_id(own_id);

    car_id = dialog.get_car_id();
    car.set_owner_id(own_id);
    car.set_id(car_id);

    serv.set_owner_id(own_id);
    serv.set_car_id(car_id);
    db.add_data(serv);

    add_column(&own, &car, &serv);
  }
}

void MainWindow::button_delete()
{

}

void MainWindow::button_edit()
{
  Dialog_Edit dialog;

  int row = ui->tableWidget->currentRow();
  if (row < 0)
    return;

  Owner own;
  Car car;
  Service serv;

  /* set owner information from selected row in table widget */
  dialog.setOwnerID(ui->tableWidget->item(row, owner_id_e)->text());
  dialog.setSurname(ui->tableWidget->item(row, surname_e)->text());
  dialog.setName(ui->tableWidget->item(row, name_e)->text());
  dialog.setMidName(ui->tableWidget->item(row, mid_name_e)->text());

  dialog.setCarID(ui->tableWidget->item(row, car_id_e)->text());
  dialog.setBrand(ui->tableWidget->item(row, brand_e)->text());
  dialog.setModel(ui->tableWidget->item(row, model_e)->text());

  dialog.setDateIn(ui->tableWidget->item(row, date_in_e)->text());

  if (ui->tableWidget->item(row, date_out_e))
    dialog.setDateOut(ui->tableWidget->item(row, date_out_e)->text());
  else
    dialog.setDateOut(NULL);

  dialog.setCoast(ui->tableWidget->item(row, coast_e)->text());
  dialog.setDescription(ui->tableWidget->item(row, descr_e)->text());

  if(dialog.exec() == QDialog::Accepted)
  {
    uint own_id, car_id;

    dialog_func<Dialog_Edit>(dialog, own, car, serv);

    own_id = dialog.get_owner_id();
    own.set_id(own_id);

    car_id = dialog.get_car_id();
    car.set_owner_id(own_id);
    car.set_id(car_id);

    if (ui->tableWidget->item(row, date_out_e)) {
      QDate date = dialog.get_date_out();

      serv.set_date_out(date);

      /* Set date to table widget */
      ui->tableWidget->item(row, date_out_e)->setText(date.toString("dd/MM/yyyy"));
    }
    serv.set_owner_id(own_id);
    serv.set_car_id(car_id);

    /* Update data in table widget */
    ui->tableWidget->item(row, surname_e)->setText(QString::fromStdString(own.get_surname()));
    ui->tableWidget->item(row, name_e)->setText(QString::fromStdString(own.get_name()));
    ui->tableWidget->item(row, mid_name_e)->setText(QString::fromStdString(own.get_sec_name()));

    ui->tableWidget->item(row, brand_e)->setText(QString::fromStdString(car.get_brand()));
    ui->tableWidget->item(row, model_e)->setText(QString::fromStdString(car.get_model()));

    ui->tableWidget->item(row, date_in_e)->setText(serv.get_date_in().toString("dd/MM/yyyy"));
    ui->tableWidget->item(row, coast_e)->setText(tr("%1").arg(serv.get_coast()));
    ui->tableWidget->item(row, descr_e)->setText(QString::fromStdString(serv.get_description()));

    db.edit_data(own, car, serv);
  }
}


void MainWindow::button_return_car()
{
  Dialog_Return_Car dialog;
  int row = ui->tableWidget->currentRow();
  if (row < 0)
    return;

  /* set owner information from selected row in table widget */
  dialog.setOwnerID(ui->tableWidget->item(row, owner_id_e)->text());
  dialog.setSurname(ui->tableWidget->item(row, surname_e)->text());
  dialog.setName(ui->tableWidget->item(row, name_e)->text());
  dialog.setMidName(ui->tableWidget->item(row, mid_name_e)->text());

  dialog.setCarID(ui->tableWidget->item(row, car_id_e)->text());
  dialog.setBrand(ui->tableWidget->item(row, brand_e)->text());
  dialog.setModel(ui->tableWidget->item(row, model_e)->text());

  dialog.setDateIn(ui->tableWidget->item(row, date_in_e)->text());
  dialog.setCoast(ui->tableWidget->item(row, coast_e)->text());
  dialog.setDescription(ui->tableWidget->item(row, descr_e)->text());

  if(dialog.exec() == QDialog::Accepted)
  {
    uint serv_id;
    QDate date;

    date = dialog.get_date_out();
    serv_id = dialog.get_serv_id();

    db.add_out_date(date, serv_id);

    QTableWidgetItem *newItem = new QTableWidgetItem();
    newItem->setText(date.toString("dd/MM/yyyy"));
    ui->tableWidget->setItem(row, date_out_e, newItem);
  }
}

void MainWindow::button_exit()
{
  exit(0);
}
void MainWindow::add_column(const Owner *own, const Car *car, const Service *service)
{
  int row = ui->tableWidget->rowCount();
  ui->tableWidget->setRowCount(row + 1);

  for(int column=0; column!=ui->tableWidget->columnCount(); ++column) {

    switch(column)
    {
      case 0:
        {
          QTableWidgetItem *newItem;
          newItem = new QTableWidgetItem(tr("%1").arg(own->get_id()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 1:
        {
          QTableWidgetItem *newItem = new QTableWidgetItem();
          newItem->setText(QString::fromStdString(own->get_surname()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 2:
        {
          QTableWidgetItem *newItem = new QTableWidgetItem();
          newItem->setText(QString::fromStdString(own->get_name()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 3:
        {
          QTableWidgetItem *newItem = new QTableWidgetItem();
          newItem->setText(QString::fromStdString(own->get_sec_name()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 4:
        {
          QTableWidgetItem *newItem;
          newItem = new QTableWidgetItem(tr("%1").arg(car->get_id()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 5:
        {
          QTableWidgetItem *newItem = new QTableWidgetItem();
          newItem->setText(QString::fromStdString(car->get_brand()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 6:
        {
          QTableWidgetItem *newItem = new QTableWidgetItem();
          newItem->setText(QString::fromStdString(car->get_model()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 7:
        {
          QTableWidgetItem *newItem;
          newItem = new QTableWidgetItem(tr("%1").arg(service->get_id()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 8:
        {
          QTableWidgetItem *newItem = new QTableWidgetItem();
          newItem->setText(service->get_date_in().toString("dd/MM/yyyy"));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 9:
        {
          if (!service->get_date_out().isNull())
          {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            newItem->setText(service->get_date_out().toString("dd/MM/yyyy"));
            ui->tableWidget->setItem(row, column, newItem);
          }
        }
        break;
      case 10:
        {
          QTableWidgetItem *newItem;
          newItem = new QTableWidgetItem(tr("%1").arg(service->get_coast()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 11:
        {
          QTableWidgetItem *newItem = new QTableWidgetItem();
          newItem->setText(QString::fromStdString(service->get_description()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      default: break;
    }
  }
}

#include "mainwindow.hxx"
#include "ui_mainwindow.h"
#include "dialog_add_owner.hxx"

#include <Qt>

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
  connect(ui->button_return_auto, SIGNAL(clicked(bool)), this, SLOT(button_return_auto()));

  ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
  ui->tableWidget->setColumnWidth(0, 30);
  ui->tableWidget->setColumnWidth(4, 30);
  ui->tableWidget->setColumnWidth(7, 30);

  for(int row=0; row!=ui->tableWidget->rowCount(); ++row){
      for(int column=0; column!=ui->tableWidget->columnCount(); ++column) {
          QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg((row+1)*(column+1)));
          ui->tableWidget->setItem(row, column, newItem);
      }
  }

  int row_count = ui->tableWidget->rowCount();

  ui->tableWidget->setRowCount(row_count + 1);
  QTableWidgetItem *table_item = new QTableWidgetItem(tr("%1").arg(rand()%100));
  table_item->setTextAlignment(Qt::AlignLeft);
  ui->tableWidget->setItem(row_count, 1, table_item);
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

void MainWindow::button_add_owner()
{
  Owner own;
  Car car;
  Service serv;

  Dialog_Add_Owner dialog;
  if(dialog.exec() == QDialog::Accepted)
  {
    uint own_id, car_id;

    own.set_surname(dialog.get_surname());
    own.set_name(dialog.get_name());
    own.set_sec_name(dialog.get_mid_name());
    own_id = db.add_data(own);

    car.set_owner_id(own_id);
    car.set_brand(dialog.get_brand());
    car.set_model(dialog.get_model());
    car_id = db.add_data(car);

    serv.set_owner_id(own_id);
    serv.set_car_id(car_id);
    serv.set_date_in(dialog.get_date_in());
    serv.set_date_out(dialog.get_date_out());
    serv.set_coast(dialog.get_coast());
    serv.set_description(dialog.get_descr());
    db.add_data(serv);
  }
}

void MainWindow::button_add_car()
{
  bool success;
  bool result = false;
  uint menu_id = 0;

  while(!result)
  {
    success = false;
    std::cout << std::endl << std::endl;

    std::cout << "Menu...\n";
    std::cout << "1) Add new owner\n"
              << "2) Add new car for choosen owner\n"
              << "3) Write down the famous owner on service\n"
              << "4) Show data\n"
              << "5) Remove data\n"
              << "6) Edit data\n"
              << "7) Return auto from service\n"
              << "0) Exit\n\n";
    while(!success)
    {
      std::cout << "Enter number of choosen menu item: ";
      std::cin >> menu_id;

      switch(menu_id)
      {
        case 0: result = true;        success = true; break;
        case 1: db.add_owner();       success = true; break;
        case 2: db.add_car(0);        success = true; break;
        case 3: db.add_service(0, 0); success = true; break;
        case 4: db.show_data();       success = true; break;
        case 5: db.remove_data();     success = true; break;
        case 6: db.edit_data();       success = true; break;
        case 7: db.add_out_date();    success = true; break;
        default:
          {
            std::cout << "There is no such number!";
            success = false; break;
          }
      }
    }
  }

  if(result)
  {
    return;
  }
}

void MainWindow::button_add_service()
{

}

void MainWindow::button_delete()
{

}

void MainWindow::button_edit()
{

}

void MainWindow::button_exit()
{

}

void MainWindow::button_return_auto()
{

}

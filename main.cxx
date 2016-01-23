#include <QCoreApplication>
#include <QApplication>
#include "mainwindow.hxx"
#include "database.hxx"
#include "dialog_add_owner.hxx"

int menu();

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow d_main;
  Dialog_Add_Owner d_own;

  d_main.show();
//  d_own.show();

//  int result = 1;
//  result = menu();
//  if(result == 1) {
//    return 0;
//  }

  return a.exec();
}

int menu()
{
  DataBase db;
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
    return 0;
  }

  return 0;
}

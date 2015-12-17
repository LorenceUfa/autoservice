#include <QCoreApplication>
#include "database.hxx"
#include "car.hxx"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  DataBase db;

  db.add_data();

  exit(0);
  return a.exec();
}

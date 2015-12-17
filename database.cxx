#include "database.hxx"

DataBase::DataBase()
{
  _car_id = 0;
  _owner_id = 0;
  _service_id = 0;
}

void DataBase::add_data()
{
  std::cout << "Enter client information...\n";
  Owner owner;
  std::cin >> owner;

  add_data(owner);
}

void DataBase::add_data(Car& car)
{
  car.set_id(++_car_id);

  _car.push_back(car);
}

void DataBase::add_data(Owner& owner)
{
  owner.set_id(++_owner_id);

  _owner.push_back(owner);
}

void DataBase::add_data(Service& service)
{
  service.set_id(++_service_id);

  _service.push_back(service);
}


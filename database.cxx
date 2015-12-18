#include "database.hxx"

DataBase::DataBase()
{
  _car_id = 0;
  _owner_id = 0;
  _service_id = 0;
}

void DataBase::add_owner()
{
  uint id = 0;

  std::cout << "Enter client information...\n";
  Owner owner;

  std::cin >> owner;

  id = add_data(owner); // push back data to owners list

  add_car(id);
}

void DataBase::add_car(uint owner_id)
{
  if (owner_id == 0) // Find owner for this car
  {
    owner_id = find_owner();
  }

  Car car;
  uint car_id = 0;

  std::cout << "Enter car information...\n";
  std::cin >> car;

  car.set_owner_id(owner_id);

  car_id = add_data(car);

  add_service(owner_id, car_id);
}

void DataBase::add_service(uint owner_id, uint car_id)
{
  if (owner_id == 0)
  {
    owner_id = find_owner();
  }
  if (car_id == 0)
  {
    car_id = find_car(owner_id);
  }

  Service service;

  std::cout << "Enter service information...\n";
  std::cin >> service;

  service.set_car_id(car_id);
  service.set_owner_id(owner_id);

  add_data(service);
}

uint DataBase::find_owner() const
{
  uint id = 0;
  bool success = false;

  std::cout << "Choose owner from list...\n";

  for (const auto& owner : _owner)
  {
    std::cout << owner;
  }

  while (!success)
  {
    std::cout << "Enter owner id: ";
    std::cin >> id;

    for (const auto& owner : _owner)
    {
      if (owner.get_id() == id)
      {
        success = true;
        break;
      }
    }

    if (!success)
    {
      std::cout << "Owner not found!\n";
      id = 0;
    }
  }

  // return found owner id
  return id;
}

uint DataBase::find_car(const uint owner_id) const
{
  uint id = 0;
  bool success = false;

  std::cout << "Choose car from list...\n";

  for (const auto& car : _car)
  {
    if (car.get_owner_id() == owner_id)
      std::cout << car;
  }

  while (!success)
  {
    std::cout << "Enter car id: ";
    std::cin >> id;

    for (const auto& car : _car)
    {
      if (car.get_id() == id)
      {
        success = true;
        break;
      }
    }

    if (!success)
    {
      std::cout << "Car not found!\n";
      id = 0;
    }
  }

  return id;
}

void DataBase::show_data()
{
  std::cout << "Clients data:\n";

  for (const auto& owner : _owner)
  {
    uint owner_id = 0;

    owner_id = owner.get_id();

    for (const auto& car: _car)
    {
      if (owner_id != car.get_owner_id())
        continue;

      uint car_id = 0;
      car_id = car.get_id();

      for (const auto& service : _service)
      {
        if ((car_id != service.get_car_id()) ||
            (owner_id != service.get_owner_id()))
          continue;

        std::cout << owner << " ";
        std::cout << car << " ";
        std::cout << service;
      }
    }
  }

}

uint DataBase::add_data(Car& car)
{
  car.set_id(++_car_id);

  _car.push_back(car);

  return car.get_id();
}

uint DataBase::add_data(Owner& owner)
{
  owner.set_id(++_owner_id);

  _owner.push_back(owner);

  return owner.get_id();
}

void DataBase::add_data(Service& service)
{
  service.set_id(++_service_id);

  _service.push_back(service);
}


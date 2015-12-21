#include "database.hxx"

DataBase::DataBase()
{
  _car_id = 0;
  _owner_id = 0;
  _service_id = 0;
}

/* Add owner to  database list */
void DataBase::add_owner()
{
  uint id = 0;

  std::cout << "Enter client information...\n";
  Owner owner;

  std::cin >> owner;

  id = add_data(owner); // push back data to owners list

  add_car(id);
}

/* Add car by owner id */
void DataBase::add_car(uint owner_id)
{
  if (owner_id == 0) // Find owner for this car
  {
    owner_id = find_owner();
  }

  if (owner_id == 0)
  {
    return;
  }

  Car car;
  uint car_id = 0;

  std::cout << "Enter car information...\n";
  std::cin >> car;

  car.set_owner_id(owner_id);

  car_id = add_data(car);

  add_service(owner_id, car_id);
}

/* Add service by owner and car id */
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

  if (owner_id == 0)
  {
    return;
  }

  if (car_id == 0)
  {
    std::cout << "Car not found!\n";
    return;
  }

  Service service;

  std::cout << "Enter service information...\n";
  std::cin >> service;

  service.set_car_id(car_id);
  service.set_owner_id(owner_id);

  add_data(service);
}

/* Functions for print and choose owner from list */
uint DataBase::find_owner() const
{
  uint id = 0;
  bool success = false;

  if (_owner.size() == 0)
  {
    std::cout << "Owner list is empty!\n";
    return 0;
  }

  std::cout << "Choose owner from list...\n";

  /* print header and borders */
  print_border(50);
  if(!print_head(owner_head))
  {
    return 0;
  }
  std::cout << "\n";
  print_border(50);

  for (const auto& owner : _owner)
  {
    std::cout << owner;
  }
  std::cout << "\n";

  print_border(50);

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


/* Functions for print and choose car from list */
uint DataBase::find_car(const uint owner_id) const
{
  uint id = 0;
  bool success = false;

  if (_car.size() == 0)
  {
    std::cout << "Car list is empty!\n";
    return 0;
  }

  std::cout << "Choose car from list...\n";

  /* print header and borders */
  print_border(50);
  if(!print_head(car_head))
  {
    return 0;
  }
  std::cout << "\n";
  print_border(50);

  for (const auto& car : _car)
  {
    if (car.get_owner_id() == owner_id)
    {
      std::cout << car;
      std::cout << "\n";
    }
  }

  print_border(50);

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

/* Function for show all database lists */
void DataBase::show_data()
{
  std::cout << "Clients data:\n";

  /* 130 spaces */
  print_border(130);

  if(!print_head(owner_head))
  {
    return;
  }
  if(!print_head(car_head))
  {
    return;
  }
  if(!print_head(service_head))
  {
    return;
  }
  std::cout << "\n";

  print_border(130);

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

        std::cout << std::setiosflags(std::ios::left);
        std::cout << owner;
        std::cout << car;
        std::cout << service;
      }
    }
  }

  print_border(130);
  std::cout << std::endl;
}

uint DataBase::add_data(Car& car) const
{
  car.set_id(++_car_id);

  _car.push_back(car);

  return car.get_id();
}

uint DataBase::add_data(Owner& owner) const
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


bool print_head(uint type)
{
  /*
   * type = 1 - Owner header
   * type = 2 - Car header
   * type = 3 - Service header
   */

  if (type == 1)
  {
    std::cout << "ID | Surname        | Name      | Second name    | ";
    return true;
  }
  else if (type == 2)
  {
    std::cout << "ID | Brand     | Model     | ";
    return true;
  }
  else if (type == 3)
  {
    std::cout << "Date in    | Date out   | Coast     | Description";
    return true;
  }
  else
  {
    std::cout << "Unknown header!\n";
    return true;
  }
  return false;
}

void print_border(uint count)
{
  uint i = 0;
  while(i < count)
  {
    std::cout << "-";
    i++;
  }
  std::cout << "\n";
}


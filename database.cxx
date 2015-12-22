#include <database.hxx>
#include <algorithm>

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

void DataBase::add_out_date()
{
  if (list_is_empty(owner_e))
    return;

  uint owner_id = 0, car_id = 0, service_id = 0;

  owner_id = find_owner();
  car_id = find_car(owner_id);
  service_id = find_service(car_id);

  for (auto& service : _service)
  {
    if (service.get_id() == service_id)
    {
      QDate date;
      std::string str;

      std::cout << "Enter car out date (DD/MM/YYY): ";
      std::cin >> str;

      date = QDate::fromString(QString::fromStdString(str), "dd/MM/yyyy");

      service.set_date_out(date);
    }
  }
}

void DataBase::edit_data()
{
  if (list_is_empty(owner_e))
    return;

  uint menu_id = 0;
  bool success = false;

  std::cout << "Choose editing object...\n";
  std::cout << "1) Owner\n"
               "2) Car\n"
               "3) Service\n"
               "4) All information\n"
               "0) Exit to main\n";
  while(!success)
  {
    std::cout << "Enter number of choosen menu item: ";
    std::cin >> menu_id;

    switch(menu_id)
    {
      case 0: success = true;                 break;
      case 1: success = true; edit_owner();   break;
      case 2: success = true; edit_car();     break;
      case 3: success = true; edit_service(); break;
      case 4: success = true; edit_all();     break;
      default:
        {
          std::cout << "There is no such number!\n";
          success = false; break;
        }
    }
  }
}

void DataBase::edit_owner()
{
  uint id = 0;

  id = find_owner();

  for (auto& owner : _owner)
  {
    if (owner.get_id() == id)
    {
      std::cin >> owner;
      break;
    }
  }
}

void DataBase::edit_car()
{
  uint id = 0;
  uint owner_id = 0;

  owner_id = find_owner();
  id = find_car(owner_id);

  for (auto& car : _car)
  {
    if (car.get_id() == id)
    {
      std::cin >> car;
      break;
    }
  }
}

void DataBase::edit_service()
{
  uint id = 0;
  uint car_id = 0, owner_id = 0;

  owner_id = find_owner();
  car_id = find_car(owner_id);
  id = find_service(car_id);

  for (auto& service : _service)
  {
    if (service.get_id() == id)
    {
      std::cin >> service;
      break;
    }
  }
}

void DataBase::edit_all()
{
  uint owner_id = 0, car_id = 0, service_id = 0;

  owner_id = find_owner();
  car_id = find_car(owner_id);
  service_id = find_service(car_id);

  for (auto& owner : _owner)
  {
    if (owner.get_id() == owner_id)
    {
      std::cin >> owner;
      break;
    }
  }

  for (auto& car : _car)
  {
    if (car.get_id() == car_id)
    {
      std::cin >> car;
      break;
    }
  }

  for (auto& service : _service)
  {
    if (service.get_id() == service_id)
    {
      std::cin >> service;
      break;
    }
  }
}

void DataBase::remove_data()
{
  if (list_is_empty(owner_e))
    return;

  uint menu_id = 0;
  bool success = false;

  std::cout << "Choose removed object...\n";
  std::cout << "1) Owner\n"
               "2) Car\n"
               "3) Service\n"
               "0) Exit to main\n";
  while(!success)
  {
    std::cout << "Enter number of choosen menu item: ";
    std::cin >> menu_id;

    switch(menu_id)
    {
      case 0: success = true;                       break;
      case 1: success = true; remove_owner(0);      break;
      case 2: success = true; remove_car(0);        break;
      case 3: success = true; remove_service(0, 0); break;
      default:
        {
          std::cout << "There is no such number!\n";
          success = false; break;
        }
    }
  }
}

void DataBase::remove_owner(uint id)
{
  if (list_is_empty(owner_e))
    return;

  if (id == 0)
  {
    id = find_owner();
  }

  std::list<Owner>::iterator own;

  for (own = _owner.begin(); own != _owner.end(); )
  {
    if(own->get_id() == id)
    {
      _owner.erase(own++);
      break;
    }
    else
      own++;
  }

  remove_car(id);
}

void DataBase::remove_car(uint owner_id)
{
  uint id = 0;
  bool del_all = false; /* if owner removed, then remove all owner cars */

  if (owner_id == 0)
  {
    owner_id = find_owner();
    id = find_car(owner_id);
  }
  else
    del_all = true;

  if ((id == 0) && (del_all == false))
  {
    return;
  }

  std::list<Car>::iterator car;

  for (car = _car.begin(); car != _car.end(); )
  {
    if ((del_all) && (car->get_owner_id() == owner_id))
    {
      _car.erase(car++);
    }
    else if ((!del_all) && (car->get_id() == id))
    {
      _car.erase(car++);
      break;
    }
    else
    {
      car++;
    }
  }

  if (del_all) /* remove all service for owner */
    remove_service(owner_id, id);
  else /* remove all service for car */
    remove_service(0, id);
}

void DataBase::remove_service(uint owner_id, uint car_id)
{
  uint id = 0;
  bool del_all_owner =false; /* remove all service for owner */
  bool del_all_car = false; /* remove all service for car */

  if ((owner_id == 0) && (car_id == 0))
  {
    owner_id = find_owner();
    car_id = find_car(owner_id);
    id = find_service(car_id);
  }
  else if ((owner_id == 0) && (car_id > 0))
  {
    del_all_car = true;
  }
  else if ((owner_id > 0) && (car_id > 0))
  {
    del_all_owner = true;
  }
  else
  {
    return;
  }

  std::list<Service>::iterator service;

  for (service = _service.begin(); service != _service.end(); )
  {
    if ((del_all_owner) && (service->get_owner_id() == owner_id))
    {
      _service.erase(service++);
    }
    else if ((del_all_car) && (service->get_car_id() == car_id))
    {
      _service.erase(service++);
    }
    else if (service->get_id() == id)
    {
      _service.erase(service++);
      break;
    }
    else
    {
      service++;
    }
  }
}

/* Functions for print and choose owner from list */
uint DataBase::find_owner() const
{
  uint id = 0;
  bool success = false;

  if (list_is_empty(owner_e))
    return 0;

  std::cout << "Choose owner from list...\n";

  /* print header and borders */
  print_border(50);
  if(!print_head(owner_e))
  {
    return 0;
  }
  std::cout << "\n";
  print_border(50);

  for (const auto& owner : _owner)
  {
    std::cout << std::setiosflags(std::ios::left);
    std::cout << owner;
    std::cout << "\n";
  }

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

  if (list_is_empty(car_e))
    return 0;

  if (owner_id == 0)
  {
    std::cout << "There is no owner ID!\n";
    return 0;
  }

  std::cout << "Choose car from list...\n";

  /* print header and borders */
  print_border(28);
  if(!print_head(car_e))
  {
    return 0;
  }
  std::cout << "\n";
  print_border(28);

  for (const auto& car : _car)
  {
    if (car.get_owner_id() == owner_id)
    {
      std::cout << std::setiosflags(std::ios::left);
      std::cout << car;
      std::cout << "\n";
    }
  }

  print_border(28);

  while (!success)
  {
    std::cout << "Enter car id: ";
    std::cin >> id;

    for (const auto& car : _car)
    {
      if ((car.get_id() == id) && (car.get_owner_id() == owner_id))
      {
        success = true;
        break;
      }
      else if ((car.get_id() == id) && (car.get_owner_id() != owner_id))
      {
        success = false;
        std::cout << "Invalid car ID!\n";
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

uint DataBase::find_service(const uint car_id) const
{
  uint id = 0;
  bool success = false;

  if (list_is_empty(service_e))
    return 0;

  if (car_id == 0)
  {
    std::cout << "There is no car ID!\n";
    return 0;
  }

  std::cout << "Choose service from list...\n";

  /* print header and borders */
  print_border(54);
  if(!print_head(service_e))
  {
    return 0;
  }
  std::cout << "\n";
  print_border(54);

  for (const auto& service : _service)
  {
    if (service.get_car_id() == car_id)
    {
      std::cout << std::setiosflags(std::ios::left);
      std::cout << service;
    }
  }

  print_border(54);

  while (!success)
  {
    std::cout << "Enter service id: ";
    std::cin >> id;

    for (const auto& service : _service)
    {
      if ((service.get_id() == id) && (service.get_car_id() == car_id))
      {
        success = true;
        break;
      }
      else if ((service.get_id() == id) && (service.get_car_id() != car_id))
      {
        success = false;
        std::cout << "Invalid service ID!\n";
      }
    }

    if (!success)
    {
      std::cout << "Service not found!\n";
      id = 0;
    }
  }

  return id;
}

/* Function for show all database lists */
void DataBase::show_data()
{
  std::cout << "Clients data:\n";



  /* 135 spaces */
  print_border(135);

  if(!print_head(main_e))
    return;

  print_border(135);

  if(!print_head(owner_e))
    return;

  if(!print_head(car_e))
    return;

  if(!print_head(service_e))
    return;

  std::cout << "\n";

  print_border(135);

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

  print_border(135);
  std::cout << std::endl;
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

bool DataBase::list_is_empty(uint type) const
{
  switch(type)
  {
    case owner_e:
      {
        if (_owner.size() == 0)
        {
          std::cout << "Owner list is empty!\n";
          return true;
        }
        else
          return false;
      }
    case car_e:
      {
        if (_car.size() == 0)
        {
          std::cout << "Car list is empty!\n";
          return true;
        }
        else
          return false;
      }
    case service_e:
      {
        if (_service.size() == 0)
        {
          std::cout << "Service list is empty!\n";
          return true;
        }
        else
          return false;
      }
    default: std::cout << "Invalid type value!\n"; return true;
  }

  return true;
}


bool print_head(uint type)
{
  /*
   * type = 1 - Owner header
   * type = 2 - Car header
   * type = 3 - Service header
   * type== 4 - Main head
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
    std::cout << "ID | Date in    | Date out   | Coast     | Description";
    return true;
  }
  else if (type == 4)
  {
    std::cout << "                     OWNER                       | "
                 "            CAR            | "
                 "                      SERVICE                         \n";
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


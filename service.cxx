#include <service.hxx>

Service::Service()
{

}

Service::Service(uint id,
                 uint owner_id,
                 uint car_id,
                 std::string description,
                 double coast,
                 QDate date_in,
                 QDate date_out) :
  _id(id), _owner_id(owner_id), _car_id(car_id),
  _description(description), _coast(coast),
  _date_in(date_in), _date_out(date_out)
{

}

std::istream& operator>>(std::istream &is, Service& service)
{
  std::string str;

  std::cout << "Date (DD/MM/YYYY): ";
  is >> str;
  service._date_in =
      QDate::fromString(QString::fromStdString(str),
                        "dd/MM/yyyy");

  std::cout << "Description: ";
  is >> service._description;

  std::cout << "Coast: ";
  is >> service._coast;

  return is;
}

void Service::set_id(uint id)
{
  _id = id;
}

void Service::set_owner_id(uint owner_id)
{
  _owner_id = owner_id;
}

void Service::set_car_id(uint car_id)
{
  _car_id = car_id;
}

void Service::set_description(std::string description)
{
  _description = description;
}

void Service::set_coast(double coast)
{
  _coast = coast;
}

void Service::set_date_in(QDate date_in)
{
  _date_in = date_in;
}

void Service::set_date_out(QDate date_out)
{
  _date_out = date_out;
}


uint Service::get_id() const
{
  return _id;
}

uint Service::get_owner_id() const
{
  return _owner_id;
}

uint Service::get_car_id() const
{
  return _car_id;
}

std::string Service::get_description() const
{
  return _description;
}

double Service::get_coast() const
{
  return _coast;
}

QDate Service::get_date_in() const
{
  return _date_in;
}

QDate Service::get_date_out() const
{
  return _date_out;
}


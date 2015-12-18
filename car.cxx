#include <car.hxx>

Car::Car() :
  _id(0), _owner_id(0), _brand(""), _model("")
{

}
Car::Car(uint id,
         uint owner_id,
         std::string brand,
         std::string model) :
  _id(id), _owner_id(owner_id), _brand(brand), _model(model)
{

}

std::istream& operator>>(std::istream &is, Car& car)
{
  std::cout << "Brand: ";
  is >> car._brand;

  std::cout << "Model: ";
  is >> car._model;

  return is;
}

std::ostream& operator<<(std::ostream &os, const Car& car)
{
  os << car._id << " "
     << car._brand << " "
     << car._model
     << std::endl;

  return os;
}


void Car::set_id(uint id)
{
  _id = id;
}

void Car::set_owner_id(uint owner_id)
{
  _owner_id = owner_id;
}

void Car::set_brand(std::string brand)
{
  _brand = brand;
}

void Car::set_model(std::string model)
{
  _model = model;
}

uint        Car::get_id() const
{
  return _id;
}

uint        Car::get_owner_id() const
{
  return _owner_id;
}

std::string Car::get_brand() const
{
  return _brand;
}

std::string Car::get_model() const
{
  return _model;
}


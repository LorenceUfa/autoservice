#include <owner.hxx>

Owner::Owner()
{

}


Owner::Owner(uint        id,
             std::string name,
             std::string surname,
             std::string sec_name) :
  _id(id), _name(name), _surname(surname), _sec_name(sec_name)
{

}

std::istream& operator>>(std::istream &is, Owner& owner)
{
  std::cout << "Enter surname: ";
  is >> owner._surname;

  std::cout << "Enter name: ";
  is >> owner._name;

  std::cout << "Enter second name: ";
  is >> owner._sec_name;
  return is;
}

std::ostream& operator<<(std::ostream &os, const Owner& owner)
{
  os << owner._id << " "
     << owner._surname << " "
     << owner._name << " "
     << owner._sec_name
     << std::endl;

  return os;
}


void Owner::set_id(uint id)
{
  _id = id;
}

void Owner::set_name(std::string name)
{
  _name = name;
}

void Owner::set_surname(std::string surname)
{
  _surname = surname;
}

void Owner::set_sec_name(std::string sec_name)
{
  _sec_name = sec_name;
}

uint Owner::get_id() const
{
  return _id;
}

std::string Owner::get_name() const
{
  return _name;
}

std::string Owner::get_surname() const
{
  return _surname;
}

std::string Owner::get_sec_name() const
{
  return _sec_name;
}

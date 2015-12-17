#ifndef OWNER
#define OWNER

#include <types.hxx>

class Owner
{
public:
  Owner();

  Owner(uint        id,
        std::string name,
        std::string surname,
        std::string sec_name);

  void set_id(uint id);
  void set_name(std::string name);
  void set_surname(std::string surname);
  void set_sec_name(std::string sec_name);

  uint get_id() const;
  std::string get_name() const;
  std::string get_surname() const;
  std::string get_sec_name() const;

  friend std::istream& operator>>(std::istream &is, Owner& owner);
  friend std::ostream& operator<<(std::ostream &os, const Owner& owner);

private:
  uint          _id;
  std::string   _name;
  std::string   _surname;
  std::string   _sec_name;

};

#endif // OWNER


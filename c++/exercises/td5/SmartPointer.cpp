#include "SmartPointer.hpp"

namespace enseirb
{

void SmartPointer::releasePointer()
{
  *counter = *counter - 1;
  if (*counter == 0)
  {
    delete counter;
    delete data;
  }
  counter = NULL;
}

SmartPointer::SmartPointer(int *data) : data(data), counter(new int(1))
{
}

SmartPointer::SmartPointer(const SmartPointer &p) : data(p.data), counter(p.counter)
{
  *counter = *counter + 1;
}

SmartPointer::~SmartPointer() { releasePointer(); }

int *SmartPointer::operator->() { return data; }

const int *SmartPointer::operator->() const { return data; }

int &SmartPointer::operator*() { return *data; }
const int &SmartPointer::operator*() const { return *data; }

const SmartPointer &SmartPointer::operator=(const SmartPointer &p)
{
  if ((this == &p) || (this->data == p.data))
    return *this;
  releasePointer();
  counter = p.counter;
  *counter = *counter + 1;
  data = p.data;
  return *this;
}

const SmartPointer &SmartPointer::operator=(int *data)
{
  releasePointer();
  counter = new int(1);
  this->data = data;
  return *this;
}

SmartPointer::operator int *()
{
  return data;
}

SmartPointer::operator const int *() const { return data; }

} // namespace enseirb

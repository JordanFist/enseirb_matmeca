#ifndef SMART_POINTER_HPP
#define SMART_POINTER_HPP

#include <cstdlib>

namespace enseirb
{
template <typename T>

class SmartPointer // a l'interieur de la classe on a pas besoin de definir template
{
  T *data;
  int *counter;

  void releasePointer();

public:
  SmartPointer(T *data);

  SmartPointer(const SmartPointer &p);

  ~SmartPointer();

  int *operator->();
  const int *operator->() const;
  T &operator*();
  const int &operator*() const;

  const SmartPointer &operator=(const SmartPointer &p);

  const SmartPointer &operator=(T *data);
  operator T*();
  operator const T *() const;
};

//en dehors de la classe il faut rajouter template et un operateur de porte <T>

template <typename T>
void SmartPointer<T>::releasePointer()
{
  *counter = *counter - 1;
  if (*counter == 0)
  {
    delete counter;
    delete data;
  }
  counter = NULL;
}

template <typename T>
SmartPointer<T>::SmartPointer(T *data) : data(data), counter(new int(1))
{
}

template <typename T>
SmartPointer<T>::SmartPointer(const SmartPointer &p) : data(p.data), counter(p.counter)
{
  *counter = *counter + 1;
}

template <typename T>
SmartPointer<T>::~SmartPointer() { releasePointer(); }

template <typename T>
int *SmartPointer<T>::operator->() { return data; }

template <typename T>
const int *SmartPointer<T>::operator->() const { return data; }

template <typename T>
T &SmartPointer<T>::operator*() { return *data; }

template <typename T>
const int &SmartPointer<T>::operator*() const { return *data; }

template <typename T>
const SmartPointer<T> &SmartPointer<T>::operator=(const SmartPointer &p)
{
  if ((this == &p) || (this->data == p.data))
    return *this;
  releasePointer();
  counter = p.counter;
  *counter = *counter + 1;
  data = p.data;
  return *this;
}

template <typename T>
const SmartPointer<T> &SmartPointer<T>::operator=(T *data)
{
  releasePointer();
  counter = new int(1);
  this->data = data;
  return *this;
}

template <typename T>
SmartPointer<T>::operator T *()
{
  return data;
}

template <typename T>
SmartPointer<T>::operator const T *() const { return data; }

} // namespace enseirb

#endif

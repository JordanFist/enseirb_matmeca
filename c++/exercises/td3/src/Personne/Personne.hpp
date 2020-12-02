#ifndef PERSONNE_HPP
#define PERSONNE_HPP

#include <Chaine.hpp>

namespace enseirb {
class Personne {
private:
  Chaine _nom;

public:
  Personne(const Chaine& c);
  Chaine& nom();
  const Chaine nom() const;
  virtual ~Personne();
};
} // namespace enseirb

#endif
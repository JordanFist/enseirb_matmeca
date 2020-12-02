#include <Chaine.hpp>
#include "Personne.hpp"
namespace enseirb
{
Personne::Personne(const Chaine &c)
{
    _nom = c;
}

Chaine &Personne::nom()
{
    return _nom;
}

const Chaine Personne::nom() const
{
    return _nom;
}
Personne::~Personne() {}
} // namespace enseirb
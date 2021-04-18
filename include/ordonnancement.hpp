// Vous ne devez pas modifier ce fichier.

#ifndef ORDONNANCEMENT
#define ORDONNANCEMENT

#include <vector>

#include "tache.hpp"

// Calcule l'ordonnancement des travaux.
// Entrees:
//   taches: Les taches a ordonnancer
// Sortie:
//   solution: au jour j, on execute la tache taches[solution[j]]
void ordonnancement(const std::vector<Tache>& taches, std::vector<unsigned int>& solution);

#endif

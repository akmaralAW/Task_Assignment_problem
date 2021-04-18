// You should not modify this file.

#include "tache.hpp"

#include <assert.h>

Tache::Tache(unsigned int numero, unsigned int echeance, unsigned int penalite)
  : m_numero(numero),
    m_echeance(echeance),
    m_penalite(penalite)
{
  assert(penalite >= 1);
}

Tache::Tache(const Tache& tache)
  : m_numero(tache.m_numero),      // number
    m_echeance(tache.m_echeance), //deadline
    m_penalite(tache.m_penalite)  //penalty
{
}

// Vous ne devez pas modifier ce fichier.

#ifndef TACHE
#define TACHE

class Tache {
private:
  unsigned int m_numero;
  unsigned int m_echeance;
  unsigned int m_penalite;

public:
  Tache(unsigned int numero, unsigned echeance, unsigned penalite);
  Tache(const Tache& tache);

  inline unsigned int numero() const { return m_numero; }
  inline unsigned int echeance() const { return m_echeance; }
  inline unsigned int penalite() const { return m_penalite; }
};

// Fonctions utiles pour trier les taches par numero, echeance ou penalite.

inline bool compareParNumero(const Tache& tache_1, const Tache& tache_2) {
  return tache_1.numero() < tache_2.numero();
}

inline bool compareParEcheance(const Tache& tache_1, const Tache& tache_2) {
  return tache_1.echeance() < tache_2.echeance();
}

inline bool compareParPenalite(const Tache& tache_1, const Tache& tache_2) {
  return tache_1.penalite() < tache_2.penalite();
}

#endif

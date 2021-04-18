#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "ordonnancement.hpp"

// Test if the instance is valid
// Complexite: Theta(n)
bool instanceValide(const std::vector<Tache>& taches) {
  for (unsigned int i = 0; i < taches.size(); i++) {
    if ((taches[i].numero() != i) || (taches[i].echeance() >= taches.size())) {
      return false;
    }
  }
  return true;
}

// Returns true if the solution vector is a valid solution a
// the instance of the problem. A valid solution must satisfy all
// the constraints, but does not have to minimize the penalty.
// Complexite: Theta(n)
bool solutionValide(const std::vector<Tache>& taches, const std::vector<unsigned int>& solution) {
  assert(instanceValide(taches));
  const unsigned int nb_taches = taches.size();
  const unsigned int nb_jours = solution.size();

  if (nb_jours != nb_taches) {
    std::cerr << "Solution vector size is incorrect\n"<< std::endl;
    return false;
  }
  
  std::vector<bool> taches_realises(nb_taches, false);
  for (unsigned int j = 0; j < nb_jours; j++) {
    if (solution[j] >= nb_taches) {
      std::cerr << "La tache " << solution[j] << " n'existe pas" << std::endl;
      return false;
    }
    if (taches_realises[solution[j]]) {
      std::cerr << "La tache " << solution[j] << " est realise plus d'une fois." << std::endl;
      return false;
    }
    taches_realises[solution[j]] = true;
  }
  return true;    
}


// Returns the penalty for a solution
// Complexite: Theta(n)
unsigned int penaliteSolution(const std::vector<Tache>& taches, const std::vector<unsigned int>& solution) {
  assert(solutionValide(taches, solution));
  unsigned int penalite = 0;
  for (unsigned int j = 0; j < solution.size(); j++) {
    const Tache& tache = taches[solution[j]];
    if (j > tache.echeance()) {
      penalite += tache.penalite();
    }
  }
  return penalite;
}

// This function solves the problem using a brute force algorithm
// Complexite: Theta(n * n!)
void forceBrute(const std::vector<Tache>& taches, std::vector<unsigned int>& solution) {
  assert(instanceValide(taches));
  std::vector<unsigned int> solution_candidate(taches.size());
  for (unsigned int i = 0; i < solution_candidate.size(); i++) {
    solution_candidate[i] = i;
  }
  std::vector<unsigned int> meilleure_solution(solution_candidate);
  do {
    assert(solutionValide(taches, solution_candidate));
    if (penaliteSolution(taches, solution_candidate) < penaliteSolution(taches, meilleure_solution)) {
      meilleure_solution = solution_candidate;
    }
  } while (std::next_permutation(solution_candidate.begin(), solution_candidate.end()));

  solution.swap(meilleure_solution);
  assert(solutionValide(taches, solution));
}

// Displays a solution and its penalty
// Complexite: Theta(n)
void afficheSolution(const std::string& message,
		     const std::vector<Tache>& taches,
		     const std::vector<unsigned int>& solution) {
  std::cerr << message;
  for (std::vector<unsigned int>::const_iterator i = solution.begin(); i != solution.end(); i++) {
    std::cerr << " " << *i;
  }
  if (solutionValide(taches, solution)) {
    std::cerr << " (penalite = " << penaliteSolution(taches, solution) << ")";
  }
  std::cerr << std::endl;
}


// Test the scheduling function and compare its result with a
//// brute force algorithm.
// Complexite: Theta(n * n!)
bool test(const std::string& nom_du_test,
	  const std::vector<Tache>& taches) {
  assert(instanceValide(taches));
  
  std::cerr<< "Execution du test \"" << nom_du_test << "\"" << std::endl;

  std::vector<unsigned int> solution_brute;
  std::vector<unsigned int> solution_vorace;
  forceBrute(taches, solution_brute);
  ordonnancement(taches, solution_vorace); //voracious

  const bool resultat = solutionValide(taches, solution_vorace) &&
    (penaliteSolution(taches, solution_vorace) == penaliteSolution(taches, solution_brute));

  afficheSolution("  solution expected:", taches, solution_brute); //expected
  afficheSolution("  solution obtained: ", taches, solution_vorace); //obtained

  if (resultat) {
    std::cerr << "+1 point: Le test \"" << nom_du_test << "\" a passe" << std::endl;
  } else {
    std::cerr << "+0 point: Le test \"" << nom_du_test << "\" a echoue" << std::endl;
  }

  return resultat;
}

bool premierExempleEnonce() { //first
  Tache taches[3] = {Tache(0, 0, 1),
		     Tache(1, 1, 2),
		     Tache(2, 1, 3)};
  return test("Premier exemple de l'enonce", std::vector<Tache>(taches, taches + 3));
}

bool deuxiemeExempleEnonce() { //second
  Tache taches[4] = {Tache(0, 2, 4),
		     Tache(1, 0, 3),
		     Tache(2, 0, 2),
		     Tache(3, 1, 1)};
  return test("Deuxieme exemple de l'enonce", std::vector<Tache>(taches, taches + 4));
}

bool testAvecQuatreTaches() {
  Tache taches[4] = {Tache(0, 	1,  3),
		     Tache(1, 	3,  4),
		     Tache(2, 	1, 1),
		     Tache(3, 	3, 2)};
  return test("Test avec quatre taches", std::vector<Tache>(taches, taches + 4));
}

bool testAvecSixTaches() {
  Tache taches[6] = {Tache(0, 2, 6),
		     Tache(1, 2, 5),
		     Tache(2, 1, 4),
		     Tache(3, 1, 3),
		     Tache(4, 0, 2),
		     Tache(5, 0, 1)};
  return test("Exemple avec six taches", std::vector<Tache>(taches, taches + 6));
}

bool testAvecBeaucoupDeTaches() {
  Tache taches[10] = {Tache(0, 	1,  5),
		      Tache(1, 	6,  2),
		      Tache(2, 	2, 10),
		      Tache(3, 	4, 3),
		      Tache(4, 	2, 5),
		      Tache(5, 	4, 2),
		      Tache(6, 	7, 6),
		      Tache(7, 	3, 8),
		      Tache(8, 	8, 10),
		      Tache(9, 	4, 7)};
  return test("Test avec beaucoup de taches", std::vector<Tache>(taches, taches + 10));
}


int main(void) {
  //premierExempleEnonce();
  //deuxiemeExempleEnonce();
  testAvecQuatreTaches();
  //testAvecSixTaches();
  //testAvecBeaucoupDeTaches();
  return 0;
}

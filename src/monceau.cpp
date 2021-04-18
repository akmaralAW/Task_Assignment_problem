// This file is only a reminder of the use of heaps. You
// don't have to compile or use it.
//
// This code is written in C ++ 11.
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// Print a triplet of integers
std::ostream& operator<<(std::ostream& os, const std::tuple<int, int, int> t) {
  os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ")";
  return os;
}

// Prints a vector
template <class InputIterator>
void imprime_vecteur(const std::string& message, InputIterator first, InputIterator last) {
  std::cout << message << std::endl;
  for (InputIterator i = first; i != last; i++)
    std::cout << *i << " ";
  std::cout << std::endl;
}

void monceau() { //heap
  int donnees[8] = {3, 6, 2, 0, 24, 12, 68, 42}; //data
  std::vector<int> monceau(donnees, donnees + 8);

  // The function std :: make_heap modifies the vector so that it satisfies the properties of the heap.
  imprime_vecteur("Monceau avant sa creation", monceau.begin(), monceau.end());
  std::make_heap(monceau.begin(), monceau.end()); // Theta(n) ou n = monceau.size()
  imprime_vecteur("Monceau apres sa creation", monceau.begin(), monceau.end());

  // To add an element to the heap
  monceau.push_back(100); // Theta(1)  (analyse amortie)
  std::push_heap(monceau.begin(), monceau.end()); // Theta(log n) en pire cas
  imprime_vecteur("Apres l'ajout de 100", monceau.begin(), monceau.end());

  // To extract the root of the heap
  std::pop_heap(monceau.begin(), monceau.end()); // Place the root at the end of the vector and restore the heap properties. Worst case: Theta (log n)
  int element_extrait = monceau.back();		 // The extracted element is at the end of the vector. Theta (1)
  monceau.pop_back();				 //We remove the last element from the executor. Theta (1) (amortized analysis)
  imprime_vecteur("Apres l'extraction de la racine", monceau.begin(), monceau.end());

  // Here are the same operations, but for a reverse heap
  std::make_heap(monceau.begin(), monceau.end(), std::greater<int>());
  imprime_vecteur("Apres la creation d'un monceau inverse", monceau.begin(), monceau.end());
  monceau.push_back(1);
  std::push_heap(monceau.begin(), monceau.end(), std::greater<int>());
  imprime_vecteur("Apres l'ajout de 1", monceau.begin(), monceau.end());
  std::pop_heap(monceau.begin(), monceau.end(), std::greater<int>());
  element_extrait = monceau.back();
  monceau.pop_back();
  imprime_vecteur("Apres l'extraction de la racine 10", monceau.begin(), monceau.end());

    // You can build heaps of tuples. The operator <enters
    // two tuples compare the first tuples entries. If they
    // are identical, so these are the second entries that are
    // compare.
  std::vector<std::tuple<int, int, int> > monceau_tuples;
  monceau_tuples.push_back(std::make_tuple(1, 2, 3));
  monceau_tuples.push_back(std::make_tuple(2, 3, 1));
  monceau_tuples.push_back(std::make_tuple(3, 1, 2));
  monceau_tuples.push_back(std::make_tuple(3, 2, 1));
  imprime_vecteur("Monceau de tuples avant sa creation", monceau_tuples.begin(), monceau_tuples.end());
  std::make_heap(monceau_tuples.begin(), monceau_tuples.end());
  imprime_vecteur("Monceau de tuples apres sa creation", monceau_tuples.begin(), monceau_tuples.end());
  // ...
}

int main(void) {
  monceau();
  return 0;
}

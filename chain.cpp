#include "chain.hpp"

#include <algorithm>
#include <cmath>

// struct PPState -----------------------------------------------------
// operator< , verifica se <p> è più vicino all'origine rispetto al punto <other>
bool PPState::operator<(PPState const& other) const { return x < other.x; }

// classe Hooke -------------------------------------------------------

// operator() , restituisce la forza elastica tra <p1> e <p2>
double Hooke::operator()(PPState const& p1, PPState const& p2) const {
  return (std::abs(p1.x - p2.x) - m_l) * m_k;
}

// classe Chain -------------------------------------------------------
/* push_back() , inserisce un punto <pps> nel vettore <m_ppses> in coda
e mette in ordine i vettori di <v>*/
void Chain::push_back(PPState const& pps) {
  m_ppses.push_back(pps);
  std::sort(m_ppses.begin(), m_ppses.end());
}

// size(), restituisce il numero di punti in <m_ppses>
int Chain::size() const { return m_ppses.size(); }

// evolve() , fa sviluppare il sistema di punti per un arco di tempo di <delta_t>
void Chain::evolve(double delta_t) {
  for (unsigned int i = 1; i < m_ppses.size() - 1; i++) {
    double acc = 0;
  }
}

// state()
std::vector<PPState> const& Chain::state() const { return m_ppses; }

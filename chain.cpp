#include "chain.hpp"

#include <algorithm>
#include <cmath>

// struct PPState -----------------------------------------------------
// operator< , verifica se <p> è più vicino all'origine rispetto al punto
// <other>
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
  std::sort(m_ppses.begin(), m_ppses.end());  // riordina
  m_N++;                                      // aumenta il numero di elementi
}

// size(), restituisce il numero di punti in <m_ppses>
int Chain::size() const { return m_N; }

// evolve() , fa sviluppare il sistema di punti per un arco di tempo di
// <delta_t>
void Chain::evolve(double delta_t) {
  assert(m_N >= 2);

  std::vector<PPState> vip(m_N);  // creazione di un vettore <vip> identico
                                  // all'evoluzione di <m_ppses>
  for (unsigned int i = 0; i != m_N; i++) {
    double sum_force;  // calcolo della forza
    if (i == 0) {
      sum_force = m_inter(m_ppses[0], m_ppses[1]);
    } else if (i == m_N - 1) {
      sum_force = -1 * (m_inter(m_ppses[m_N - 2], m_ppses[m_N - 1]));
    } else {
      sum_force = -1 * (m_inter(m_ppses[i - 1], m_ppses[i])) +
                  m_inter(m_ppses[i], m_ppses[i + 1]);
    }
    // calcolo e sostituzione dei parametri dei punti di <m_ppses> in base alle
    // equazioni del moto
    double acc = sum_force / m_ppses[i].m;
    vip[i].v = m_ppses[i].v + (acc * delta_t);
    vip[i].x =
        m_ppses[i].x + m_ppses[i].v * delta_t + 0.5 * acc * delta_t * delta_t;
    vip[i].m = m_ppses[i].m;
  }  // end for loop

  m_ppses.clear();  // cancella i valori di <m_ppses>
  m_ppses.reserve(m_N);
  std::copy(vip.begin(), vip.end(),
            std::back_inserter(m_ppses));  // update di <m_ppses>
}

// state()
std::vector<PPState> const& Chain::state() const { return m_ppses; }

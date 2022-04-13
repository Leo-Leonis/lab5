#ifndef CHAIN_HPP
#define CHAIN_HPP

#include <cassert>
#include <vector>

struct PPState {
  double m{};
  double x{};
  double v{};

  bool operator<(PPState const& other) const;
};

class Hooke {
  double m_k;
  double m_l;

 public:
  // costruttore
  Hooke(double k = 0., double l = 0.) : m_k{k}, m_l{l} {
    assert(k >= 0. && l >= 0.);  // valori sensati
  };
  // funzioni membro
  double operator()(PPState const& p1, PPState const& p2) const;
};

class Chain {
  Hooke m_inter;
  std::vector<PPState> m_ppses;

 public:
  // costruttore
  Chain(Hooke const& inter): m_inter{inter}
        {

        };
  // funzioni membro
  void push_back(PPState const& pps);
  int size() const;
  void evolve(double delta_t);
  std::vector<PPState> const& state() const;
};

#endif
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "chain.hpp"

#include "doctest.h"

TEST_CASE("Testing Hooke: std") {
  Hooke hooke(2., 10.);
  PPState p1{1., 0., 0.};
  PPState p2{1., 12., 0.};
  double f = hooke(p1, p2);
  CHECK(f == 4.);
}

TEST_CASE("Testing Hooke: hypercompressed spring") {
  Hooke hooke(2., 10.);
  PPState p1{1., 0., 0.};
  PPState p2{1., 0., 0.};
  double f = hooke(p1, p2);
  CHECK(f == -20.);
}

TEST_CASE("Testing Hooke: equilibrium state") {
  Hooke hooke(2., 10.);
  PPState p1{1., 0., 0.};
  PPState p2{1., 10., 0.};
  double f = hooke(p1, p2);
  CHECK(f == 0.);
}

TEST_CASE("Testing Chain one pair: std") {
  Chain c{Hooke{0.1, 2.}};
  c.push_back({1., 0., 0.});
  const auto state_t = c.state();
  CHECK(state_t.size() == 1);
  c.push_back({1., 4., 0.});
  const auto state_i = c.state();
  CHECK(state_i.size() == 2);

  c.evolve(1.0);
  const auto state_f = c.state();
  CHECK(state_f[0].x == 0.1);
  CHECK(state_f[1].x == 3.9);
  CHECK(state_f[0].v == 0.2);
  CHECK(state_f[1].v == -0.2);
}

TEST_CASE("Testing Chain one pair: equilibrium state") {
  Chain c{Hooke{0.1, 2.}};
  c.push_back({1., 2., 0.});
  const auto state_t = c.state();
  CHECK(state_t.size() == 1);
  c.push_back({1., 0., 0.});
  const auto state_i = c.state();
  CHECK(state_i.size() == 2);

  c.evolve(1.0);
  const auto state_f = c.state();
  CHECK(state_f[0].x == 0.);
  CHECK(state_f[1].x == 2.);
  CHECK(state_f[0].v == 0.);
  CHECK(state_f[1].v == 0.);
}

TEST_CASE("Testing Chain for 3 particles: std") {
  Chain c{Hooke{0.1, 2.}};
  c.push_back({1., 0., 0.5});
  c.push_back({1., 2., 0.});
  c.push_back({1., 4., 0.});
  const auto state_i = c.state();
  c.evolve(1.0);
  c.evolve(1.0);
  const auto state_f = c.state();
  CHECK(state_f[0].x == 0.975);
  CHECK(state_f[0].v == 0.45);
  CHECK(state_f[1].x == 2.025);
  CHECK(state_f[1].v == 0.05);
  CHECK(state_f[2].x == 4.);
  CHECK(state_f[2].v == 0.);

}
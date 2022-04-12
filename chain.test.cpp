#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "chain.hpp"

TEST_CASE("Testing Hooke 1") {
    Hooke hooke(2., 10.);
    PPState p1{1., 0., 0.};
    PPState p2{1., 12., 0.};
    double f = hooke(p1, p2);
    CHECK(f == 4.);
}

TEST_CASE("Testing Hooke 2") {
    Hooke hooke(2., 10.);
    PPState p1{1., 0., 0.};
    PPState p2{1., 0., 0.};
    double f = hooke(p1, p2);
    CHECK(f == -20.);
}

TEST_CASE("Testing Hooke 3") {
    Hooke hooke(2., 10.);
    PPState p1{1., 0., 0.};
    PPState p2{1., 10., 0.};
    double f = hooke(p1, p2);
    CHECK(f == 0.);
}

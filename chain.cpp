#include "chain.hpp"

double Hooke::operator()(PPState const& p1, PPState const& p2) const
{
    double d = p1.x - p2.x;
    if (d < 0) {d *= -1;};
    /* double diff = d - m_l;
    double force = (diff) * m_k;
    return force; */
    return (d - m_l) * m_k;
}


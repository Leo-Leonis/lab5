#include "chain.hpp"

// classe Hooke -------------------------------------------------------
double Hooke::operator()(PPState const& p1, PPState const& p2) const
{
    double d = p1.x - p2.x;
    if (d < 0) {d *= -1;};
    /* double diff = d - m_l;
    double force = (diff) * m_k;
    return force; */
    return (d - m_l) * m_k;
}

// classe Chain ------------------------------------------------------

void Chain::push_back(PPState const& pps) {
    m_ppses.push_back(pps);
}

int Chain::size() const {
    return m_ppses.size();
}
    
void Chain::evolve(double delta_t){
    double acc = ;
}

std::vector<PPState> const& Chain::state() const {
    return m_ppses;
}


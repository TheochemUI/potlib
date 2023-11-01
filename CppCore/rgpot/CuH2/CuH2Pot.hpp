#pragma once
// MIT License
// Copyright 2023--present Rohit Goswami <HaoZeke>
// clang-format off
#include <utility>
// clang-format on
#include "rgpot/Potential.hpp"
#include "rgpot/types/AtomMatrix.hpp"
using rgpot::types::AtomMatrix;

// natms(2), ndim, U(1), R(ndim), F(ndim), box(3)
extern "C" void c_force_eam(int *natms, int ndim, double *box, double *R,
                            double *F, double *U);

namespace rgpot {
class CuH2Pot : public Potential {
public:
  // Constructor initializes potential type and atom properties
  CuH2Pot() : Potential(PotType::CuH2) {}

  std::pair<double, AtomMatrix>
  operator()(const AtomMatrix &positions,
             const std::vector<int> &atmtypes,
             const std::array<std::array<double, 3>, 3> &box) const override;

private:
  // Variables
  // EON compatible function
  void force(long N, const double *R, const int *atomicNrs, double *F,
             double *U, const double *box) const;
};
} // namespace rgpot

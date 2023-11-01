#pragma once
// MIT License
// Copyright 2023--present Rohit Goswami <HaoZeke>
// clang-format off
#include <utility>
// clang-format on
#include "rgpot/Potential.hpp"
#include "rgpot/types/AtomMatrix.hpp"
using rgpot::types::AtomMatrix;

namespace rgpot {
class LJPot : public Potential {
public:
  // Constructor initializes potential type and atom properties
  LJPot() : Potential(PotType::LJ), u0{1.0}, cuttOffR{15.0}, psi{1.0} {}

  std::pair<double, AtomMatrix>
  operator()(const AtomMatrix &positions,
             const std::vector<int> &atmtypes,
             const std::array<std::array<double, 3>, 3> &box) const override;

private:
  // Variables
  double u0;
  double cuttOffR;
  double psi;
  double cuttOffU;
  // EON compatible function
  void force(long N, const double *R, const int *atomicNrs, double *F,
             double *U, const double *box) const;
};
} // namespace rgpot

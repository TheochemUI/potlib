#pragma once
// MIT License
// Copyright 2023--present Rohit Goswami <HaoZeke>
// clang-format off
#include <utility>
// clang-format on
#include "rgpot/Potential.hpp"

namespace rgpot {
class LJPot : public Potential {
public:
  // Constructor initializes potential type and atom properties
  LJPot() : Potential(PotType::LJ), u0{1.0}, cuttOffR{15.0}, psi{1.0} {}

  std::pair<double, AtomMatrix>
  operator()(const Eigen::Ref<const AtomMatrix> &positions,
             const Eigen::Ref<const Eigen::VectorXi> &atmtypes,
             const Eigen::Ref<const Eigen::Matrix3d> &box) const override;

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

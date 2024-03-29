// MIT License
// Copyright 2023--present Rohit Goswami <HaoZeke>
// clang-format off
#include <limits>
#include <set>
// clang-format on
#include "rgpot/CuH2/CuH2Pot.hpp"
#include "rgpot/types/AtomMatrix.hpp"
using rgpot::types::AtomMatrix;

namespace rgpot {
std::pair<double, AtomMatrix>
CuH2Pot::operator()(const AtomMatrix &positions,
                    const std::vector<int> &atmtypes,
                    const std::array<std::array<double, 3>, 3> &box) const {
  std::multiset<double> natmc;
  const auto N = positions.rows();
  int natms[2]{0, 0};                // Always Cu, then H
  int ndim{3 * static_cast<int>(N)}; // see main.f90
  for (auto idx : atmtypes) {
    natmc.insert(idx);
  }
  if (natmc.count(29) <= 0 || natmc.count(1) <= 0) {
    throw std::runtime_error("The system does not have Copper or Hydrogen, but "
                             "the CuH2 potential was requested");
  }
  natms[0] = natmc.count(29); // Cu
  natms[1] = natmc.count(1);  // H
  if (natms[0] + natms[1] != N) {
    throw std::runtime_error("The system has other atom types, but the CuH2 "
                             "potential was requested");
  }

  // The box only takes the diagonal (assumes cubic)
  double box_eam[]{box[0][0], box[1][1], box[2][2]};
  double energy{std::numeric_limits<double>::infinity()};
  AtomMatrix forces = AtomMatrix::Zero(N, 3);
  c_force_eam(natms, ndim, box_eam, const_cast<double *>(positions.data()),
              forces.data(), &energy);

  return {energy, forces};
}
} // namespace rgpot

// MIT License
// Copyright 2023--present Rohit Goswami <HaoZeke>
#include "CuH2Pot.hpp"

namespace rgpot {
std::pair<double, AtomMatrix>
CuH2Pot::operator()(const Eigen::Ref<const AtomMatrix> &positions,
                    const Eigen::Ref<const VectorXi> &atmtypes,
                    const Eigen::Ref<const Eigen::Matrix3d> &box) const {
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
  double box_eam[]{box(0, 0), box(1, 1), box(2, 2)};
  double energy{std::numeric_limits<double>::infinity()};
  AtomMatrix forces{Eigen::MatrixXd::Zero(N, 3)};

  c_force_eam(natms, ndim, box_eam, const_cast<double *>(positions.data()),
              forces.data(), &energy);

  return {energy, forces};
}
} // namespace rgpot

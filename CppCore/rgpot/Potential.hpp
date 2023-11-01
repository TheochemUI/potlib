#pragma once
// MIT License
// Copyright 2023--present Rohit Goswami <HaoZeke>
// clang-format off
#include <utility>
// clang-format on

#include "rgpot/pot_types.hpp"

namespace rgpot {
class Potential {
public:
  // Constructor takes potential type
  explicit Potential(PotType inp_type) : m_type(inp_type) {}

  // Operator() to calculate energy and forces for the given coordinates and
  // atom types
  virtual std::pair<double, AtomMatrix>
  operator()(const Eigen::Ref<const AtomMatrix> &positions,
             const Eigen::Ref<const Eigen::VectorXi> &atmtypes,
             const Eigen::Ref<const Eigen::Matrix3d> &box) const = 0;

  virtual ~Potential() = default;

private:
  PotType m_type;
};
} // namespace rgpot

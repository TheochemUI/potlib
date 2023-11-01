#pragma once
// MIT License
// Copyright 2023--present Rohit Goswami <HaoZeke>

#include "pot_types.hpp"

namespace rgpot {
class Potential {
public:
  // Constructor takes potential type
  Potential(PotType inp_type) : m_type(inp_type) {}

  // Operator() to calculate energy and forces for the given coordinates and
  // atom types
  virtual std::pair<double, AtomMatrix>
  operator()(const Eigen::Ref<const AtomMatrix> &positions,
             const Eigen::Ref<const VectorXi> &atmtypes,
             const Eigen::Ref<const Eigen::Matrix3d> &box) const = 0;

  virtual ~Potential() = default;

private:
  PotType m_type;
};
} // namespace rgpot

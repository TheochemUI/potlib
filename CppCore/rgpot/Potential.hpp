#pragma once
// MIT License
// Copyright 2023--present Rohit Goswami <HaoZeke>
// clang-format off
#include <utility>
#include <vector>
// clang-format on

#include "rgpot/pot_types.hpp"
#include "rgpot/types/AtomMatrix.hpp"

using rgpot::types::AtomMatrix;

namespace rgpot {
class Potential {
public:
  // Constructor takes potential type
  explicit Potential(PotType inp_type) : m_type(inp_type) {}

  // Operator() to calculate energy and forces for the given coordinates and
  // atom types
  virtual std::pair<double, AtomMatrix>
  operator()(const AtomMatrix &positions, const std::vector<int> &atmtypes,
             const std::array<std::array<double, 3>, 3> &box) const = 0;

  virtual ~Potential() = default;

private:
  PotType m_type;
};
} // namespace rgpot

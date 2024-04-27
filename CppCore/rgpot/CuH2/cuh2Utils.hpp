#pragma once
// MIT License
// Copyright 2024--present Rohit Goswami <HaoZeke>
// clang-format off
#include <utility>
#include <vector>
// clang-format on
#include "rgpot/types/AtomMatrix.hpp"
#ifdef WITH_XTENSOR
#include "xtensor-blas/xlinalg.hpp"
#include "xtensor/xarray.hpp"
#include "xtensor/xview.hpp"
#endif
using rgpot::types::AtomMatrix;

namespace rgpot {
namespace cuh2 {
namespace utils {
#ifdef WITH_XTENSOR
namespace xts {
xt::xtensor<double, 2>
perturb_positions(const xt::xtensor<double, 2> &base_positions,
                  const xt::xtensor<int, 1> &atmNumVec, double hcu_dist,
                  double hh_dist);
std::pair<double, double>
calculateDistances(const xt::xtensor<double, 2> &positions,
                   const xt::xtensor<int, 1> &atmNumVec);

// TODO(rg): This is duplicated from xts::func !!
template <class E, class ScalarType = double>
void ensure_normalized(E &&vector, bool is_normalized = false,
                       ScalarType tol = static_cast<ScalarType>(1e-6)) {
  if (!is_normalized) {
    auto norm = xt::linalg::norm(vector, 2);
    if (norm == 0.0) {
      throw std::runtime_error(
          "Cannot normalize a vector whose norm is smaller than tol");
    }
    if (std::abs(norm - static_cast<ScalarType>(1.0)) >= tol) {
      vector /= norm;
    }
  }
}

} // namespace xts
#endif
} // namespace utils

} // namespace cuh2

} // namespace rgpot

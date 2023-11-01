// MIT License
// Copyright 2023--present Rohit Goswami <HaoZeke>
#pragma once

// Include required headers
#include <array>
#include <vector>
#include <xtensor/xtensor.hpp>

#include "rgpot/types/AtomMatrix.hpp"

using rgpot::types::AtomMatrix;

namespace rgpot {
namespace types {
namespace adapt {
namespace xtensor {

// Convert from xtensor::xtensor<double, 2> to AtomMatrix
inline AtomMatrix convertToAtomMatrix(const xt::xtensor<double, 2> &matrix) {
  AtomMatrix result(matrix.shape(0), matrix.shape(1));
  for (size_t i = 0; i < matrix.shape(0); ++i) {
    for (size_t j = 0; j < matrix.shape(1); ++j) {
      result(i, j) = matrix(i, j);
    }
  }
  return result;
}

// Convert from AtomMatrix to xtensor::xtensor<double, 2>
inline xt::xtensor<double, 2> convertToXtensor(const AtomMatrix &atomMatrix) {
  xt::xtensor<double, 2> result =
      xt::zeros<double>({atomMatrix.rows(), atomMatrix.cols()});
  for (size_t i = 0; i < atomMatrix.rows(); ++i) {
    for (size_t j = 0; j < atomMatrix.cols(); ++j) {
      result(i, j) = atomMatrix(i, j);
    }
  }
  return result;
}

// Convert from xtensor::xtensor<int, 1> to std::vector<int>
template <typename T>
std::vector<T> convertToVector(const xt::xtensor<T, 1> &vector) {
  return std::vector<T>(vector.begin(), vector.end());
}

// Convert from xt::xtensor<double, 2> with shape (3,3) to
// std::array<std::array<double, 3>, 3>
inline std::array<std::array<double, 3>, 3>
convertToArray3x3(const xt::xtensor<double, 2> &matrix) {
  std::array<std::array<double, 3>, 3> result;
  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      result[i][j] = matrix(i, j);
    }
  }
  return result;
}

} // namespace xtensor
} // namespace adapt
} // namespace types
} // namespace rgpot

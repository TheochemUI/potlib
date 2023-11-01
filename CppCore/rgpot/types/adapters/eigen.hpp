#pragma once
// MIT License
// Copyright 2023--present Rohit Goswami <HaoZeke>
// clang-format off
#include <Eigen/Dense>
// clang-format on
#include <array>
#include <vector>

#include "rgpot/types/AtomMatrix.hpp"

using rgpot::types::AtomMatrix;

namespace rgpot {
namespace types {
namespace adapt {
namespace eigen {

// Convert from Eigen::MatrixXd to AtomMatrix
inline AtomMatrix convertToAtomMatrix(const Eigen::MatrixXd &matrix) {
  AtomMatrix result(matrix.rows(), matrix.cols());
  for (int i = 0; i < matrix.rows(); ++i) {
    for (int j = 0; j < matrix.cols(); ++j) {
      result(i, j) = matrix(i, j);
    }
  }
  return result;
}

// Convert from AtomMatrix to Eigen::MatrixXd
inline Eigen::MatrixXd convertToEigen(const AtomMatrix &atomMatrix) {
  return Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic,
                                        Eigen::RowMajor>>(
      atomMatrix.data(), atomMatrix.rows(), atomMatrix.cols());
}

// Convert from Eigen::VectorXi to std::vector<int>
template <typename T>
std::vector<T> convertToVector(const Eigen::VectorX<T> &vector) {
  return std::vector<T>(vector.data(), vector.data() + vector.size());
}

// Convert from Matrix3d to std::array<std::array<double, 3>, 3>
inline std::array<std::array<double, 3>, 3>
convertToEigen3d(const Eigen::Matrix3d &matrix) {
  std::array<std::array<double, 3>, 3> result;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      result[i][j] = matrix(i, j);
    }
  }
  return result;
}

} // namespace eigen
} // namespace adapt
} // namespace types
} // namespace rgpot

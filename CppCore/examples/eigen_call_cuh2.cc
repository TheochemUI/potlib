// MIT License
// Copyright 2023--present Rohit Goswami <HaoZeke>
// clang-format off
#include <fmt/ostream.h>
#include <cstdlib>
// clang-format on
#include "rgpot/CuH2/CuH2Pot.hpp"
#include "rgpot/types/adapters/eigen.hpp"
using rgpot::types::AtomMatrix;

int main(void) {
  auto cuh2pot = rgpot::CuH2Pot();
  Eigen::MatrixXd positions{
      {0.63940268750835, 0.90484742551374, 6.97516498544584}, // Cu
      {3.19652040936288, 0.90417430354811, 6.97547796369474}, // Cu
      {8.98363230369760, 9.94703496017833, 7.83556854923689}, // H
      {7.64080177576300, 9.94703114803832, 7.83556986121272}, // H
  };

  Eigen::VectorXi atomTypes{{29, 29, 1, 1}};
  Eigen::Matrix3d boxMatrix{{15, 0, 0}, //
                      {0, 20, 0}, //
                      {0, 0, 30}};
  auto [energy, forces] = cuh2pot(convertToAtomMatrix(positions), convertToVector(atomTypes), convertToEigen3d(boxMatrix));
  auto forcesEig = convertToEigen(forces);
  fmt::print("Got energy {}\n Forces:\n{}", energy, fmt::streamed(forcesEig));
  return EXIT_SUCCESS;
}
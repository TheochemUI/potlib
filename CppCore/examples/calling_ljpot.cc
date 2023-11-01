// MIT License
// Copyright 2023--present Rohit Goswami <HaoZeke>
// clang-format off
#include <fmt/ostream.h>
#include <cstdlib>
// clang-format on
#include "../src/LennardJones/LJPot.hpp"

int main(void) {
  using rgpot::AtomMatrix;
  auto ljpot = LJPot();
  AtomMatrix positions{
      {1, 2, 3},       //
      {1.5, 2.5, 3.5}, //
      {4, 5, 6}        //
  };
  Eigen::VectorXi atmtypes{{0, 0, 0}};
  Eigen::Matrix3d box{{15, 0, 0}, //
                      {0, 20, 0}, //
                      {0, 0, 30}};
  auto [energy, forces] = ljpot(positions, atmtypes, box);
  fmt::print("Got energy {}\n Forces:\n{}", energy, fmt::streamed(forces));
  return EXIT_SUCCESS;
}

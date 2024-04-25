// MIT License
// Copyright 2023--present Rohit Goswami <HaoZeke>
#include <catch2/catch_all.hpp>

#include "rgpot/CuH2/cuh2Utils.hpp"

TEST_CASE("extract_positions correctly extracts position vectors",
          "[extract_positions]") {
  yodecon::types::ConFrameVec conFrameVec;
  conFrameVec.prebox_header = {"Generated by eOn", ""};
  conFrameVec.boxl = {25.0, 25.0, 25.0};
  conFrameVec.angles = {90.0, 90.0, 90.0};
  conFrameVec.postbox_header = {"", ""};
  conFrameVec.natm_types = 4;
  conFrameVec.natms_per_type = {2, 4, 6, 1};
  conFrameVec.masses_per_type = {15.99, 12.011, 1.008, 32.065};
  conFrameVec.symbol.push_back("O");
  conFrameVec.x.push_back(10.477713);
  conFrameVec.y.push_back(12.379463);
  conFrameVec.z.push_back(12.871778);
  conFrameVec.is_fixed.push_back(false);
  conFrameVec.atom_id.push_back(1);
  auto positions = rgpot::cuh2::utils::xts::extract_positions(conFrameVec);

  REQUIRE(positions.shape()[0] == 1); // 1 atoms
  REQUIRE(positions.shape()[1] == 3); // 3 dimensions

  REQUIRE(positions(0, 0) == 10.477713);
  REQUIRE(positions(0, 1) == 12.379463);
  REQUIRE(positions(0, 2) == 12.871778);
}

TEST_CASE("perturb_positions correctly perturbs hydrogen atom positions and "
          "sets new z-coordinate",
          "[perturb_positions]") {
  xt::xtensor<double, 2> base_positions = {{0, 0, 0}, {1, 0, 0}, {0.5, 0.5, 2}};
  xt::xtensor<int, 1> atmNumVec = {1, 1, 29}; // Hydrogens and one Copper
  double hcu_dist = 1.5;
  double hh_dist = 1.0;

  auto perturbed_positions = rgpot::cuh2::utils::xts::perturb_positions(
      base_positions, atmNumVec, hcu_dist, hh_dist);

  // Expected behavior
  REQUIRE_THAT(perturbed_positions(0, 2),
               Catch::Matchers::WithinAbs(2.0 + hcu_dist, 1e-4));
  REQUIRE_THAT(perturbed_positions(1, 2),
               Catch::Matchers::WithinAbs(2.0 + hcu_dist, 1e-4));

  // Check if the distance between hydrogens is approximately 1.0
  auto hDist = xt::linalg::norm(xt::row(perturbed_positions, 0) -
                                xt::row(perturbed_positions, 1));
  REQUIRE_THAT(hDist, Catch::Matchers::WithinAbs(hh_dist, 1e-4));
}

TEST_CASE("calculateDistances calculates distances correctly",
          "[calculateDistances]") {
  xt::xtensor<double, 2> positions = {
      {0.0, 0.0, 3.0}, {1.0, 0.0, 3.0}, {0.5, 0.5, 2.0}};
  xt::xtensor<int, 1> atmNumVec = {1, 1, 29}; // Hydrogens and one Copper

  auto distances =
      rgpot::cuh2::utils::xts::calculateDistances(positions, atmNumVec);
  // Distance between hydrogens
  REQUIRE_THAT(distances.first, Catch::Matchers::WithinAbs(1.0, 1e-4));
  // Distance from H to top Cu layer
  REQUIRE_THAT(distances.second, Catch::Matchers::WithinAbs(1.0, 1e-4));
}

// Additional tests to cover error handling and unexpected inputs
TEST_CASE("perturb_positions throws when unexpected atom numbers arepresent",
          "[perturb_positions]") {
  xt::xtensor<double, 2> base_positions = {{0, 0, 0}, {1, 0, 0}};
  xt::xtensor<int, 1> atmNumVec = {1, 30}; // Invalid atom number

  REQUIRE_THROWS_AS(rgpot::cuh2::utils::xts::perturb_positions(
                        base_positions, atmNumVec, 1.5, 1.0),
                    std::runtime_error);
}

TEST_CASE(
    "calculateDistances throws when not exactly two hydrogens are present",
    "[calculateDistances]") {
  xt::xtensor<double, 2> positions = {{0.0, 0.0, 3.0}, {0.5, 0.5, 2.0}};
  xt::xtensor<int, 1> atmNumVec = {1, 29}; // Not two Hydrogens

  REQUIRE_THROWS_AS(
      rgpot::cuh2::utils::xts::calculateDistances(positions, atmNumVec),
      std::runtime_error);
}

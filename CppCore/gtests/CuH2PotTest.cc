/*
 * CuH2PotTest.hpp
 *
 *  Created on: 20 April 2024
 *      Author: Rohit Goswami
 *     Company: University of Iceland
 */

#include "../src/CuH2/CuH2Pot.hpp"
#include <gtest/gtest.h>

TEST(CuH2PotTest, EnergyAndForces) {
  using namespace rgpot;
  // Define test inputs
  auto cuh2pot = CuH2Pot();
  AtomMatrix positions{
      {0.63940268750835, 0.90484742551374, 6.97516498544584}, // Cu
      {3.19652040936288, 0.90417430354811, 6.97547796369474}, // Cu
      {8.98363230369760, 9.94703496017833, 7.83556854923689}, // H
      {7.64080177576300, 9.94703114803832, 7.83556986121272}  // H
  };
  Eigen::VectorXi atmtypes{{29, 29, 1, 1}};
  Eigen::Matrix3d box{{15.345599999999999, 0, 0}, //
                      {0, 21.702000000000002, 0}, //
                      {0, 0, 100.00000000000000}};
  auto [energy, forces] = cuh2pot(positions, atmtypes, box);

  // Expected energy and forces, using main.f90
  double expected_energy = -2.7114096242662238;
  // clang-format off
  AtomMatrix expected_forces {
  {1.4919411183978113,  -3.9273058476626193E-004,  1.8260603127768336E-004},
  {-1.4919411183978113,  3.9273058476626193E-004, -1.8260603127768336E-004},
  {-4.9118653085630006, -1.3944215503304855E-005,  4.7990036210569753E-006},
  {4.9118653085630006,   1.3944215503304855E-005, -4.7990036210569753E-006}
  };
  // clang-format on

  // Check that computed energy and forces match expected values
  ASSERT_NEAR(energy, expected_energy, 1e-6);
  ASSERT_TRUE(forces.isApprox(expected_forces, 1e-6));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

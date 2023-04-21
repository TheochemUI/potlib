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
  Eigen::Matrix3d box{{15, 0, 0}, //
                      {0, 20, 0}, //
                      {0, 0, 30}};
  auto [energy, forces] = cuh2pot(positions, atmtypes, box);

  // Expected energy and forces, using main.f90
  double expected_energy = -2.7114093289369636;
  // clang-format off
  AtomMatrix expected_forces {
  {1.4919412444104894,  -3.9273061793716405E-004,  1.8260604670099651E-004},
  {-1.4919412444104894,  3.9273061793716405E-004, -1.8260604670099651E-004},
  {-4.9118648185366567, -1.3944214112176943E-005,  4.7990031422901425E-006},
  {4.9118648185366567,   1.3944214112176943E-005, -4.7990031422901425E-006}
  };
  // clang-format on

  // Check that computed energy and forces match expected values
  ASSERT_DOUBLE_EQ(energy, expected_energy);
  ASSERT_TRUE(forces.isApprox(expected_forces));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

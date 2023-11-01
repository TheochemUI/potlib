#include "../src/LennardJones/LJPot.hpp"
#include <cstdlib>
#include <fmt/ostream.h>

int main(void) {
  using namespace rgpot;
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

// MIT License
// Copyright 2023--present Rohit Goswami <HaoZeke>
// clang-format off
#include <algorithm>
#include <limits>
// clang-format on
#include "rgpot/CuH2/cuh2Utils.hpp"
using rgpot::types::AtomMatrix;

#ifdef WITH_XTENSOR
namespace rgpot::cuh2::utils::xts {

xt::xtensor<double, 2>
extract_positions(const yodecon::types::ConFrameVec &frame) {
  size_t n_atoms = frame.x.size();
  std::array<size_t, 2> shape = {static_cast<size_t>(n_atoms), 3};

  xt::xtensor<double, 2> positions = xt::empty<double>(shape);
  for (size_t i = 0; i < n_atoms; ++i) {
    positions(i, 0) = frame.x[i];
    positions(i, 1) = frame.y[i];
    positions(i, 2) = frame.z[i];
  }

  return positions;
}

xt::xtensor<double, 2>
perturb_positions(const xt::xtensor<double, 2> &base_positions,
                  const xt::xtensor<int, 1> &atmNumVec, double hcu_dist,
                  double hh_dist) {
  xt::xtensor<double, 2> positions = base_positions;
  std::vector<size_t> hIndices, cuIndices;

  for (size_t i = 0; i < atmNumVec.size(); ++i) {
    if (atmNumVec(i) == 1) { // Hydrogen atom
      hIndices.push_back(i);
    } else if (atmNumVec(i) == 29) { // Copper atom
      cuIndices.push_back(i);
    } else {
      throw std::runtime_error("Unexpected atomic number");
    }
  }

  if (hIndices.size() != 2) {
    throw std::runtime_error("Expected exactly two hydrogen atoms");
  }

  // Compute the midpoint of the hydrogens
  auto hMidpoint =
      (xt::row(positions, hIndices[0]) + xt::row(positions, hIndices[1])) / 2;

  // TODO(rg): This is buggy in cuh2vizR!! (maybe)
  // Compute the HH direction
  xt::xtensor<double, 1> hh_direction;
  size_t h1_idx, h2_idx;
  if (positions(hIndices[0], 0) < positions(hIndices[1], 0)) {
    hh_direction =
        xt::row(positions, hIndices[1]) - xt::row(positions, hIndices[0]);
    ensure_normalized(hh_direction);
    h1_idx = hIndices[0];
    h2_idx = hIndices[1];
  } else {
    hh_direction =
        xt::row(positions, hIndices[0]) - xt::row(positions, hIndices[1]);
    ensure_normalized(hh_direction);
    h1_idx = hIndices[1];
    h2_idx = hIndices[0];
  }

  // Set the new position of the hydrogens using the recorded indices
  xt::row(positions, h1_idx) = hMidpoint - (0.5 * hh_dist) * hh_direction;
  xt::row(positions, h2_idx) = hMidpoint + (0.5 * hh_dist) * hh_direction;

  // Find the z-coordinate of the topmost Cu layer
  double maxCuZ = std::numeric_limits<double>::lowest();
  for (auto cuIndex : cuIndices) {
    maxCuZ = std::max(maxCuZ, positions(cuIndex, 2));
  }

  // Compute the new z-coordinate for the H atoms
  double new_z = maxCuZ + hcu_dist;

  // Update the z-coordinates of the H atoms
  for (auto hIndex : hIndices) {
    positions(hIndex, 2) = new_z;
  }

  return positions;
}

std::pair<double, double>
calculateDistances(const xt::xtensor<double, 2> &positions,
                   const xt::xtensor<int, 1> &atmNumVec) {
  std::vector<size_t> hIndices, cuIndices;
  for (size_t i = 0; i < atmNumVec.size(); ++i) {
    if (atmNumVec(i) == 1) { // Hydrogen atom
      hIndices.push_back(i);
    } else if (atmNumVec(i) == 29) { // Copper atom
      cuIndices.push_back(i);
    } else {
      throw std::runtime_error("Unexpected atomic number");
    }
  }

  if (hIndices.size() != 2) {
    throw std::runtime_error("Expected exactly two hydrogen atoms");
  }

  // Calculate the distance between Hydrogen atoms
  double hDistance =
      xt::linalg::norm(xt::view(positions, hIndices[0], xt::all()) -
                       xt::view(positions, hIndices[1], xt::all()));

  // Calculate the midpoint of Hydrogen atoms
  xt::xtensor<double, 1> hMidpoint =
      (xt::view(positions, hIndices[0], xt::all()) +
       xt::view(positions, hIndices[1], xt::all())) /
      2.0;

  // Find the z-coordinate of the topmost Cu layer
  double maxCuZ = std::numeric_limits<double>::lowest();
  for (size_t cuIndex : cuIndices) {
    maxCuZ = std::max(maxCuZ, positions(cuIndex, 2));
  }

  double cuSlabDist = positions(hIndices[0], 2) - maxCuZ;

  return std::make_pair(hDistance, cuSlabDist);
}

} // namespace rgpot::cuh2::utils::xts
#endif

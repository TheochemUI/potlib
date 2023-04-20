#include "LJPot.hpp"

namespace rgpot {

std::pair<double, AtomMatrix>
LJPot::operator()(const Eigen::Ref<const AtomMatrix> &positions,
                  const Eigen::Ref<const VectorXi> &atmtypes,
                  const Eigen::Ref<const Eigen::Matrix3d> &box) const {
  double energy{std::numeric_limits<double>::infinity()};
  long nAtoms{positions.rows()};
  AtomMatrix forces{Eigen::MatrixXd::Zero(nAtoms, 3)};
  this->force(nAtoms, positions.data(), atmtypes.data(), forces.data(), &energy,
              box.data());
  return std::make_pair(energy, forces);
}

// pointer to number of atoms, pointer to array of positions
// pointer to array of forces, pointer to internal energy
// address to super-cell size
void LJPot::force(long N, const double *R, const int *atomicNrs, double *F,
                  double *U, const double *box) const {
  // This is adapted, untouched from EON's BSD 3 clause implementation
  // Original source:
  // https://github.com/TheochemUI/EONgit/blob/stable/client/potentials/LJ/LJ.cpp
  // Copyright (c) 2010, EON Development Team
  // All rights reserved. BSD 3-Clause License.
  double diffR{0}, diffRX{0}, diffRY{0}, diffRZ{0}, dU{0}, a{0}, b{0};
  *U = 0;
  for (int i = 0; i < N; i++) {
    F[3 * i] = 0;
    F[3 * i + 1] = 0;
    F[3 * i + 2] = 0;
  }
  // Initializing end

  for (int i = 0; i < N - 1; i++) {
    for (int j = i + 1; j < N; j++) {
      diffRX = R[3 * i] - R[3 * j];
      diffRY = R[3 * i + 1] - R[3 * j + 1];
      diffRZ = R[3 * i + 2] - R[3 * j + 2];

      diffRX =
          diffRX -
          box[0] *
              floor(diffRX / box[0] +
                    0.5); // floor = largest integer value less than argument
      diffRY = diffRY - box[4] * floor(diffRY / box[4] + 0.5);
      diffRZ = diffRZ - box[8] * floor(diffRZ / box[8] + 0.5);

      diffR = sqrt(diffRX * diffRX + diffRY * diffRY + diffRZ * diffRZ);

      if (diffR < cuttOffR) {
        // 4u0((psi/r0)^12-(psi/r0)^6)
        a = pow(psi / diffR, 6);
        b = 4 * u0 * a;

        *U = *U + b * (a - 1) - cuttOffU;

        dU = -6 * b / diffR * (2 * a - 1);
        // F is the negative derivative
        F[3 * i] = F[3 * i] - dU * diffRX / diffR;
        F[3 * i + 1] = F[3 * i + 1] - dU * diffRY / diffR;
        F[3 * i + 2] = F[3 * i + 2] - dU * diffRZ / diffR;

        F[3 * j] = F[3 * j] + dU * diffRX / diffR;
        F[3 * j + 1] = F[3 * j + 1] + dU * diffRY / diffR;
        F[3 * j + 2] = F[3 * j + 2] + dU * diffRZ / diffR;
      }
    }
  }
  return;
}
} // namespace rgpot

#pragma once
#include "../Potential.hpp"

// natms(2), ndim, U(1), R(ndim), F(ndim), box(3)
extern "C" void c_force_eam(int *natms, int ndim, double *box, double *R,
                            double *F, double *U);

namespace rgpot {
class CuH2Pot : public Potential {
public:
  // Constructor initializes potential type and atom properties
  CuH2Pot() : Potential(PotType::CuH2) {}

  std::pair<double, AtomMatrix>
  operator()(const Eigen::Ref<const AtomMatrix> &positions,
             const Eigen::Ref<const VectorXi> &atmtypes,
             const Eigen::Ref<const Eigen::Matrix3d> &box) const override;

private:
  // Variables
  // EON compatible function
  void force(long N, const double *R, const int *atomicNrs, double *F,
             double *U, const double *box) const;
};
} // namespace rgpot

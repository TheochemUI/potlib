/**
 * @file mopac_c_abi.h
 * @brief C ABI between MOPACPot and libmopacc.so (OmniPotentRPC/mopacc).
 *
 * Packed MopacCParams, not Cap'n Proto. Units: geometry Angstrom, energy
 * Hartree, gradient Hartree/Bohr. Keep this header in lockstep with
 * mopacc/include/mopacc.h.
 */
#pragma once

#include <stddef.h>

#define RGPOT_MOPACC_C_ABI_VERSION 1

#ifdef __cplusplus
extern "C" {
#endif

#if defined(RGPOT_MOPACC_BUILD) && (defined(_WIN32) || defined(_WIN64))
#define RGPOT_MOPACC_API __declspec(dllexport)
#else
#define RGPOT_MOPACC_API
#endif

#define MOPACC_MODEL_PM7 0
#define MOPACC_MODEL_PM6_D3H4 1
#define MOPACC_MODEL_PM6_ORG 2
#define MOPACC_MODEL_PM6 3
#define MOPACC_MODEL_AM1 4
#define MOPACC_MODEL_RM1 5

typedef struct MopacCParams {
  int charge;
  int spin;
  int model;
  double tolerance;
  int max_time;
} MopacCParams;

typedef struct MopacCResult {
  int ok;
  double energy_h;
  char message[512];
} MopacCResult;

RGPOT_MOPACC_API int mopacc_set_params(const void *params,
                                       size_t params_size_bytes);

RGPOT_MOPACC_API MopacCResult mopacc_energy_gradient(
    int n_atoms, const double *positions_ang, const int *atomic_numbers,
    const void *params, size_t params_size_bytes, double *grad_h_bohr);

RGPOT_MOPACC_API int mopacc_c_abi_version(void);
RGPOT_MOPACC_API int mopacc_available(void);
RGPOT_MOPACC_API const char *mopacc_version(void);

#ifdef __cplusplus
}
#endif

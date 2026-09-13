# MOPACPot — consumer of the split mopacc engine

rgpot dlopens [`libmopacc.so`](https://github.com/OmniPotentRPC/mopacc).
This directory is the frontend only. OpenMOPAC lives in mopacc.

Params are packed `MopacCParams`. Default Hamiltonian is AM1; the
engine is every OpenMOPAC model plus SCF / relax / vibe.

```
app
  MOPACPot
    dlopen(MOPACC_LIBRARY / RGPOT_MOPACC_ENGINE / libmopacc.so)
      mopacc_set_params / mopacc_energy_gradient
        OpenMOPAC mopac_scf  model=4 AM1
```

| Variable | Role |
| --- | --- |
| `MOPACC_LIBRARY` | path to `libmopacc.so` |
| `RGPOT_MOPACC_ENGINE` | same |

ABI units: Hartree, Hartree/Bohr. Frontend: eV, eV/Å.

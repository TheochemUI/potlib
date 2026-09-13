# MOPACPot — consumer of the split mopacc engine

rgpot dlopens [`libmopacc.so`](https://github.com/OmniPotentRPC/mopacc).
This directory is the frontend only. OpenMOPAC lives in mopacc.

Not the eOn AMS MOPAC engine. Not an Expr term. Params are packed
`MopacCParams`, not Cap'n Proto.

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

# UmaPot: UMA / OMol AOTInductor frontend

`UmaPot` loads a compiled AOTInductor package (`.pt2`) that
`scripts/export_uma_aoti.py` wrote from a UMA checkpoint.

vesin builds the neighbor list. The graph returns energy and forces.
Charge and spin are per-call tensors. The compiled graph does not
call fairchem at evaluate time.

## Package

One `.pt2` per composition. The sidecar next to it records cutoff,
max neighbors, task, charge, spin, `z_set`, and label.

`scripts/export_baker_uma_aoti.py` walks Baker endpoints and
deduplicates by `(z_set, charge, spin)`.

| File | Role |
| --- | --- |
| `model.pt2` | AOTInductor package |
| `model.pt2.json` | sidecar: cutoff, neighbors, task, `z_set` |

`UmaConfig.cutoff` / `max_neighbors` are defaults. The sidecar wins
when it is present.

## potserv

```
Uma:<model.pt2>
Uma:<model.pt2>:<task>
```

Task default is `omol`. Device default is `cpu`.

## Build

Needs torch and vesin (`-Dwith_uma=true`, pixi env that has both).
`libuma_engine.so` is the dlopen plugin for eonclient: the host
never links torch. Config is a Cap'n Proto `UmaParams` message.

Molecular graphs use a large constant box so the neighbor list
shape is stable. Do not treat that box as a periodic crystal.

Elja / some HPC loaders need the AOTI execstack rewrite in
`aoti_execstack.hpp` (`docs/newsfragments/+uma-elja-execstack.fixed.md`).

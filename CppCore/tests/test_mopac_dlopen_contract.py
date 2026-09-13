#!/usr/bin/env python3
"""rgpot dlopens the split mopacc engine. No in-tree OpenMOPAC embed."""

from __future__ import annotations

import sys
from pathlib import Path


def require(condition: bool, message: str) -> None:
    if not condition:
        raise AssertionError(message)


def main() -> int:
    root = Path(sys.argv[1]) if len(sys.argv) > 1 else Path.cwd()
    mopac_dir = root / "CppCore" / "rgpot" / "MOPACPot"
    meson = (mopac_dir / "meson.build").read_text(encoding="utf-8")
    frontend = (mopac_dir / "MOPACPot.cc").read_text(encoding="utf-8")

    for token in ("shared_library(", "with_mopac", "libmopac.so", "mopac_scf"):
        require(
            token not in meson,
            f"meson.build must not embed OpenMOPAC ({token})",
        )
    require("dlopen" in frontend or "DynLib" in frontend, "frontend must dlopen")
    require("mopacpot_dep = declare_dependency(" in meson, "missing mopacpot_dep")
    print("ok: mopacc is a split engine")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

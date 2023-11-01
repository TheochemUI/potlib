# Source files
src_files = [
]

# Implemented potentials
subdir('src/LennardJones') # 'lennard_jones'
subdir('src/CuH2') # 'cuh2'

potentials = [
  lennard_jones,
  cuh2,
]

_linkto += potentials

# Create library
potlib = library('pot',
                 src_files,
                 dependencies: _deps,
                 cpp_args: _args,
                 link_with: _linkto,
                 install: true)

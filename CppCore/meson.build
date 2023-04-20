# Source files
src_files = [
  'src/base_types.cc',
  'src/helpers.cc',
  'src/Potential.cc',
]

# Implemented potentials
subdir('src/LennardJones') # 'lennard_jones'
subdir('src/CuH2') # 'cuh2'

potentials = [
  lennard_jones,
  cuh2,
]

_linkto += potentials

# Create static library
potlib = library('pot',
                 src_files,
                 dependencies: _deps,
                 cpp_args: _args,
                 link_with: _linkto,
                 install: true)

# Source files
src_files = [
  'src/base_types.cc',
  'src/helpers.cc',
  'src/Potential.cc',
]

# Implemented potentials
subdir('src/LennardJones') # 'lennard_jones'

potentials = [
  lennard_jones
]

_linkto += potentials

# Create static library
potlib = library('pot',
                 src_files,
                 dependencies: _deps,
                 cpp_args: _args,
                 link_with: _linkto,
                 install: true)

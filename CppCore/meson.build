# Source files
src_files = [
  'src/base_types.cc',
  'src/helpers.cc',
  'src/Potential.cc',
  'src/LennardJones/LJPot.cc',
]

# Create static library
potlib = library('pot',
                 src_files,
                 dependencies: _deps,
                 cpp_args: _args,
                 install: true)

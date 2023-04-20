project('pot', 'cpp',
  version : '0.1',
  default_options : ['warning_level=2', 'cpp_std=c++17'])
# IMPORTANT!! warning_level=3 passes -fimplicit-none
# Many of the older Fortran codes need implicit typing

host_system = host_machine.system()

# Add C++ compiler options
cpp_args = ['-Wall', '-Wextra', '-Wpedantic']
_args = []
_deps = []

# Add conditionals
if host_system == 'darwin'
  _args += ['-DOSX=TRUE']
  add_global_arguments(['-faligned-allocation'], language: 'cpp')
endif

# Languages
add_languages('c', required: true)
cc = meson.get_compiler('c')
cppc = meson.get_compiler('cpp')

# Dependencies
eigen_dep = dependency('Eigen3', method : 'cmake', modules : ['Eigen3::Eigen'], required : true)
fmt_dep = dependency('fmt', method : 'cmake',  modules : ['fmt::fmt'],  required : true)
spdlog_dep = dependency('spdlog', required : true)
_deps += [ spdlog_dep, fmt_dep, eigen_dep ]

# Testing only
gtest_dep = dependency('gtest', main : true, required : true)
gmock_dep = dependency('gmock', required : false)

# --------------------- Library

subdir('CppCore') # defines potlib

# ------------------------ Examples

if get_option('with_examples')
example_array = [#
  ['CallLJPot', 'ljpot_call', 'calling_ljpot.cc', ''],
             ]
# Not really a test but the best way to make tiny executables
foreach example : example_array
  test(example.get(0),
       executable(example.get(1),
          sources : ['CppCore/examples/'+example.get(2)],
          dependencies : _deps,
          link_with: [potlib],
          cpp_args : _args
                 ),
        workdir : meson.source_root() + example.get(3)
      )
endforeach
endif

project('pot', 'cpp',
  version : '0.1',
  default_options : ['warning_level=2', 'cpp_std=c++17'])
# IMPORTANT!! warning_level=3 passes -fimplicit-none
# Many of the older Fortran codes need implicit typing

host_system = host_machine.system()

# Add C++ compiler options
cpp_args = ['-Wall', '-Wextra', '-Wpedantic']
_args = [cpp_args] # Extra arguments
_deps = [] # Dependencies
_linkto = [] # All the sub-libraries (potentials)

# Add conditionals
if host_system == 'darwin'
  _args += ['-DOSX=TRUE']
  cpp_args += ['-faligned-allocation']
endif

# Languages
add_languages('c', required: true)
add_languages('fortran', required: true)
cc = meson.get_compiler('c')
cppc = meson.get_compiler('cpp')

# Dependencies
# libm for Unix systems
m_dep = cppc.find_library('m', required: false)
_deps += m_dep
# For clang
_deps += [declare_dependency(link_args: '-lstdc++')]
# All installed with meson wrap install <blah> originally
eigen_dep = dependency('eigen', version: '3.4.0')
if not eigen_dep.found()
  eigen_dep = dependency('eigen', version: '3.4.0',
                         subproject: subproject('eigen'),
                         required: true)
endif
_deps += eigen_dep

if not get_option('pure_lib')
  _args += ['-DNOT_PURE_LIB=TRUE']
  subproject('fmt')
  fmt_dep = dependency('fmt', required: true)
  _deps += fmt_dep
endif

# --------------------- Library

subdir('CppCore') # defines potlib
_linkto += potlib

# ------------------------ Examples

if get_option('with_examples')
example_array = [#
  ['CallLJPot', 'ljpot_call', 'calling_ljpot.cc', ''],
  ['CallCuH2Pot', 'cuh2_call', 'calling_cuh2.cc', ''],
             ]
# Not really a test but the best way to make tiny programs
foreach example : example_array
  test(example.get(0),
       executable(example.get(1),
          sources : ['CppCore/examples/'+example.get(2)],
          dependencies : _deps,
          link_with: _linkto,
          cpp_args : _args
                 ),
        workdir : meson.source_root() + example.get(3)
      )
endforeach
endif

# ------------------------ Tests

if get_option('with_tests')
  subproject('gtest')
  gtest_dep = dependency('gtest', main : true, required : true)
  gmock_dep = dependency('gmock', required : false)
  _args += ['-DPOTTEST']
  _deps += [ gtest_dep, gmock_dep ]
test_array = [#
  ['CuH2', 'cuh2_run', 'CuH2PotTest.cc', ''],
             ]
foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
          sources : ['CppCore/gtests/'+test.get(2)],
          dependencies : _deps,
          link_with : _linkto,
          cpp_args : _args
                 ),
        workdir : meson.source_root() + test.get(3)
      )
endforeach
endif

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
                 dependencies: _deps,
                 cpp_args: _args,
                 link_with: _linkto,
                 install: true)

# ------------------------ Examples

if get_option('with_examples')
fmt_dep = dependency('fmt', required: true)
_deps += fmt_dep
example_array = [#
  ['CallLJPot', 'ljpot_call', 'calling_ljpot.cc', ''],
  ['CallCuH2Pot', 'cuh2_call', 'calling_cuh2.cc', ''],
             ]
# Not really a test but the best way to make tiny programs
foreach example : example_array
  test(example.get(0),
       executable(example.get(1),
          sources : ['examples/'+example.get(2)],
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
  test_deps = _deps
  test_deps += dependency(
    'Catch2',
    method: 'cmake',
    modules: ['Catch2::Catch2WithMain'],
  )
  test_args = _args
  test_args += ['-DPOTTEST']
  test_array = [#
    ['CuH2', 'cuh2_run', 'CuH2PotTest.cc', ''],
  ]
  foreach test : test_array
    test(test.get(0),
         executable(test.get(1),
                    sources : ['gtests/'+test.get(2)],
                    dependencies : test_deps,
                    include_directories: _incdirs,
                    cpp_args: test_args,
                    link_with: _linkto,
                   ),
         workdir : meson.source_root() + test.get(3)
        )
  endforeach
endif

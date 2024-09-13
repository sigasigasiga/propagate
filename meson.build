project('siga-propagate', 'cpp', default_options : [ 'cpp_std=c++23' ])

siga_propagate_dep = declare_dependency(
  include_directories: include_directories('include')
)

meson.override_dependency('siga-propagate', siga_propagate_dep)

if get_option('tests').enabled()
  test(
    'deducer',
    executable(
      'deducer',
      'test/deducer.cpp',
      dependencies: [siga_propagate_dep]
    )
  )

  test(
    'optional',
    executable(
      'optional',
      'test/optional.cpp',
      dependencies: [siga_propagate_dep]
    )
  )
endif

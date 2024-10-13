project('siga-propagate', 'cpp', default_options : [ 'cpp_std=c++23' ])

siga_propagate_dep = declare_dependency(
  include_directories: include_directories('include')
)

meson.override_dependency('siga-propagate', siga_propagate_dep)

if get_option('tests').enabled()
  test(
    'test_ubiq',
    executable(
      'test_ubiq',
      'test/ubiq.cpp',
      dependencies: [siga_propagate_dep]
    )
  )

  test(
    'test_optional',
    executable(
      'test_optional',
      'test/optional.cpp',
      dependencies: [siga_propagate_dep]
    )
  )

  test(
    'test_macro',
    executable(
      'test_macro',
      'test/macro.cpp',
      dependencies: [siga_propagate_dep]
    )
  )
endif

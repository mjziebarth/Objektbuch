project('objektbuch', 'cpp', default_options : ['cpp_std=c++20'])

include = include_directories('include')

objektbuch = declare_dependency(
    include_directories: include
)

#
# Test:
#
test_compile = executable(
    'test_compile',
    'testing/test_compile.cpp',
    dependencies : objektbuch
)
test(
    'Run compiled test...',
    test_compile,
    args : []
)
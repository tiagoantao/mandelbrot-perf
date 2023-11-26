project('mandelbrot-perf', 'c', 'cuda',
  version : '0.1',
  default_options : ['warning_level=2'])

cuda_compiler = meson.get_compiler('cuda')
cuda = import('unstable-cuda')
nvcc_flags = cuda.nvcc_arch_flags(cuda_compiler, 'Common')

glib_dep = dependency('glib-2.0', version : '>= 2.40', required : true)

ymir = subproject('ymir', required : true)
ymir_dep = ymir.get_variable('ymir_dep')

inc_dirs = include_directories('include')

basic_exe = executable('mandelbrot_basic', 'basic/mandelbrot_basic.c', 'shared.c',
  include_directories : inc_dirs,
  c_args: ['-Wpedantic'],
  dependencies : [glib_dep, ymir_dep])

cuda_exe = executable('mandelbrot_cuda', 'cuda/mandelbrot_cuda.cu', 'shared.c',
  cuda_args: nvcc_flags,
  include_directories : inc_dirs,
  dependencies : [glib_dep, ymir_dep])

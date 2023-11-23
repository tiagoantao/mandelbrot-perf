project('mandelbrot-per-basic', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

glib_dep = dependency('glib-2.0', version : '>= 2.40', required : true)
#png_dep = dependency('libpng', required : true)

ymir = subproject('ymir', required : true)
ymir_dep = ymir.get_variable('ymir_dep')

exe = executable('mandelbrot_basic', 'basic/mandelbrot_basic.c',
  install : true,
  dependencies : [glib_dep, ymir_dep])

test('basic', exe)

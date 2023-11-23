project('mandelbrot-per-basic', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

glib_dep = dependency('glib-2.0', version : '>= 2.40', required : true)
#png_dep = dependency('libpng', required : true)

ymir = subproject('ymir', required : true)

exe = executable('mandelbrot_basic', 'basic/mandelbrot_basic.c',
  install : true,
  dependencies : [glib_dep])

test('basic', exe)

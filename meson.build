project('dioimperatoresalvini', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20', 'optimization=3'])
 
executable('dioimperatoresalvini',
           [
             'src/main.cc',
             'src/particle.cc',
             'src/universe.cc',
             'src/matter.cc',
             'src/element.cc',
           ],
           install : true,
           dependencies: dependency('raylib'),
           include_directories: include_directories('include'))


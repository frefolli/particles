@all: ./build/dioimperatoresalvini.exe

./build/dioimperatoresalvini.exe: include/rf/*.hh src/*.cc
	meson build
	meson compile -C build

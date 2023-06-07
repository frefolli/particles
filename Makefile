@all: ./build/dioimperatoresalvini

./build/dioimperatoresalvini: include/rf/*.hh src/*.cc
	meson build
	meson compile -C build

run: ./build/dioimperatoresalvini
	./build/dioimperatoresalvini

clean:
	rm -rf build

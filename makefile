all:
	mkdir -p build
	cd build && cmake .. && make -j2 -s && picotool load unicorn-gol.uf2 -f

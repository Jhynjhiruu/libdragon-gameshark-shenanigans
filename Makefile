TARGET := fw.bin

default: $(TARGET)

fw.bin: test.tmp
	dd if=$< of=$@ bs=262144 conv=sync

test.tmp: ipl3_prod.z64 build/bootstrap/test.elf build/prog/prog.elf
	dd if=ipl3_prod.z64 bs=256 conv=sync of=$@
	dd if=build/bootstrap/test.elf bs=256 conv=sync >> $@
	dd if=build/prog/prog.elf.stripped >> $@

build/bootstrap/test.elf: src/bootstrap/loader.c src/bootstrap/bootstrap.ld src/bootstrap/Makefile
	make -C src/bootstrap

build/prog/prog.elf: src/prog/main.c src/prog/Makefile
	make -C src/prog

clean:
	rm fw.bin
	rm test.tmp
	make -C src/bootstrap clean
	make -C src/prog clean

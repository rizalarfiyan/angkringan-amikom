.PHONY: build run watch dev dir cmake clean
make:
	$(MAKE) build

build:
	@echo "Build app"
	$(MAKE) dir
	$(MAKE) cmake
	cd ./build && make

run:
	@echo "Running app"
	./build/angkringan_amikom

watch:
	watchexec --restart -w src '$(MAKE) build && $(MAKE) run'

dev:
	@echo "\nRunning app with development\n"
	$(MAKE) dir
	$(MAKE) cmake
	$(MAKE) watch

dir:
	mkdir -p ./build
	cd ./build

cmake:
	cd ./build && cmake ..

clean:
	rm -rf ./build

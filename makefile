build:
	@echo "Build app"

run:
	@echo "Running app"

run_dev:
	g++ -lpthread ./src/main.cpp -o ./temp/run && chmod +x ./temp/run && ./temp/run

watch:
	watchexec --restart -w src '$(MAKE) dir && $(MAKE) clean && $(MAKE) run_dev'

dev:
	@echo "\nRunning app with development\n"
	$(MAKE) watch

fresh:
	$(MAKE) clean
	$(MAKE) dir

dir:
	mkdir -p ./temp

clean:
	rm -rf ./temp/*

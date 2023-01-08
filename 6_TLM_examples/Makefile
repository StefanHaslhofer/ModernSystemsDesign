all:
	@mkdir -p build
	cd build && cmake ..
	+cd build && $(MAKE)
	@echo
	@echo "--------------------------------------------------------"
	@echo "Done. The examples are compiled in the 'build' directory"
	@echo "--------------------------------------------------------"

clean:
	rm -rf build

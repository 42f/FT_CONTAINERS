
all:
	@git submodule update --init --recursive
	@ln -s project_headers/* tester/includes/your_headers_files
	@cp project_headers/your_headers.hpp tester/includes/
	$(MAKE) f -C $(LIBDIR)

.PHONY: all
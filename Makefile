
all:
	@git submodule update --init --recursive
	@$(RM) -rf tester/includes/your_headers_files/*
	@cp -rf ./project_headers/* ./tester/includes/your_headers_files/
	@cp ./project_headers/your_headers.hpp ./tester/includes/
	$(MAKE) -C ./tester f

fclean:
	@$(RM) -rf ./tester/includes/your_headers_files/*
	@true > tester/includes/your_headers.hpp  
	$(MAKE) -C ./tester fclean

.PHONY: all
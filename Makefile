# C project: Bachelor Thesis
BUILD_DIR=./build_rd
CMAKE_MACROS=-DCMAKE_BUILD_TYPE=Release -DPICO_SDK_PATH=pico-sdk/
#CMAKE_MACROS+=-DCMAKE_EXPORT_COMPILE_COMMANDS=YES

##############################################

.PHONY: build rubber_ducky doc pack clean

all: build

build: $(BUILD_DIR)/Makefile
	make -C$(BUILD_DIR) -j8

rubber_ducky: $(BUILD_DIR)/Makefile
	make -C$(BUILD_DIR) -j8 rubber_ducky

clean:
	rm -rf $(BUILD_DIR) .coverage tests/reports/ compile_commands.json

####### RD Client python commands ############

.PHONY: test test_show_coverage

run_cli:
	@poetry run app -v

run_client:
	@poetry run app -vn -p 5000 -H 192.168.4.1

test:
	poetry run coverage run -m pytest -vv && poetry run coverage report -m

test_show_coverage: test
	poetry run coverage html && firefox tests/reports/htmlcov/index.html

##############################################

$(BUILD_DIR)/Makefile: CMakeLists.txt ./rubber_ducky/*
	cmake -H. -B$(BUILD_DIR) $(CMAKE_MACROS)
	if [ -f "$(BUILD_DIR)/compile_commands.json" ]; then cp $(BUILD_DIR)/compile_commands.json .; fi


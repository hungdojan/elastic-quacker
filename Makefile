# C project: Bachelor Thesis
BUILD_DIR=./pico_build

##############################################

.PHONY: build rubber_ducky doc pack clean

all: build

build: $(BUILD_DIR)/Makefile
	make -C$(BUILD_DIR) -j8

rubber_ducky: $(BUILD_DIR)/Makefile
	make -C$(BUILD_DIR) -j8 rubber_ducky

doc: Doxygen
	doxygen

clean:
	rm -rf doc *.zip $(BUILD_DIR) .coverage tests/reports/

####### RD Client python commands ############

.PHONY: export_req test test_show_coverage

export_req:
	poetry export --without-hashes --format=requirements.txt > requirements.txt

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
	cmake -H. -B$(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=YES -DPICO_SDK_PATH=pico-sdk/
	cp $(BUILD_DIR)/compile_commands.json .


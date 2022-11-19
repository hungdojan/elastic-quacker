# C project: Bachelor Thesis
BUILD_DIR=./build

##############################################

.PHONY: build build_release run run_release doc pack clean

all: build

doc: Doxygen
	doxygen

pack: src/* README.md Makefile CMakeLists.txt Doxygen
	rm -f *.zip
	zip -r $(TARGET_NAME) $^

clean:
	rm -rf doc *.zip $(BUILD_DIR)

##############################################

build: $(BUILD_DIR)/Makefile
	make -C$(BUILD_DIR) -j8

$(BUILD_DIR)/Makefile: CMakeLists.txt ./rubber_ducky/* ./mass_storage/*
	if [[ ! -f ./pico_sdk_import.cmake ]]; then cp ./pico-sdk/external/pico_sdk_import.cmake .; fi
	export PICO_SDK_PATH=../pico-sdk/ && cmake -H. -B$(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=YES
	cp $(BUILD_DIR)/compile_commands.json .


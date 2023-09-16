.PHONY: install clean

VERSION := 0.1
CMAKE := cmake

build: CMakeLists.txt
	rm -rf build && mkdir build
	cd build && $(CMAKE) .. && $(MAKE)

install: build
	cd build && $(MAKE) install

clean:
	rm -rf build test docs CMakeLists.txt

CMakeLists.txt:
	echo "cmake_minimum_required(VERSION 3.26.4)" > CMakeLists.txt
	echo "project(winyl VERSION ${VERSION} DESCRIPTION \"Wii network library\")" >> CMakeLists.txt
	
	echo "set(CMAKE_SYSTEM_NAME NintendoWii)" >> CMakeLists.txt
	echo "set(CMAKE_BUILD_TYPE Release)" >> CMakeLists.txt

	sh -c "echo \"add_library(winyl STATIC$$(find src/ -type f -name \*.c -printf " %p"))\" >> CMakeLists.txt"
	
	echo "set_target_properties(winyl PROPERTIES VERSION \$${PROJECT_VERSION})" >> CMakeLists.txt
	#echo "set_target_properties(winyl PROPERTIES PUBLIC_HEADER include/version.h DESTINATION winyl)" >> CMakeLists.txt
	sh -c "echo \"install(FILES$$(find include/ -type f -name \*.h -printf " %p") DESTINATION include/winyl)\" >> CMakeLists.txt"

	echo "string(LENGTH \"${VERSION}\" VERSION_LEN)" >> CMakeLists.txt
	echo "add_compile_definitions(_WINYL_VERSION=\"${VERSION}\")" >> CMakeLists.txt
	echo "add_compile_definitions(_WINYL_VERSION_LEN=\$${VERSION_LEN})" >> CMakeLists.txt

	echo "install(TARGETS winyl)" >> CMakeLists.txt

build/inc:
	mkdir -p build/inc
	cp -r include build/inc
	cd build/inc && mv include winyl

test: build build/inc
	gcc -g -Ibuild/inc test.c -Lbuild -lwinyl -lyuarel -otest

getversion:
	@echo "${VERSION}"

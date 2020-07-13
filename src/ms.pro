############################################################
# Project file
# Makefile will include this project file
############################################################

# Specify C++14
CXXFLAGS += -std=c++14

# Specify target name
TARGET = sweepy 

# Specify the #include directories which should be searched when compiling the project.
INCLUDEPATH = .

# Specify the source directories which should be searched when compiling the project.
DEPENDPATH = .

# Defines the header files for the project.
HEADERS = $(wildcard *.h)

# Defines the source files for the project.
SOURCES = $(wildcard *.cpp)
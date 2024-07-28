# Intro to the Yui Programming Language

## How to Compile the Language

* make sure to be in parent `yui` directory
* make file using `cmake -S . -B build/`
* then run `cmake --build build/`
* then `./build/yui`

## How to Compile Programs

* run `./build/yui <file_name.yui>` to compile the program
* the compiled version of the `.yui` file will be outputed as a `.o` 
* this can then be run through `./out`
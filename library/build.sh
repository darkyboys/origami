mkdir 2>/dev/null objects
echo "Building objects/lexer.o [1/2]"
g++ library/lexer.cc -o objects/lexer.o -c
echo "Building objects/runtime.o [1/2]"
g++ library/runtime.cc -o objects/runtime.o -c
echo "Building is done. Please include the library/origami.hh file in your project and compile it with objects/lexer.o and objects/runtime.o"
echo "[Finished]"
mkdir 2>/dev/null objects
echo "Building objects/lexer.o [1/3]"
g++ library/lexer.cc -o objects/lexer.o -c
echo "Building objects/runtime.o [2/3]"
g++ library/runtime.cc -o objects/runtime.o -c
echo "Building objects/subfunction.o [3/3]"
g++ library/subfunction.cc -o objects/subfunction.o -c
echo "Building is done. Please include the library/origami.hh file in your project and compile it with objects/lexer.o, objects/subfunction.o and objects/runtime.o"
echo "[Finished]"
#include "../library/origami.hh"
#include <iostream>

origami::function print(origami::function args){
    for (std::string s : args){
        std::cout << s << "\n";
    }
    return {};
}

origami::function dir(origami::function args){
    origami::function rval = origami::oint::Lexer(R"(
compiler = "g++"
src = "src"

i = 0
while !i = 1000{
    if i = 101 {
        print (compiler, src, 100, i)
        compiler = "gcc"
        src = "dir"
    }
    i = i + 1
}
)");
    return rval;
}

int main(){
    origami::ProgramFile file("File.origami");
    file.runtime.make_function("print", print);
    file.runtime.make_function("dir", dir);
    file.run();
}
#include "../library/origami.hh"
#include <iostream>

origami::function print(origami::function args, origami::oint::Runtime* rnt){
    for (std::string s: args){
        std::cout << s << '\n';
    }
    return {};
}

int main(){
    origami::ProgramFile file("examples/subfunc-example.origami");
    file.runtime.make_function("print", print);
    file.runtime.make_function(file.runtime.sub_function("print", "print"), print);
    file.run();

//     std::cout << file.code<<"\n";

//     std::string program = origami::oint::subfunction(origami::oint::Lexer(R"(

// i = 1
// while !i = 100{
//     x = i % 2
//     if i%2 = 0{
//          print ("i is av even number: ", i)
//     }
//     i = i + 1
// }
    
// )", 0, 1));

//     // std::cout << program<<"\n";
//     // std::string program = origami::oint::subfunction(origami::oint::Lexer(file.code, 0, 1));

//     std::cout << program<<"\n";

//     origami::Program p(program);
//     p.runtime.make_function("print", print);
//     p.runtime.make_function(p.runtime.sub_function("print", "print"), print);
//     p.run();
}
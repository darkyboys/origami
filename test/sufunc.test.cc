#include "../library/lexer.hh"
#include "../library/subfunction.hh"
#include <iostream>


int main(){
    std::string code = R"(
a = 2
v = 32
if !a = 23{
    print(a)
    a(b(), c(d().b(d().e())), b().e(e().b().b().c()))
}

a().b().c()
a(b(b()))
a(b(), c())
a(b(), c())
    .d()
    .e()

a(b(), c())
    .d(a())
    .e(a().b())
    )";

    // std::cout << origami::oint::subfunction(code);
    // for (std::string s: origami::oint::Lexer(code)){
    //     if (s == "\n") std::cout << "\\n"<<'\n';
    //     else std::cout << s <<"\n";
    // }

    
    std::cout << origami::oint::subfunction(origami::oint::Lexer(code, 0));
}
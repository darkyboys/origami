#include "../library/lexer.hh"
#include "../library/origami.hh"
// #include "subfunction.hh"

std::vector <std::string> add (std::vector <std::string> args, origami::oint::Runtime* rnt){
    std::vector <std::string> rval;
    std::string str;
    for (std::string s : args){
        // std::cout << "Adding: "<<s<<" to args.\n";
        str += s;
    }
    
    rval.push_back(str);
    return rval;
}



origami::function list_return(origami::function args, origami::oint::Runtime* rnt){
    return origami::function{"Hello", "World", "2025"};
}

origami::function print (origami::function args, origami::oint::Runtime* rnt){
    for (std::string s : args){
        std::cout << s << "\n";
    }

    origami::oint::Type* var = rnt->variable("A");
    if (var == nullptr){
        std::cout << "A does not exist!";
        rnt->execute(origami::oint::Lexer("A = 12"));
        var = rnt->variable("A");
        std::cout << "A was created with value: "<<var->value[0]<<"\n";
    }
    else {

    }
    return {};
}

int main(){
//     std::string code = R"(
// A = 23
// b = 22
// c = a + b + "Hello world\"\"\"" + "Hs"

// a s f

// # Variables
// s
// s
// s

// a, b, c, s = "d" + 23 + "asd" # - 2


// if (1 == 3){
//     print ("Hello world 2024")print ("Rocm is insane")
// }

// insane_function (
//     "string",
//     2,
//     "arr",
//     "arr2"
// ).add(1, 2)
//     .subtract (1,2)
//     .mul(1,2)


// #include <iostream>
//     )";


//     std::string code2 = R"(
// a = insane_function(
//     crazy_call(
//         "level 1" + nested_call("level 2", inner_call("level 3")) 
//     ).add(1,2,3)
//      .subtract(4, 5)
// ).mul(
//     complex_op(123, "string with \"quotes\"", arr[5])
// ).div(
//     another_call(
//         "deep",
//         insane_function("even deeper")
//     )
// )

// # totally unrelated comment

// weird_var, another_var = "mixed" + 42 - crazy_call("oops") # comment at the end

// final_result = insane_function(
//     insane_function(
//         insane_function("whoa")
//     ).add("chained").subtract("still chained")
// ).mul("final")
// )";


// std::string code3 = R"(
// int main(int argc, char* argv[]){
//     char msg[] = "Hello world";
//     printf("%s, msg);
//     return 0;
// }
// )";

    // for (std::string token : origami::oint::Lexer(code2)){
    //     std::cout << "token: "<<token<<"\n";
    // }

    // std::cout << origami::oint::evaluate(origami::oint::Lexer("!1+!0*!0+!0"))<<"\n\n";

//     origami::oint::Runtime rnt;
//     rnt.execute(
//         origami::oint::Lexer(R"(
// a = 1
// b = 0
// c = 1
// d = 0
// e = a & b
// f = a & c
// g = 0 & a
// h = !a & 0 | !1
// )")
//     );

//     rnt.execute(origami::oint::Lexer("h = g+12"));

    // origami::oint::Type *var = rnt.variable("d");
    // if (var == nullptr){
    //     std::cout << "Does not exist\n";
    // }
    // else {
    //     std::cout << var->value[0]<<"\n";
    // }


    // std::cout << rnt.variable("e")->value[0]<<"\n";
    // std::cout << rnt.variable("f")->value[0]<<"\n";
    // std::cout << rnt.variable("g")->value[0]<<"\n";
    // std::cout << rnt.variable("h")->value[0]<<"\n";


    // for (std::string exp : rnt.normalize_expression(
    //     origami::oint::Lexer(R"(!a & 0 | !1 b h)")
    // )){
    //     std::cout << exp << "\n";
    // }

//     origami::oint::Runtime rnt;
//     rnt.make_function("add", add);

//         rnt.execute(
//         origami::oint::Lexer(R"(
// a = 1
// b = 0
// c = 1
// d = 0
// e = a & b
// f = a & c
// g = 0 & a
// h = !a & 0 | !1
// y = add (a+b)
// x = "Hello"

// if a = b & a = c{
//     y = 1
//     if 1{
//         y = 0
//         if y | a{
//             y = 1
//         }
//     }
// }{
//     if y = "1+1"{
//         y = 23
//     }
//     {
//         y = 26
//     }
// }
// )")
//     );
    
//     std::cout << rnt.variable("e")->value[0]<<"\n";
//     std::cout << rnt.variable("f")->value[0]<<"\n";
//     std::cout << rnt.variable("g")->value[0]<<"\n";
//     std::cout << rnt.variable("h")->value[0]<<"\n";
//     std::cout << rnt.variable("y")->value[0]<<"\n";
//     std::cout << rnt.make_normal(rnt.variable("x")->value[0])<<"\n";


    // for (std::string exp : rnt.normalize_expression(
    //     origami::oint::Lexer(R"(1+1+2+ -23 + f - d)")
    // )){
    //     std::cout << exp << "\n";
    // }




    // Subfunction test

//     std::string code = R"(
// myfunction()
// myfunction()
//     .global()
//     .pkg()
//     .another(args)

// myfunc2(myfunction().ae())
//     myfunc2()
//         .global(myfunc().nite())
//     )";

    // std::string file = origami::oint::flattenCode(
    //     origami::oint::Lexer(code)
    // );


    // std::cout << file;

        
    // for (std::string tk : origami::oint::Lexer(code)){
    //     std::cout << "Token: "<<tk<<"\n";
    // }


    // WHile loop test
    origami::oint::Runtime rnt;
    rnt.make_function("add", add);
    rnt.make_function("list", list_return);
    rnt.make_function("print", print);

        rnt.execute(
        origami::oint::Lexer(R"(
a = "Hello"
times x 1 + list() {
    print (x)
}
)")
    );
    
    // std::cout << rnt.variable("e")->value[0]<<"\n";
    // std::cout << rnt.variable("f")->value[0]<<"\n";
    // std::cout << rnt.variable("g")->value[0]<<"\n";
    // std::cout << rnt.variable("h")->value[0]<<"\n";
    // std::cout << rnt.variable("y")->value[0]<<"\n";
    // std::cout << rnt.make_normal(rnt.variable("x")->value[0])<<"\n";
    std::cout << rnt.variable("a")->value[0]<<"\n";

}

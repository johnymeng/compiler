/*---------------STANDARD LIBRARY---------------*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include <cstddef>

/*---------------HEADER FILES---------------*/
#include "tokenization.hpp"
#include "parser.hpp"
#include "generation.hpp"

// enum class TokenType
// {
//     exit,
//     int_lit,
//     semi
// };

// struct Token
// {
//     TokenType type;
//     std::optional<std::string> value {};
// };

// //turns file into tokens 
// std::vector<Token> tokenize(const std::string& str)
// {
    
// }

// std::string tokens_to_asm(const std::vector<Token> &tokens)
// {
//     std::stringstream output;
//     output << "global _start\n _start:\n";
//     for(int i = 0; i < tokens.size(); i++)
//     {
//         const Token& token = tokens[i];

//         if(token.type == TokenType::exit)
//         {
//             if(i + 1 < tokens.size() && tokens[i+1].type == TokenType::int_lit)
//             {
//                 if(i + 2 < tokens.size() && tokens[i+2].type == TokenType::semi)
//                 {
//                     output << "    mov rax, 60\n";
//                     output << "    mov rdi, " << tokens[i+1].value.value() << "\n";
//                     output << "    syscall";
//                 }
//             }
//         }
//     }
//     return output.str();
// }

//count of arguments, string of arguments
int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cerr<<R"(                                                                               
                           ,,                                                   
                ,,,.,,,,.,   .,,,,,,***/,,****.                                 
             .**/,,,,,,*,**,,,,,,,,****,******/**,.                             
           .***/,,,,,,,/****,,,,******************,.,*                          
            ,*,/,*..,,,/*#,*,,,,,*/,***********,,,*,,,**                        
          .,,,*,*,*,,**//**,,,,..,,,*,,,*,,/,*,,,*,,,,,,,.                      
          .*,/*/**/**//**,/,,,.  ,,,*/,*/*,,,,,,,,* ,/,,,,.                     
              (*****/******/,,,,,********,***,****** .*,,,,                     
             *,,,*(,*(**,,,/*,********/*****,.****/*  .,*,,,                    
            ,.,,,*/**,****,*******/*****(*/*..******.. /****                    
            /,,/,,******(*****(***#**(*&&@&#,,/.,,..#./(**,,                    
             ,*/,*****/*(**(**(**//,(#..&%%( .      /,.**,.*                    
              .***/***(**,., .,****,.,*,..**..       ,.*/.                      
              /*((*/**/*** ,,, /,**,.,,,.... .         .*,                      
             .*/*/*//**/**(,,,.. *,**......            *,/                      
             ./**(***/*/**/*%%#//.,***   .       ..  .  **                      
            , *,,**,**/(****(*/(,,,. .,/. ...       .  /                        
            , /**,*,**((***/*/**/*,,,,,,..... .. . ,.                           
             /*****,**/#**,,****//*,,,,,,,,,,*((((.                             
              ***#*,,**##***(/**/(/,,,,,,,,,,((/(((                             
              *.**/****/#/***.*/#/**,,,,,,,,*/,  /*/..                          
             *, */* *****,* **//,.,,,,,**,,,,(/*,*                              
                  .*...*.  .//*@#*..,.,,,,, /,*.#**/((.                         
                          .,,...,*(*/......&/(.,.#* .#((,                       
                       /(#####%%(**,,,....(/.##(%#%%###(/(,                     
                     *#######%%%%%%#.,,,,*/&%%%%*%&*/%#/*,#.                    
                    .,.    . ./####((/  ...&%%#,.&#/.//%%%/   .                 
                   .,*,,      ,*.####(((..**,,,..&&(*...,%%#/    .              
                  .,*.,,    .,..,,*##(#(#..,....,/&&%     (&%,,  .,             
                 *...*.* . ....*..*,##(##%...... .*&%....,*(&%     .            
                  ,/.*.., .......*.,*####%%,,...  .&%.      ,/. .               
                   /....,..........,*,&%%%%#.,   . &    .,,,.,, .   .  .*,,     
                    ,...,,..,,,......,.%%%%(/   ..,,...,,.,.,..    ,.,....,.    
                    ,*..,,,..*,,......,,%%@*.. *..*,..,/,*,,...,,,....,..,,     
                  *(%%,.,,,...,,....  ..*&&..,..,,**..***,,,//*,,,,,,,,./.      
                .#(#%%/.,,,,....,,.... . #@**.**./*,..*,,,,,,,**..*, ..         
               /(((#%%%,,/,,......,.... ..@(.,*..**../,,,,,,,*.,.,.*            
              /(((#####*.**,....,,,.,.. ..*@*,,.**,.*,,,,,,,***.., .            
              /((((((##*,,*............. ,.#&.,.*,,*,,,,,,,,,**. .  .           
               *//(((((,,,*...........*/**(&#*.,*,**,,,,,,,*,,.,. . ,           )"<<std::endl;

        std::cerr<<"Oh no, there's an error! Yahasorry, that's the wrong usage! The correct usage is..."<<std::endl;
        std::cerr<<"Correct Usage: yui <yaha-input.yui>"<<std::endl;

        return EXIT_FAILURE;
    }

    std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input(argv[1], std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    std::cout<< contents <<std::endl;

    Tokenizer tokenizer(std::move(contents));
    std::vector<Token> tokens = tokenizer.tokenize();


    Parser parser(std::move(tokens));
    std::optional<NodeExit> tree = parser.parse();

    if(!tree.has_value())
    {
        std::cerr << "No Exit statement found" << std::endl;
        exit(EXIT_FAILURE);
    }

    Generator generator(tree.value());
    {
        std::fstream file("out.asm", std::ios::out);
        file << generator.generate();
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");
    
    return EXIT_SUCCESS;
}
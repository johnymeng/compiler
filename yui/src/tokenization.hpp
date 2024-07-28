#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include <string>
#include <cstddef>


enum class TokenType
{
    exit,
    int_lit,
    semi
};

struct Token
{
    TokenType type;
    std::optional<std::string> value {};
};

class Tokenizer
{
public:
    explicit Tokenizer(std::string src)
        : m_src(std::move(src))
    {

    }

    std::vector<Token> tokenize()
    {
        std::string buf;
        std::vector<Token> tokens;

        while(peek().has_value())
        {
            if(std::isalpha(peek().value()))
            {
                buf.push_back(consume());
                while(peek().has_value() && std::isalnum(peek().value()))
                {
                    buf.push_back(consume());
                }

                if(buf == "exit")
                {
                    tokens.push_back({.type = TokenType::exit});
                    buf.clear();
                    continue;
                }
                else
                {
                    std::cerr << "A Yahamistake was Made!" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if(std::isdigit(peek().value()))
            {
                buf.push_back(consume());
                while(peek().has_value() && std::isdigit(peek().value()))
                {
                    buf.push_back(consume());
                }
                tokens.push_back({.type = TokenType::int_lit, .value = buf});
                buf.clear();
                continue;
            }
            else if(peek().value() == ';')
            {
                consume();
                tokens.push_back({.type = TokenType::semi});
                continue;
            }
            else if(std::isspace(peek().value()))
            {
                consume();
                continue;
            }
            else
            {
                std::cerr << "A Yahamistake was Made!" << std::endl;
                exit(EXIT_FAILURE);
            }           
        }
        m_index = 0;
        return tokens;
    }

private:
    const std::string m_src;
    size_t m_index = 0; 

    [[nodiscard]] std::optional<char> peek(int ahead=1) const
    {
        if(m_index + ahead > m_src.length())
        {
            return{};
        }
        else
        {
            return m_src.at(m_index);
        }
    }

    char consume()
    {
        return m_src.at(m_index++);
    }

};
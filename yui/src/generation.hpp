#pragma once

#include "tokenization.hpp"
#include "parser.hpp"

class Generator
{
public:
    inline Generator(NodeExit root)
        : m_root(std::move(root))
    {

    }

    [[nodiscard]] std::string generate() const
    {
        std::stringstream output;
        output << "global _start\n _start:\n";
        output << "    mov rax, 60\n";
        output << "    mov rdi, " << m_root.expr.int_lit.value.value() << "\n";
        output << "    syscall";

        return output.str();
    }

private:
    const NodeExit m_root;
};
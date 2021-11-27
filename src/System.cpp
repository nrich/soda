#include "System.h"

std::string OpCodeAsString(OpCode opcode) {
    switch(opcode) {
        case OpCode::NOP: return "NOP";
        case OpCode::HALT: return "HALT";
        case OpCode::SETA: return "SETA";
        case OpCode::SETB: return "SETB";
        case OpCode::SETC: return "SETC";
        case OpCode::LOADA: return "LOADA";
        case OpCode::LOADB: return "LOADB";
        case OpCode::LOADC: return "LOADC";
        case OpCode::STOREA: return "STOREA";
        case OpCode::STOREB: return "STOREB";
        case OpCode::STOREC: return "STOREC";
        case OpCode::PUSHA: return "PUSHA";
        case OpCode::PUSHB: return "PUSHB";
        case OpCode::PUSHC: return "PUSHC";
        case OpCode::POPA: return "POPA";
        case OpCode::POPB: return "POPB";
        case OpCode::POPC: return "POPC";
        case OpCode::MOVCA: return "MOVCA";
        case OpCode::MOVCB: return "MOVCB";
        case OpCode::MOVCIDX: return "MOVCIDX";
        case OpCode::INCA: return "INCA";
        case OpCode::INCB: return "INCB";
        case OpCode::INCC: return "INCC";
        case OpCode::IDXA: return "IDXA";
        case OpCode::IDXB: return "IDXB";
        case OpCode::IDXC: return "IDXC";
        case OpCode::WRITEAX: return "WRITEAX";
        case OpCode::WRITEBX: return "WRITEBX";
        case OpCode::WRITECX: return "WRITECX";
        case OpCode::ADD: return "ADD";
        case OpCode::SUB: return "SUB";
        case OpCode::MUL: return "MUL";
        case OpCode::DIV: return "DIV";
        case OpCode::IDIV: return "IDIV";
        case OpCode::MOD: return "MOD";
        case OpCode::EXP: return "EXP";
        case OpCode::ATAN: return "ATAN";
        case OpCode::COS: return "COS";
        case OpCode::LOG: return "LOG";
        case OpCode::SIN: return "SIN";
        case OpCode::SQR: return "SQR";
        case OpCode::TAN: return "TAN";
        case OpCode::RND: return "RND";
        case OpCode::SEED: return "SEED";
        case OpCode::FLT: return "FLT";
        case OpCode::INT: return "INT";
        case OpCode::PTR: return "PTR";
        case OpCode::STR: return "STR";
        case OpCode::VSTR: return "VSTR";
        case OpCode::AND: return "AND";
        case OpCode::OR: return "OR";
        case OpCode::NOT: return "NOT";
        case OpCode::EQ: return "EQ";
        case OpCode::NE: return "NE";
        case OpCode::GT: return "GT";
        case OpCode::GE: return "GE";
        case OpCode::LT: return "LT";
        case OpCode::LE: return "LE";
        case OpCode::CMP: return "CMP";
        case OpCode::SETIDX: return "SETIDX";
        case OpCode::LOADIDX: return "LOADIDX";
        case OpCode::STOREIDX: return "STOREIDX";
        case OpCode::INCIDX: return "INCIDX";
        case OpCode::SAVEIDX: return "SAVEIDX";
        case OpCode::PUSHIDX: return "PUSHIDX";
        case OpCode::POPIDX: return "POPIDX";
        case OpCode::JMP: return "JMP";
        case OpCode::JMPEZ: return "JMPEZ";
        case OpCode::JMPNZ: return "JMPNZ";
        case OpCode::IDATA: return "IDATA";
        case OpCode::FDATA: return "FDATA";
        case OpCode::PDATA: return "PDATA";
        case OpCode::SDATA: return "SDATA";
        case OpCode::SYSCALL: return "SYSCALL";
        case OpCode::CALL: return "CALL";
        case OpCode::RETURN: return "RETURN";
        case OpCode::IRQ: return "IRQ";
        case OpCode::ALLOC: return "ALLOC";
        case OpCode::CALLOC: return "CALLOC";
        case OpCode::YIELD: return "YIELD";
        case OpCode::TRACE: return "TRACE";
        default: return "????";
    }
}


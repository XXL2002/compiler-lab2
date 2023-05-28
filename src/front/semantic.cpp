#include "front/semantic.h"

#include <cassert>

using ir::Function;
using ir::Instruction;
using ir::Operand;
using ir::Operator;

#define TODO assert(0 && "TODO");

#define GET_CHILD_PTR(node, type, index)                     \
    auto node = dynamic_cast<type *>(root->children[index]); \
    assert(node);
#define ANALYSIS(node, type, index)                          \
    auto node = dynamic_cast<type *>(root->children[index]); \
    assert(node);                                            \
    analysis##type(node, buffer);
#define COPY_EXP_NODE(from, to)              \
    to->is_computable = from->is_computable; \
    to->v = from->v;                         \
    to->t = from->t;

/*
    没有提供输入输出相关的 IR，可以通过调用库函数来与标准输入输出进行交互
*/
map<std::string, ir::Function *> *frontend::get_lib_funcs()
{
    static map<std::string, ir::Function *> lib_funcs = {
        {"getint", new Function("getint", Type::Int)},
        {"getch", new Function("getch", Type::Int)},
        {"getfloat", new Function("getfloat", Type::Float)},
        {"getarray", new Function("getarray", {Operand("arr", Type::IntPtr)}, Type::Int)},
        {"getfarray", new Function("getfarray", {Operand("arr", Type::FloatPtr)}, Type::Int)},
        {"putint", new Function("putint", {Operand("i", Type::Int)}, Type::null)},
        {"putch", new Function("putch", {Operand("i", Type::Int)}, Type::null)},
        {"putfloat", new Function("putfloat", {Operand("f", Type::Float)}, Type::null)},
        {"putarray", new Function("putarray", {Operand("n", Type::Int), Operand("arr", Type::IntPtr)}, Type::null)},
        {"putfarray", new Function("putfarray", {Operand("n", Type::Int), Operand("arr", Type::FloatPtr)}, Type::null)},
    };
    return &lib_funcs;
}

void frontend::SymbolTable::add_scope(Block *node)
{
    TODO;
}
void frontend::SymbolTable::exit_scope()
{
    TODO;
}

string frontend::SymbolTable::get_scoped_name(string id) const
{
    TODO;
}

Operand frontend::SymbolTable::get_operand(string id) const
{
    TODO;
}

frontend::STE frontend::SymbolTable::get_ste(string id) const
{
    TODO;
}

frontend::Analyzer::Analyzer() : tmp_cnt(0), symbol_table()
{
    TODO;
}

ir::Program frontend::Analyzer::get_ir_program(CompUnit *root)
{
    TODO;
}

// add
// analysis functions
// buffer应该为上一层的列表
void frontend::Analyzer::analysisCompUnit(CompUnit *root, ir::Program &program)
{
    for (int i = 0; i < root->children.size(); i++)
    {
        if (root->children[i]->type == NodeType::COMPUINT)
        {
            ir::Program &buffer = program; // 为program起别名buffer
            ANALYSIS(node, CompUnit, i);
        }
        else if (root->children[i]->type == NodeType::DECL)
        {
            // 为其创建globalFunc
            ir::Function globalFunc;
            vector<ir::Instruction *> buffer;
            ANALYSIS(node, Decl, i);
            for (int j = 0; j < buffer.size(); j++)
            {
                globalFunc.addInst(buffer[j]);
            }
            
            // 生成global return，并添加
            ir::Instruction *globalreturn = new ir::Instruction(ir::Operand(),
                                                                ir::Operand(),
                                                                ir::Operand(), ir::Operator::_return);
            globalFunc.addInst(globalreturn);
            
            // 设置globalValue
            TODO;
            // program.globalVal.emplace_back(ir::Operand());  // emplace_back() 和 push_back() 的区别，就在于底层实现的机制不同。push_back() 向容器尾部添加元素时，首先会创建这个元素，然后再将这个元素拷贝或者移动到容器中（如果是拷贝的话，事后会自行销毁先前创建的这个元素）；而 emplace_back() 在实现时，则是直接在容器尾部创建这个元素，省去了拷贝或移动元素的过程。

            program.addFunction(globalFunc);
        }
        else if (root->children[i]->type == NodeType::FUNCDEF)
        {
            // 创建Function buffer，解析完成后添加至program中
            ir::Function buffer;
            ANALYSIS(node, FuncDef, i);
            program.addFunction(buffer);
        }
    }
}
void frontend::Analyzer::analysisFuncDef(FuncDef *root, ir::Function &function)
{
    if (root->children.size()>5){
        // 有形参
        vector<ir::Operand> buffer;
        ANALYSIS(node, FuncFParams, 3);
    }
    
    
    // for (int i = 0; i < root->children.size();i++){
    //     if (root->children[i]->type==NodeType::FUNCTYPE){
    //         vector<ir::Instruction *> buffer;
    //         ANALYSIS(node, FuncType, i);
    //         for (int j = 0; j < buffer.size(); j++)
    //         {
    //             function.addInst(buffer[j]);
    //         }
    //     }
    // }
}
void frontend::Analyzer::analysisDecl(Decl *node, vector<ir::Instruction *> &buffer)
{
}
void frontend::Analyzer::analysisConstDecl(ConstDecl *node, vector<ir::Instruction *> &buffer)
{
}
void frontend::Analyzer::analysisBType(BType *node, vector<ir::Instruction *> &buffer)
{
}
void frontend::Analyzer::analysisConstDef(ConstDef *node, vector<ir::Instruction *> &buffer)
{
}
void frontend::Analyzer::analysisConstInitVal(ConstInitVal *node, vector<ir::Instruction *> &buffer)
{
}
void frontend::Analyzer::analysisFuncType(FuncType *node, vector<ir::Instruction *> &buffer)
{
}
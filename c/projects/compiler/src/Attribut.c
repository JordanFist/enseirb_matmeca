#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Attribut.h"
#include "Table_des_symboles.h"
#include "Table_des_chaines.h"
#include "stack.h"

extern FILE *test_c;
extern FILE *test_h;
extern FILE *main_test_c;

static Stack *label_list;

#define STRING_SIZE 128

void init_attribut()
{
    test_c = fopen("build/test.c", "w");
    test_h = fopen("build/test.h", "w");
    main_test_c = fopen("build/main_test.c", "w");
    fprintf(main_test_c, "#include \"test.h\"\n"
                         "#include <stdio.h>\n"
                         "int main()\n{\n"
                         "#include \"test.c\"\n"
                         "return 0;\n}");
    label_list = stackCreate();
}

reg new_reg(typeEnum type)
{
    static reg reg_int = 0;
    static reg reg_float = 0;
    static reg reg_bool = 0;
    static reg reg_string = 0;
    switch (type)
    {
    case Int:
        fprintf(test_h, "int ri%u;\n", reg_int);
        return reg_int++;
        break;
    case Float:
        fprintf(test_h, "float rf%u;\n", reg_float);
        return reg_float++;
        break;
    case Bool:
        fprintf(test_h, "int rb%u;\n", reg_bool);
        return reg_bool++;
        break;
    case String:
        // fprintf(test_h, "char rs%u[256];\n", reg_bool);
        return reg_string++;
        break;
    default:
        return EXIT_FAILURE;
    }
}

void new_var(const char *var_name, const symb_value_type *svt, unsigned int index)
{
    switch (svt->type)
    {
    case Int:
        fprintf(test_h, "int %s%u;\n", var_name, index);
        break;
    case Float:
        fprintf(test_h, "float %s%u;\n", var_name, index);
        break;
    case Bool:
        fprintf(test_h, "int %s%u;\n", var_name, index);
        break;
    case String:
        fprintf(test_h, "char *%s%u;\n", var_name, index);
        break;
    }
}

label new_label()
{
    static label counter = 0;
    return counter++;
}

int set_value(symb_value_type *dst, const symb_value_type src)
{
    dst->type = src.type;
    dst->reg = src.reg;
    switch (dst->type)
    {
    case Int:
        dst->value.vali = src.value.vali;
        break;
    case Float:
        dst->value.valf = src.value.valf;
        break;
    case Bool:
        dst->value.valb = src.value.valb;
        break;
    case String:
        strcpy(dst->value.vals, src.value.vals);
        break;
    default:
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

//----------------------------
//--- Types homogenisation ---
//----------------------------

#define CAST(ref, casted, c_type, valt, ret)              \
    ret.casted.reg = new_reg(ref->type);                  \
    ret.casted.type = ref->type;                          \
    ret.casted.value.valt = (c_type)(casted->value.vali); \
    ret.ref = *ref;                                       \
    fprintf(test_c, "rf%u = (float)ri%u;\n", ret.casted.reg, casted->reg);

homogene_pair homogenise(const symb_value_type *svt1, const symb_value_type *svt2)
{
    homogene_pair hp;
    if (svt1->type == svt2->type)
    {
        hp.svt1 = *svt1;
        hp.svt2 = *svt2;
        return hp;
    }

    // if svt1 is of type float, and svt2 of type int
    if (svt1->type == Float && svt2->type == Int)
    {
        CAST(svt1, svt2, float, valf, hp)
    }
    else if (svt2->type == Float && svt1->type == Int)
    {
        CAST(svt2, svt1, float, valf, hp)
    }

    return hp;
}

//--------------------------
//--- Numbers operations ---
//--------------------------

symb_value_type minus(symb_value_type v)
{
    symb_value_type ret;
    set_value(&ret, v);
    switch (ret.type)
    {
    case Int:
        ret.value.vali = -ret.value.vali;
        fprintf(test_c, "ri%u = - ri%u;\n", ret.reg, ret.reg);
        break;
    case Float:
        ret.value.valf = -ret.value.valf;
        fprintf(test_c, "rd%u = - rd%u;\n", ret.reg, ret.reg);
        break;
    case Bool:
        break;
    case String:
        break;
    }
    return ret;
}

#define BINARY_OP(ret, hp, op)                                     \
    switch (ret.type)                                              \
    {                                                              \
    case Int:                                                      \
        ret.value.vali = hp.svt1.value.vali op hp.svt2.value.vali; \
        fprintf(test_c, "ri%u = ri%u " #op " ri%u;\n",             \
                hp.svt1.reg,                                       \
                hp.svt1.reg,                                       \
                hp.svt2.reg);                                      \
        break;                                                     \
    case Float:                                                    \
        ret.value.valf = hp.svt1.value.valf op hp.svt2.value.valf; \
        fprintf(test_c, "rf%u = rf%u " #op " rf%u;\n",             \
                hp.svt1.reg,                                       \
                hp.svt1.reg,                                       \
                hp.svt2.reg);                                      \
        break;                                                     \
    case Bool:                                                     \
        break;                                                     \
    case String:                                                   \
        break;                                                     \
    }
symb_value_type add(symb_value_type svt1, symb_value_type svt2)
{
    symb_value_type ret;
    // we homogenize svt1's type and svt2's type
    homogene_pair hp = homogenise(&svt1, &svt2);
    // copying reg, type (and value but we don't care) from hp.svt1 into ret
    set_value(&ret, hp.svt1);
    BINARY_OP(ret, hp, +)
    return ret;
}

symb_value_type mult(symb_value_type svt1, symb_value_type svt2)
{
    symb_value_type ret;
    homogene_pair hp = homogenise(&svt1, &svt2);
    // copying reg, type (and value but we don't care) from svt1 into ret
    set_value(&ret, hp.svt1);
    BINARY_OP(ret, hp, *)
    return ret;
}

//---------------------------------
//--- Affectations, expressions ---
//---------------------------------

void print_affectation(const sid *sid, const symb_value_type *svt)
{
	char* name = sid_to_string(*sid);
	unsigned int index = get_symbol_value(*sid).index;
    switch (svt->type)
    {
    case Int:
        fprintf(test_c, "%s%u = ri%u;\n",
                name,
                index,
                svt->reg);
        break;
    case Float:
        fprintf(test_c, "%s%u = rf%u;\n",
                name,
                index,
                svt->reg);
        break;
    case Bool:
        fprintf(test_c, "%s%u = rb%u;\n",
                name,
                index,
                svt->reg);
        break;
    case String:
        break;
    }
}

void print_affectation_result(const sid *sid, const symb_value_type *svt)
{
    switch (svt->type)
    {
    case Int:
        fprintf(test_c, "printf(\"%s est de type <int> et vaut %%d\\n\", ri%u);\n\n",
                sid_to_string(*sid),
                svt->reg);
        break;
    case Float:
        fprintf(test_c, "printf(\"%s est de type <float> et vaut %%f\\n\", rf%u);\n\n",
                sid_to_string(*sid),
                svt->reg);
        break;
    case Bool:
        fprintf(test_c, "printf(\"%s est de type <bool> et vaut %%s\\n\", rb%u);\n\n",
                sid_to_string(*sid),
                svt->reg);
        break;
    case String:
        break;
    }
}

void print_expr_result(const symb_value_type *svt)
{
    switch (svt->type)
    {
    case Int:
        // fprintf(test_c, "printf(\"<exp> est de type <int> et vaut %d\\n\");\n\n", svt->value.vali);
        fprintf(test_c, "printf(\"<exp> est de type <int> et vaut %%d\\n\", ri%u);\n\n", svt->reg);
        break;
    case Float:
        // fprintf(test_c, "printf(\"<exp> est de type <float> et vaut %f\\n\");\n\n", svt->value.valf);
        fprintf(test_c, "printf(\"<exp> est de type <float> et vaut %%f\\n\", rf%u);\n\n", svt->reg);

        break;
    case Bool:
        // fprintf(test_c, "printf(\"<exp> est de type <bool> et vaut %s\\n\");\n\n", svt->value.valb ? "true" : "false");
        fprintf(test_c, "printf(\"<exp> est de type <int> et vaut %%d\\n\", r%u);\n\n", svt->reg);

        break;
    case String:
        // fprintf(test_c, "printf(\"<exp> est de type <string> et vaut \"%s\"\\n\");\n\n", svt->value.vals);
        break;
    }
}

void print_atom_exp(const symb_value_type *svt)
{
    switch (svt->type)
    {
    case Int:
        fprintf(test_c, "ri%u = %d;\n",
                svt->reg,
                svt->value.vali);
        break;
    case Float:
        fprintf(test_c, "rf%u = %f;\n",
                svt->reg,
                svt->value.valf);
        break;
    case Bool:
        fprintf(test_c, "rb%u = %d;\n",
                svt->reg,
                svt->value.valb);
        break;
    case String:
        break;
    }
}

void print_atom_exp_var(const symb_value_type *svt, const sid *sid)
{
	char* name = sid_to_string(*sid);
	unsigned int index = get_symbol_value(*sid).index;
    switch (svt->type)
    {
    case Int:
        fprintf(test_c, "ri%u = %s%u;\n",
                svt->reg,
                name,
                index);
        break;
    case Float:
        fprintf(test_c, "rf%u = %s%u;\n",
                svt->reg,
                name,
                index);
        break;
    case Bool:
        fprintf(test_c, "rb%u = %s%u;\n",
                svt->reg,
                name,
                index);
        break;
    case String:
        // fprintf(test_c, "rs%u = %s;\n",
        //         svt->reg,
        //         var);
        break;
    }
}

//--------------------
//--- If then else ---
//--------------------

symb_value_type if_init(const symb_value_type *bool)
{
    label depth = new_label();
    StackItem item;
    item.val_int = depth;
    stackPush(label_list, item);

    fprintf(test_c,
            "if (!rb%u)\n"
            "\tgoto label_else%u;\n",
            bool->reg,
            depth);

    return *bool;
}

symb_value_type if_then(const symb_value_type *expr)
{
    label depth = stackTop(label_list).val_int;
    fprintf(test_c, "goto label_end%u;\n", depth);
    fprintf(test_c, "label_else%u:\n", depth);
    return *expr;
}

symb_value_type if_else(const symb_value_type *expr)
{
    label depth = stackTop(label_list).val_int;
    stackPop(label_list);
    fprintf(test_c, "label_end%u:\n", depth);
    return *expr;
}

symb_value_type if_end(const symb_value_type *bool, const symb_value_type *expr1, const symb_value_type *expr2)
{
    symb_value_type ret;
    if (bool->value.valb)
        set_value(&ret, *expr1);
    else
        set_value(&ret, *expr2);
    switch (ret.type)
    {
    case Int:
        ret.reg = new_reg(Int);
        fprintf(test_c, "ri%u = ri%u;\n", ret.reg, bool->value.valb ? expr1->reg : expr2->reg);
        break;
    case Float:
        ret.reg = new_reg(Float);
        fprintf(test_c, "rf%u = rf%u;\n", ret.reg, bool->value.valb ? expr1->reg : expr2->reg);
        break;
    case String:
        break;
    case Bool:
        break;
    }

    return ret;
}

//----------------
//--- Booleans ---
//----------------

symb_value_type bool_or(const symb_value_type *b1, const symb_value_type *b2)
{
    symb_value_type ret;
    set_value(&ret, *b1);
    ret.value.valb = b1->value.valb || b2->value.valb;
    fprintf(test_c, "rb%u = rb%u || rb%u;\n", b1->reg, b1->reg, b2->reg);

    return ret;
}
symb_value_type bool_and(const symb_value_type *b1, const symb_value_type *b2)
{
    symb_value_type ret;
    set_value(&ret, *b1);
    ret.value.valb = b1->value.valb && b2->value.valb;
    fprintf(test_c, "rb%u = rb%u && rb%u;\n", b1->reg, b1->reg, b2->reg);

    return ret;
}

symb_value_type bool_not(const symb_value_type *b)
{
    symb_value_type ret;
    set_value(&ret, *b);
    ret.value.valb = !b->value.valb;
    fprintf(test_c, "rb%u = !rb%u;\n", b->reg, b->reg);

    return ret;
}
/*explication du #comparison : https://gcc.gnu.org/onlinedocs/cpp/Stringizing.html*/
#define CMP(hp, ret, comparison)                                                                   \
    switch (hp.svt1.type)                                                                          \
    {                                                                                              \
    case Int:                                                                                      \
        ret.value.valb = hp.svt1.value.vali comparison hp.svt2.value.vali;                         \
        fprintf(test_c, "rb%u = ri%u " #comparison " ri%u;\n", ret.reg, hp.svt1.reg, hp.svt2.reg); \
        break;                                                                                     \
    case Float:                                                                                    \
        ret.value.valb = hp.svt1.value.valf comparison hp.svt2.value.valf;                         \
        fprintf(test_c, "rb%u = rf%u " #comparison " rf%u;\n", ret.reg, hp.svt1.reg, hp.svt2.reg); \
        break;                                                                                     \
    case String:                                                                                   \
        break;                                                                                     \
    case Bool:                                                                                     \
        break;                                                                                     \
    }

symb_value_type bool_less_than(const symb_value_type *svt1, const symb_value_type *svt2)
{
    symb_value_type ret;
    ret.reg = new_reg(Bool);
    ret.type = Bool;
    homogene_pair hp = homogenise(svt1, svt2);
    CMP(hp, ret, <)
    return ret;
}
symb_value_type bool_greater_than(const symb_value_type *svt1, const symb_value_type *svt2)
{
    symb_value_type ret;
    ret.reg = new_reg(Bool);
    ret.type = Bool;
    homogene_pair hp = homogenise(svt1, svt2);
    CMP(hp, ret, >)
    return ret;
}
symb_value_type bool_less_equal(const symb_value_type *svt1, const symb_value_type *svt2)
{
    symb_value_type ret;
    ret.reg = new_reg(Bool);
    ret.type = Bool;
    homogene_pair hp = homogenise(svt1, svt2);
    CMP(hp, ret, <=)
    return ret;
}
symb_value_type bool_greater_equal(const symb_value_type *svt1, const symb_value_type *svt2)
{
    symb_value_type ret;
    ret.reg = new_reg(Bool);
    ret.type = Bool;
    homogene_pair hp = homogenise(svt1, svt2);
    CMP(hp, ret, >=)
    return ret;
}

symb_value_type bool_equal(const symb_value_type *svt1, const symb_value_type *svt2)
{
    symb_value_type ret;
    ret.reg = new_reg(Bool);
    ret.type = Bool;
    homogene_pair hp = homogenise(svt1, svt2);
    CMP(hp, ret, ==)
    return ret;
}

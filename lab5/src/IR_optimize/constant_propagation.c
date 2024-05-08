//
// Created by hby on 22-12-4.
//

#include <constant_propagation.h>

// v1 is old (in IN[blk]), v2 is new (pass from OUT[pred]) 
static CPValue meetValue(CPValue v1, CPValue v2) {
    /* TODO
     * 计算不同数据流数据汇入后变量的CPValue的meet值
     * 要考虑 UNDEF/CONST/NAC 的不同情况
     */
    // TODO();
    if(v1.kind == NAC || v2.kind ==NAC)
        return get_NAC();
    else if(v1.kind == CONST && v2.kind == UNDEF)
        return v1;
    else if(v1.kind == UNDEF && v2.kind == CONST)
        return v2;
    else
    {
        if(v1.const_val == v2.const_val)
            return v1;
        else // 说明不同路径上定制不一样，此值属于变量
            return get_NAC();
    }
}

static CPValue calculateValue(IR_OP_TYPE IR_op_type, CPValue v1, CPValue v2) {
    /* TODO
     * 计算二元运算结果的CPValue值
     * 要考虑 UNDEF/CONST/NAC 的不同情况
     * if(v1.kind == CONST && v2.kind == CONST) {
     *      int v1_const = v1.const_val, v2_const = v2.const_val;
     *      int res_const;
     *      switch (IR_op_type) {
     *          case IR_OP_ADD: res_const = v1_const + v2_const; break;
     *          case IR_OP_SUB: res_const = v1_const - v2_const; break;
     *          case IR_OP_MUL: res_const = v1_const * v2_const; break;
     *          case IR_OP_DIV:
     *              if(v2_const == 0) return get_UNDEF();
     *              res_const = v1_const / v2_const; break;
     *          default: assert(0);
     *      }
     *      return get_CONST(res_const);
     *  } ... 其他情况
     */
    // TODO();
    if(v1.kind == CONST && v2.kind == CONST)
    {
        int v1_const = v1.const_val, v2_const = v2.const_val;
        int res_const;
        switch (IR_op_type) {
            case IR_OP_ADD: res_const = v1_const + v2_const; break;
            case IR_OP_SUB: res_const = v1_const - v2_const; break;
            case IR_OP_MUL: res_const = v1_const * v2_const; break;
            case IR_OP_DIV:
                if(v2_const == 0) return get_UNDEF();
                res_const = v1_const / v2_const; break;
            default: assert(0);
        }
        return get_CONST(res_const);        
    }
    else if(v1.kind == UNDEF || v2.kind == UNDEF)
        return get_UNDEF();
    else 
        return get_NAC();
}

// UNDEF等价为在Map中不存在该Var的映射项

static CPValue
Fact_get_value_from_IR_var(Map_IR_var_CPValue *fact, IR_var var) {
    return VCALL(*fact, exist, var) ? VCALL(*fact, get, var) : get_UNDEF();
}

static CPValue
Fact_get_value_from_IR_val(Map_IR_var_CPValue *fact, IR_val val) {
    if(val.is_const) return get_CONST(val.const_val);
    else return Fact_get_value_from_IR_var(fact, val.var);
}

static void
Fact_update_value(Map_IR_var_CPValue *fact, IR_var var, CPValue val) {
    // 如果新值的定义是undef, 那么删除新的值
    if (val.kind == UNDEF) VCALL(*fact, delete, var);
    // 将新的值写入map当中
    else VCALL(*fact, set, var, val);
}

// fact is in IN[blk], var and val are the corresponding <var, CPValue> OUT[pred]
static bool
Fact_meet_value(Map_IR_var_CPValue *fact, IR_var var, CPValue val) {
    // 找到fact中var对应的项目
    CPValue old_val = Fact_get_value_from_IR_var(fact, var);
    CPValue new_val = meetValue(old_val, val);
    // for NAC and UNDEF, const_val == 0
    // 假如说fact中对应的类型和new相同，那么不进行更新
    if(old_val.kind == new_val.kind && old_val.const_val == new_val.const_val)
        return false;
    Fact_update_value(fact, var, new_val);
    return true;
}


//// ============================ Dataflow Analysis ============================

static void ConstantPropagation_teardown(ConstantPropagation *t) {
    for_map(IR_block_ptr, Map_ptr_IR_var_CPValue, i, t->mapInFact)
        RDELETE(Map_IR_var_CPValue, i->val);
    for_map(IR_block_ptr, Map_ptr_IR_var_CPValue, i, t->mapOutFact)
        RDELETE(Map_IR_var_CPValue, i->val);
    Map_IR_block_ptr_Map_ptr_IR_var_CPValue_teardown(&t->mapInFact);
    Map_IR_block_ptr_Map_ptr_IR_var_CPValue_teardown(&t->mapOutFact);
}

static bool
ConstantPropagation_isForward (ConstantPropagation *t) {
    // TODO: return isForward?;
    return true;
}

// 在initializeForward当中会进行调用

static Map_IR_var_CPValue*
ConstantPropagation_newBoundaryFact (ConstantPropagation *t, IR_function *func) {
    Map_IR_var_CPValue *fact = NEW(Map_IR_var_CPValue);
    /* TODO
     * 在Boundary(Entry/Exit?)中, 函数参数初始化为?
     * for_vec(IR_var, param_ptr, func->params)
     *     VCALL(*fact, insert, *param_ptr, get_UNDEF/CONST/NAC?());
     */
    // TODO();
    for_vec(IR_var, param_ptr, func->params)
        VCALL(*fact, insert, *param_ptr, get_NAC());
    return fact;
}

// 在initializeForward当中会进行调用

static Map_IR_var_CPValue*
ConstantPropagation_newInitialFact (ConstantPropagation *t) {
    return NEW(Map_IR_var_CPValue);
}

// 在initializeForward当中会进行调用

static void
ConstantPropagation_setInFact (ConstantPropagation *t,
                               IR_block *blk,
                               Map_IR_var_CPValue *fact) {
    VCALL(t->mapInFact, set, blk, fact);
}

// 在initializeForward当中会进行调用

static void
ConstantPropagation_setOutFact (ConstantPropagation *t,
                            IR_block *blk,
                            Map_IR_var_CPValue *fact) {
    VCALL(t->mapOutFact, set, blk, fact);
}

// 在workListdoSolve中会进行调用

static Map_IR_var_CPValue*
ConstantPropagation_getInFact (ConstantPropagation *t, IR_block *blk) {
    return VCALL(t->mapInFact, get, blk);
}

// 在workListdoSolve中会进行调用

static Map_IR_var_CPValue*
ConstantPropagation_getOutFact (ConstantPropagation *t, IR_block *blk) {
    return VCALL(t->mapOutFact, get, blk);
}

// 在workListdoSolve中会进行调用
// fact is one of the OUT[pred], target is IN[S]
static bool
ConstantPropagation_meetInto (ConstantPropagation *t,
                              Map_IR_var_CPValue *fact,
                              Map_IR_var_CPValue *target) {
    bool updated = false;
    for_map(IR_var, CPValue, i, *fact)
        updated |= Fact_meet_value(target, i->key, i->val);
    return updated;
}

// 在workListdoSolve中会进行调用

void ConstantPropagation_transferStmt (ConstantPropagation *t,
                                       IR_stmt *stmt,
                                       Map_IR_var_CPValue *fact) {
    if(stmt->stmt_type == IR_ASSIGN_STMT) {
        IR_assign_stmt *assign_stmt = (IR_assign_stmt*)stmt;
        IR_var def = assign_stmt->rd;
        CPValue use_val = Fact_get_value_from_IR_val(fact, assign_stmt->rs);
        /* TODO: solve IR_ASSIGN_STMT
         * Fact_update_value/Fact_meet_value?(...);
         */
        // TODO();
        Fact_update_value(fact, def, use_val);
    } else if(stmt->stmt_type == IR_OP_STMT) {
        IR_op_stmt *op_stmt = (IR_op_stmt*)stmt;
        IR_OP_TYPE IR_op_type = op_stmt->op;
        IR_var def = op_stmt->rd;
        CPValue rs1_val = Fact_get_value_from_IR_val(fact, op_stmt->rs1);
        CPValue rs2_val = Fact_get_value_from_IR_val(fact, op_stmt->rs2);
        /* TODO: solve IR_OP_STMT
         * Fact_update_value/Fact_meet_value?(...,calculateValue(...));
         */
        // TODO();
        Fact_update_value(fact, def, calculateValue(IR_op_type, rs1_val, rs2_val));
    } else { // Other Stmt with new_def
        IR_var def = VCALL(*stmt, get_def);
        if(def != IR_VAR_NONE) {
            /* TODO: solve stmt with new_def
             * Fact_update_value/Fact_meet_value?(...);
             */
            // TODO();
            Fact_update_value(fact, def, get_NAC());
        }
    }
}

// 在workListdoSolve中会进行调用
// 此处根据stmt，和这一轮计算得到的in_fact，计算当前这一轮的new_out_fact
bool ConstantPropagation_transferBlock (ConstantPropagation *t,
                                        IR_block *block,
                                        Map_IR_var_CPValue *in_fact,
                                        Map_IR_var_CPValue *out_fact) {
    Map_IR_var_CPValue *new_out_fact = ConstantPropagation_newInitialFact(t);
    ConstantPropagation_meetInto(t, in_fact, new_out_fact);
    for_list(IR_stmt_ptr, i, block->stmts) {
        IR_stmt *stmt = i->val;
        ConstantPropagation_transferStmt(t, stmt, new_out_fact);
    }
    bool updated = ConstantPropagation_meetInto(t, new_out_fact, out_fact);
    RDELETE(Map_IR_var_CPValue, new_out_fact);
    return updated;
}

void ConstantPropagation_print_result (ConstantPropagation *t, IR_function *func) {
    printf("Function %s: Constant Propagation Result\n", func->func_name);
    for_list(IR_block_ptr, i, func->blocks) {
        IR_block *blk = i->val;
        printf("=================\n");
        printf("{Block%s %p}\n", blk == func->entry ? "(Entry)" :
                                 blk == func->exit ? "(Exit)" : "",
               blk);
        IR_block_print(blk, stdout);
        // 此处的map表示变量名和变量类型的映射，某变量编号<->常量/变量/未定义
        Map_IR_var_CPValue *in_fact = VCALL(*t, getInFact, blk),
                *out_fact = VCALL(*t, getOutFact, blk);
        printf("[In]:  ");
        for_map(IR_var, CPValue , j, *in_fact) {
            printf("{v%u: ", j->key);
            if(j->val.kind == NAC) printf("NAC} ");
            else printf("#%d} ", j->val.const_val);
        }
        printf("\n");
        printf("[Out]: ");
        for_map(IR_var, CPValue , j, *out_fact) {
            printf("{v%u: ", j->key);
            if(j->val.kind == NAC)printf("NAC} ");
            else printf("#%d} ", j->val.const_val);
        }
        printf("\n");
        printf("=================\n");
    }
}

void ConstantPropagation_init(ConstantPropagation *t) {
    const static struct ConstantPropagation_virtualTable vTable = {
            .teardown        = ConstantPropagation_teardown,
            .isForward       = ConstantPropagation_isForward,
            .newBoundaryFact = ConstantPropagation_newBoundaryFact,
            .newInitialFact  = ConstantPropagation_newInitialFact,
            .setInFact       = ConstantPropagation_setInFact,
            .setOutFact      = ConstantPropagation_setOutFact,
            .getInFact       = ConstantPropagation_getInFact,
            .getOutFact      = ConstantPropagation_getOutFact,
            .meetInto        = ConstantPropagation_meetInto,
            .transferBlock   = ConstantPropagation_transferBlock,
            .printResult     = ConstantPropagation_print_result
    };
    t->vTable = &vTable;
    Map_IR_block_ptr_Map_ptr_IR_var_CPValue_init(&t->mapInFact);
    Map_IR_block_ptr_Map_ptr_IR_var_CPValue_init(&t->mapOutFact);
}

//// ============================ Optimize ============================

// 常量折叠, 将所有use替换为相应常量
static void block_constant_folding (ConstantPropagation *t, IR_block *blk) {
    // new_in_fact一开始是IN[B]的全部常量
    Map_IR_var_CPValue *blk_in_fact = VCALL(*t, getInFact, blk);
    Map_IR_var_CPValue *new_in_fact = ConstantPropagation_newInitialFact(t);
    ConstantPropagation_meetInto(t, blk_in_fact, new_in_fact);
    for_list(IR_stmt_ptr, i, blk->stmts) {
        IR_stmt *stmt = i->val;
        // 得到每个语句use的变量
        IR_use use = VCALL(*stmt, get_use_vec);
        for(int j = 0; j < use.use_cnt; j++)
        // 对于stmt使用到的变量，假如该变量本来不是常量，但是可以被替换为常量，那么将其赋值为常量
            if(!use.use_vec[j].is_const) {
                IR_var use_var = use.use_vec[j].var;
                CPValue use_CPVal = Fact_get_value_from_IR_var(new_in_fact, use_var);
                // 假如说use的变量类型为常量，则将其直接替换为常量
                if(use_CPVal.kind == CONST)
                    use.use_vec[j] = (IR_val){.is_const = true, .const_val = use_CPVal.const_val};
            }
        // 根据当前语句，修改可用的常量
        ConstantPropagation_transferStmt(t, stmt, new_in_fact);
    }
    RDELETE(Map_IR_var_CPValue, new_in_fact);
}

void ConstantPropagation_constant_folding (ConstantPropagation *t, IR_function *func) {
    for_list(IR_block_ptr, j, func->blocks) {
        IR_block *blk = j->val;
        block_constant_folding(t, blk);
    }
}



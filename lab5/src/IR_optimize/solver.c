//
// Created by hby on 22-12-2.
//

#include <dataflow_analysis.h>

//// ============================ Forward ============================

static void initializeForward(DataflowAnalysis *t, IR_function *func) {
    for_list(IR_block_ptr, i, func->blocks) {
        // 常量传播: newInitialFact return an empty map<IR_var, CPValue>
        // 可用表达式：返回全集
        void *new_in_fact = VCALL(*t, newInitialFact);
        VCALL(*t, setInFact, i->val, new_in_fact);
        if(i->val == func->entry) { // Entry为Boundary, 需要特殊处理
            // 常量传播: return a map<IR_var, CPValue> of params, params are NAC
            // 可用表达式：返回空集
            void *entry_out_fact = VCALL(*t, newBoundaryFact, func);
            VCALL(*t, setOutFact, i->val, entry_out_fact);
        } else {

            void *new_out_fact = VCALL(*t, newInitialFact);
            VCALL(*t, setOutFact, i->val, new_out_fact);
        }
    }
}

static void iterativeDoSolveForward(DataflowAnalysis *t, IR_function *func) {
    while(true) {
        bool updated = false;
        // 遍历所有blk
        for_list(IR_block_ptr, i, func->blocks) {
            IR_block *blk = i->val;
            // 获取 IN[blk] 与 OUT[blk]
            Fact *in_fact = VCALL(*t, getInFact, blk), *out_fact = VCALL(*t, getOutFact, blk);
            // IN[blk] = meetAll(OUT[pred] for pred in AllPred[blk])
            // 可用表达式：in_fact(IN[B]) =取交集（所有OUT[pred]）
            for_list(IR_block_ptr, j, *VCALL(func->blk_pred, get, blk)) {
                IR_block *pred = j->val;
                Fact *pred_out_fact = VCALL(*t, getOutFact, pred);
                VCALL(*t, meetInto, pred_out_fact, in_fact);
            }
            // 若OUT[blk]发生update, 则进行继续迭代
            // 可用表达式：out_fact(out[B]) = e_genB U (IN[B] - e_killB)
            if(VCALL(*t, transferBlock, blk, in_fact, out_fact))
                updated = true;
        }
        if(!updated) break;
    }
}

static void worklistDoSolveForward(DataflowAnalysis *t, IR_function *func) {
    List_IR_block_ptr worklist;
    List_IR_block_ptr_init(&worklist);
    // 初始化将所有blk插入worklist
    for_list(IR_block_ptr, i, func->blocks)
        VCALL(worklist, push_back, i->val);
    while(worklist.tail != NULL) {
        // 从worklist的头部中取出 blk
        IR_block *blk = worklist.head->val;
        VCALL(worklist, pop_front);
        // 获取 IN[blk] 与 OUT[blk]
        Fact *in_fact = VCALL(*t, getInFact, blk), *out_fact = VCALL(*t, getOutFact, blk);
        // IN[blk] = meetAll(OUT[pred] for pred in AllPred[blk]) 
        // 关键部分，处理所有前驱节点的out[pred] 和当前节点的in[blk]
        for_list(IR_block_ptr, i, *VCALL(func->blk_pred, get, blk)) {
            IR_block *pred = i->val;
            Fact *pred_out_fact = VCALL(*t, getOutFact, pred);
            VCALL(*t, meetInto, pred_out_fact, in_fact);
        }
        // 若OUT[blk]发生update, 则将其后继全部加入 worklist
        if(VCALL(*t, transferBlock, blk, in_fact, out_fact))
            for_list(IR_block_ptr, i, *VCALL(func->blk_succ, get, blk))
                VCALL(worklist, push_back, i->val);
    }
    List_IR_block_ptr_teardown(&worklist);
}

//// ============================ Backward ============================

/* TODO:
 * 根据前向求解器的实现，完成后向求解器的实现
 */

static void initializeBackward(DataflowAnalysis *t, IR_function *func) {
    for_list(IR_block_ptr, i, func->blocks) {
        // 活跃变量：全部初始化为空集
        void *new_out_fact = VCALL(*t, newInitialFact);
        VCALL(*t, setOutFact, i->val, new_out_fact);
        if(i->val == func->exit) { // Entry为Boundary, 需要特殊处理
            void *exit_in_fact = VCALL(*t, newBoundaryFact, func);
            VCALL(*t, setInFact, i->val, exit_in_fact);
        } else {
            void *new_in_fact = VCALL(*t, newInitialFact);
            VCALL(*t, setInFact, i->val, new_in_fact);
        }
    }
}

static void iterativeDoSolveBackward(DataflowAnalysis *t, IR_function *func) {
    while(true) {
        bool updated = false;
        // 遍历所有blk
        for_list(IR_block_ptr, i, func->blocks) {
            IR_block *blk = i->val;
            // 获取 IN[blk] 与 OUT[blk]
            Fact *in_fact = VCALL(*t, getInFact, blk), *out_fact = VCALL(*t, getOutFact, blk);
            // OUT[blk] = meetAll(IN[success] for success in AllSuccess[blk])
            for_list(IR_block_ptr, j, *VCALL(func->blk_succ, get, blk)) {
                IR_block *succ = j->val;
                Fact *succ_in_fact = VCALL(*t, getInFact, succ);
                VCALL(*t, meetInto, succ_in_fact, out_fact);
            }
            // 若IN[blk]发生update, 则进行继续迭代
            if(VCALL(*t, transferBlock, blk, in_fact, out_fact))
                updated = true;
        }
        if(!updated) break;
    }
}

static void worklistDoSolveBackward(DataflowAnalysis *t, IR_function *func) {
    List_IR_block_ptr worklist;
    List_IR_block_ptr_init(&worklist);
    // 初始化将所有blk插入worklist
    for_list(IR_block_ptr, i, func->blocks)
        VCALL(worklist, push_back, i->val);
    while(worklist.tail != NULL) {
        // 从worklist的头部中取出 blk
        IR_block *blk = worklist.head->val;
        VCALL(worklist, pop_front);
        // 获取 IN[blk] 与 OUT[blk]
        Fact *in_fact = VCALL(*t, getInFact, blk), *out_fact = VCALL(*t, getOutFact, blk);
        // OUT[blk] = meetAll(IN[succ]) 
        for_list(IR_block_ptr, i, *VCALL(func->blk_succ, get, blk)) {
            IR_block *succ = i->val;
            Fact *succ_in_fact = VCALL(*t, getInFact, succ);
            VCALL(*t, meetInto, succ_in_fact, out_fact);
        }
        // 若IN[blk]发生update, 则将其pred全部加入 worklist
        if(VCALL(*t, transferBlock, blk, in_fact, out_fact))
            for_list(IR_block_ptr, i, *VCALL(func->blk_pred, get, blk))
                VCALL(worklist, push_back, i->val);
    }
    List_IR_block_ptr_teardown(&worklist);
}

//// ============================ Solver ============================

// 具有worklist_solver和interative_solver两种处理函数，但是只用到了worklist_solver

void worklist_solver(DataflowAnalysis *t, IR_function *func) {
    if(VCALL(*t, isForward)) {
        initializeForward(t, func);
        worklistDoSolveForward(t, func);
    } else {
        initializeBackward(t, func);
        worklistDoSolveBackward(t, func);
    }
}

void iterative_solver(DataflowAnalysis *t, IR_function *func) {
    if(VCALL(*t, isForward)) {
        initializeForward(t, func);
        iterativeDoSolveForward(t, func);
    } else {
        initializeBackward(t, func);
        iterativeDoSolveBackward(t, func);
    }
}
#pragma once
//#ifndef OOO_CPU_H
//#define OOO_CPU_H

#include "types.h"

//X #include "cache.h"
//X 
//X #ifdef CRC2_COMPILE
//X #define STAT_PRINTING_PERIOD 1000000
//X #else
//X #define STAT_PRINTING_PERIOD 10000000
//X #endif
//X #define DEADLOCK_CYCLE 1000000
//X 
//X using namespace std;
//X 
//X // CORE PROCESSOR
//X #define FETCH_WIDTH 6
//X #define DECODE_WIDTH 6
//X #define EXEC_WIDTH 6
//X #define LQ_WIDTH 2
//X #define SQ_WIDTH 2
//X #define RETIRE_WIDTH 4
//X #define SCHEDULER_SIZE 128
//X #define BRANCH_MISPREDICT_PENALTY 1
//X //#define SCHEDULING_LATENCY 0
//X //#define EXEC_LATENCY 0
//X //#define DECODE_LATENCY 2
//X 
//X #define STA_SIZE (ROB_SIZE*NUM_INSTR_DESTINATIONS_SPARC)
//X 
//X extern uint32_t SCHEDULING_LATENCY, EXEC_LATENCY, DECODE_LATENCY;
//X 
// cpu
class O3_CPU {
  public:
    uint32_t cpu;

//X     // trace
//X     FILE *trace_file;
//X     char trace_string[1024];
//X     char gunzip_command[1024];
//X 
//X     // instruction
//X     input_instr next_instr;
//X     input_instr current_instr;
//X     cloudsuite_instr current_cloudsuite_instr;
//X     uint64_t instr_unique_id, completed_executions, 
//X              begin_sim_cycle, begin_sim_instr, 
//X              last_sim_cycle, last_sim_instr,
//X              finish_sim_cycle, finish_sim_instr,
//X              warmup_instructions, simulation_instructions, instrs_to_read_this_cycle, instrs_to_fetch_this_cycle,
//X              next_print_instruction, num_retired;
//X     uint32_t inflight_reg_executions, inflight_mem_executions, num_searched;
//X     uint32_t next_ITLB_fetch;
//X 
//X     // reorder buffer, load/store queue, register file
//X     CORE_BUFFER IFETCH_BUFFER{"IFETCH_BUFFER", FETCH_WIDTH*2};
//X     CORE_BUFFER DECODE_BUFFER{"DECODE_BUFFER", DECODE_WIDTH*3};
//X     CORE_BUFFER ROB{"ROB", ROB_SIZE};
//X     LOAD_STORE_QUEUE LQ{"LQ", LQ_SIZE}, SQ{"SQ", SQ_SIZE};
//X 
//X     // store array, this structure is required to properly handle store instructions
//X     uint64_t STA[STA_SIZE], STA_head, STA_tail; 
//X 
//X     // Ready-To-Execute
//X     uint32_t RTE0[ROB_SIZE], RTE0_head, RTE0_tail, 
//X              RTE1[ROB_SIZE], RTE1_head, RTE1_tail;  
//X 
//X     // Ready-To-Load
//X     uint32_t RTL0[LQ_SIZE], RTL0_head, RTL0_tail, 
//X              RTL1[LQ_SIZE], RTL1_head, RTL1_tail;  
//X 
//X     // Ready-To-Store
//X     uint32_t RTS0[SQ_SIZE], RTS0_head, RTS0_tail,
//X              RTS1[SQ_SIZE], RTS1_head, RTS1_tail;
//X 
//X     // branch
//X     int branch_mispredict_stall_fetch; // flag that says that we should stall because a branch prediction was wrong
//X     int mispredicted_branch_iw_index; // index in the instruction window of the mispredicted branch.  fetch resumes after the instruction at this index executes
//X     uint8_t  fetch_stall;
//X     uint64_t fetch_resume_cycle;
//X     uint64_t num_branch, branch_mispredictions;
//X     uint64_t total_rob_occupancy_at_branch_mispredict;
//X   uint64_t total_branch_types[8];
//X 
//X     // TLBs and caches
//X     CACHE ITLB{"ITLB", ITLB_SET, ITLB_WAY, ITLB_SET*ITLB_WAY, ITLB_WQ_SIZE, ITLB_RQ_SIZE, ITLB_PQ_SIZE, ITLB_MSHR_SIZE},
//X           DTLB{"DTLB", DTLB_SET, DTLB_WAY, DTLB_SET*DTLB_WAY, DTLB_WQ_SIZE, DTLB_RQ_SIZE, DTLB_PQ_SIZE, DTLB_MSHR_SIZE},
//X           STLB{"STLB", STLB_SET, STLB_WAY, STLB_SET*STLB_WAY, STLB_WQ_SIZE, STLB_RQ_SIZE, STLB_PQ_SIZE, STLB_MSHR_SIZE},
//X           L1I{"L1I", L1I_SET, L1I_WAY, L1I_SET*L1I_WAY, L1I_WQ_SIZE, L1I_RQ_SIZE, L1I_PQ_SIZE, L1I_MSHR_SIZE},
//X           L1D{"L1D", L1D_SET, L1D_WAY, L1D_SET*L1D_WAY, L1D_WQ_SIZE, L1D_RQ_SIZE, L1D_PQ_SIZE, L1D_MSHR_SIZE},
//X           L2C{"L2C", L2C_SET, L2C_WAY, L2C_SET*L2C_WAY, L2C_WQ_SIZE, L2C_RQ_SIZE, L2C_PQ_SIZE, L2C_MSHR_SIZE};
//X 
//X   // trace cache for previously decoded instructions
//X   
//X     // constructor
    O3_CPU() {
        cpu = 0;

//X         // trace
//X         trace_file = NULL;
//X 
//X         // instruction
//X         instr_unique_id = 0;
//X         completed_executions = 0;
//X         begin_sim_cycle = 0;
//X         begin_sim_instr = 0;
//X         last_sim_cycle = 0;
//X         last_sim_instr = 0;
//X         finish_sim_cycle = 0;
//X         finish_sim_instr = 0;
//X         warmup_instructions = 0;
//X         simulation_instructions = 0;
//X         instrs_to_read_this_cycle = 0;
//X         instrs_to_fetch_this_cycle = 0;
//X 
//X         next_print_instruction = STAT_PRINTING_PERIOD;
//X         num_retired = 0;
//X 
//X         inflight_reg_executions = 0;
//X         inflight_mem_executions = 0;
//X         num_searched = 0;
//X 
//X         next_ITLB_fetch = 0;
//X 
//X         // branch
//X         branch_mispredict_stall_fetch = 0;
//X         mispredicted_branch_iw_index = 0;
//X         fetch_stall = 0;
//X 	fetch_resume_cycle = 0;
//X         num_branch = 0;
//X         branch_mispredictions = 0;
//X 	for(uint32_t i=0; i<8; i++)
//X 	  {
//X 	    total_branch_types[i] = 0;
//X 	  }
//X 	
//X         for (uint32_t i=0; i<STA_SIZE; i++)
//X 	  STA[i] = UINT64_MAX;
//X         STA_head = 0;
//X         STA_tail = 0;
//X 
//X         for (uint32_t i=0; i<ROB_SIZE; i++) {
//X 	  RTE0[i] = ROB_SIZE;
//X 	  RTE1[i] = ROB_SIZE;
//X         }
//X         RTE0_head = 0;
//X         RTE1_head = 0;
//X         RTE0_tail = 0;
//X         RTE1_tail = 0;
//X 
//X         for (uint32_t i=0; i<LQ_SIZE; i++) {
//X 	  RTL0[i] = LQ_SIZE;
//X 	  RTL1[i] = LQ_SIZE;
//X         }
//X         RTL0_head = 0;
//X         RTL1_head = 0;
//X         RTL0_tail = 0;
//X         RTL1_tail = 0;
//X 
//X         for (uint32_t i=0; i<SQ_SIZE; i++) {
//X 	  RTS0[i] = SQ_SIZE;
//X 	  RTS1[i] = SQ_SIZE;
//X         }
//X         RTS0_head = 0;
//X         RTS1_head = 0;
//X         RTS0_tail = 0;
//X         RTS1_tail = 0;
    }

//X     // functions
//X     void read_from_trace(),
//X          fetch_instruction(),
//X          decode_and_dispatch(),
//X          schedule_instruction(),
//X          execute_instruction(),
//X          schedule_memory_instruction(),
//X          execute_memory_instruction(),
//X          do_scheduling(uint32_t rob_index),  
//X          reg_dependency(uint32_t rob_index),
//X          do_execution(uint32_t rob_index),
//X          do_memory_scheduling(uint32_t rob_index),
//X          operate_lsq(),
//X          complete_execution(uint32_t rob_index),
//X          reg_RAW_dependency(uint32_t prior, uint32_t current, uint32_t source_index),
//X          reg_RAW_release(uint32_t rob_index),
//X          mem_RAW_dependency(uint32_t prior, uint32_t current, uint32_t data_index, uint32_t lq_index),
//X          handle_o3_fetch(PACKET *current_packet, uint32_t cache_type),
//X          handle_merged_translation(PACKET *provider),
//X          handle_merged_load(PACKET *provider),
//X          release_load_queue(uint32_t lq_index),
//X          complete_instr_fetch(PACKET_QUEUE *queue, uint8_t is_it_tlb),
//X          complete_data_fetch(PACKET_QUEUE *queue, uint8_t is_it_tlb);
//X 
//X     void initialize_core();
//X     void add_load_queue(uint32_t rob_index, uint32_t data_index),
//X          add_store_queue(uint32_t rob_index, uint32_t data_index),
//X          execute_store(uint32_t rob_index, uint32_t sq_index, uint32_t data_index);
//X     int  execute_load(uint32_t rob_index, uint32_t sq_index, uint32_t data_index);
//X     void check_dependency(int prior, int current);
//X     void operate_cache();
//X     void update_rob();
//X     void retire_rob();
//X 
//X     uint32_t  add_to_rob(ooo_model_instr *arch_instr),
//X               check_rob(uint64_t instr_id);
//X 
//X     uint32_t add_to_ifetch_buffer(ooo_model_instr *arch_instr);
//X     uint32_t add_to_decode_buffer(ooo_model_instr *arch_instr);
//X 
//X     uint32_t check_and_add_lsq(uint32_t rob_index);
//X 
//X     // branch predictor
     uint8_t predict_branch(uint64_t ip);
     void initialize_branch_predictor();
     void last_branch_result(uint64_t ip, uint8_t taken);
//X
//X     void    initialize_branch_predictor(),
//X             last_branch_result(uint64_t ip, uint8_t taken);
//X 
//X   // code prefetching
//X   void l1i_prefetcher_initialize();
//X   void l1i_prefetcher_branch_operate(uint64_t ip, uint8_t branch_type, uint64_t branch_target);
//X   void l1i_prefetcher_cache_operate(uint64_t v_addr, uint8_t cache_hit, uint8_t prefetch_hit);
//X   void l1i_prefetcher_cycle_operate();
//X   void l1i_prefetcher_cache_fill(uint64_t v_addr, uint32_t set, uint32_t way, uint8_t prefetch, uint64_t evicted_v_addr);
//X   void l1i_prefetcher_final_stats();
//X   int prefetch_code_line(uint64_t pf_v_addr); 

  uint32_t tst_idx=0;

};

extern O3_CPU ooo_cpu[NUM_CPUS];

//#endif

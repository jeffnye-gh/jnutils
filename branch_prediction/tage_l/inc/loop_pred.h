#pragma once
#include <inttypes.h>
#include <iostream>
#include <ostream>

#define ENTRIES 256 // Number of entries in the predictor table
#define WAY 4       // Associativity of the predictor table
#define LOGIND 6    // Number of bits required to index into the table
#define LOGWAY 2    // Number of bits required to determine the way at a particular index
#define TAGSIZE 14  // Number of bits to represent tag in the table
#define ITERSIZE 14 // Max size of the loop that the predictor can predict properly
#define AGE 31      // Intiial age of the the entry

struct Entry
{
    uint16_t tag;          // Stores the 14-bit tag for the entry
    uint16_t past_iter;    // Stores the 14-bit count for the number of iterations seen in past
    uint16_t current_iter; // Stores the 14-bit count for the number of iterations seen currently
    uint8_t age;           // 8-bit counter signifying age of entry
    uint8_t confidence;    // 2-bit counter signifying confidence in prediction
  int dump_entry(int id,bool filter,std::ostream &os=std::cout);

};

class LoopPred
{
public:
    Entry table[ENTRIES]; // Predictor table
    int ind;              // Index in loop
    int hit;              // The way in the loop where we get a hit else -1
    int ptag;             // The tag calculated
    uint8_t seed;

public:
    bool is_valid;     // Validity of prediction
    uint8_t loop_pred; // The prediction returned for current PC

    void init();
    uint8_t get_pred(uint64_t pc);
    void update_entry(uint8_t taken, uint8_t tage_pred);
    void dump(bool filter,std::ostream &os=std::cout);

    int tst_idx{0};
};

//X // Intialises the predictor
//X void LoopPred::init()
//X {
//X     seed = 0;
//X     for (int i = 0; i < ENTRIES; i++)
//X     {
//X         table[i].tag = 0;
//X         table[i].past_iter = 0;
//X         table[i].current_iter = 0;
//X         table[i].age = 0;
//X         table[i].confidence = 0;
//X     }
//X }
//X 
//X // Predicts based on the current pc
//X uint8_t LoopPred::get_pred(uint64_t pc)
//X {
//X     hit = -1;
//X     ind = (pc & ((1 << LOGIND) - 1)) << LOGWAY;         // Calculate index
//X     ptag = (pc >> LOGIND) & ((1 << TAGSIZE) - 1);       // Calculate tag
//X 
//X     for (int i = ind; i < ind + WAY; i++)
//X     {
//X         // If a matching block is found, set hit and valid values
//X         // Return based on current and past counts of iterations
//X         if (table[i].tag == ptag)
//X         {
//X             hit = i;
//X             is_valid = (table[i].confidence == 3);
//X             if (table[i].current_iter + 1 == table[i].past_iter)
//X             {
//X                 loop_pred = 0;
//X                 return 0;
//X             }
//X             loop_pred = 1;
//X             return 1;
//X         }
//X     }
//X 
//X     // No matching entry found in table; return false
//X     is_valid = false;
//X     loop_pred = 0;
//X     return 0;
//X }
//X 
//X // Updates the predictor table based on the prediction and actually taken/not taken branch
//X void LoopPred::update_entry(uint8_t taken, uint8_t tage_pred)
//X {
//X     if (hit >= 0)
//X     {
//X         Entry &entry = table[ind + hit];
//X         if (is_valid)
//X         {
//X             // If the predicton was wrong, free the entry
//X             if (taken != loop_pred)
//X             {
//X                 entry.past_iter = 0;
//X                 entry.age = 0;
//X                 entry.confidence = 0;
//X                 entry.current_iter = 0;
//X                 return;
//X             }
//X 
//X             if (taken != tage_pred)
//X             {
//X                 if (entry.age < AGE)
//X                     entry.age++;
//X             }
//X         }
//X 
//X         entry.current_iter++;
//X         entry.current_iter &= ((1 << ITERSIZE) - 1);
//X 
//X         // If the iteration is greater than what was seen last time, free the entry
//X         if (entry.current_iter > entry.past_iter)
//X         {
//X             entry.confidence = 0;
//X             if (entry.past_iter != 0)
//X             {
//X                 entry.past_iter = 0;
//X                 entry.age = 0;
//X                 entry.confidence = 0;
//X             }
//X         }
//X 
//X         if (!taken)
//X         {
//X             if (entry.current_iter == entry.past_iter)
//X             {
//X                 // Increase the confidence if correct
//X                 if (entry.confidence < 3)
//X                     entry.confidence++;
//X                 
//X                 // We do not care for loops with < 3 iterations
//X                 if ((entry.past_iter > 0) && (entry.past_iter < 3))
//X                 {
//X                     entry.past_iter = 0;
//X                     entry.age = 0;
//X                     entry.confidence = 0;
//X                 }
//X             }
//X             else
//X             {
//X                 // Set the newly allocated entry
//X                 if (entry.past_iter == 0)
//X                 {
//X                     entry.confidence = 0;
//X                     entry.past_iter = entry.current_iter;
//X                 }
//X                 // else free the entry
//X                 else
//X                 {
//X                     entry.past_iter = 0;
//X                     entry.age = 0;
//X                     entry.confidence = 0;
//X                 }
//X             }
//X             entry.current_iter = 0;
//X         }
//X     }
//X     // If the branch is taken but there is no entry, we must allocate one entry in the table
//X     else if (taken)
//X     {
//X         seed = (seed + 1) & 3;
//X         for (int i = 0; i < WAY; i++)
//X         {
//X             int j = ind + ((seed + i) & 3);
//X             if (table[j].age == 0)
//X             {
//X                 table[j].tag = ptag;
//X                 table[j].past_iter = 0;
//X                 table[j].current_iter = 1;
//X                 table[j].age = AGE;
//X                 table[j].confidence = 0;
//X                 break;
//X             }
//X             else if (table[j].age > 0)
//X                 table[j].age--;
//X         }
//X     }
//X }

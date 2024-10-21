
#include "types.h"
#include "loop_pred.h"
#include <ostream>
#include <iomanip>
#include <iostream>
using namespace std;

extern std::ostream *lp_os;

// ====================================================================
int Entry::dump_entry(int id,bool filter,std::ostream &os)
{
  int not_default = 0;
  uint32_t _tag  = CAST(tag);
  uint32_t _past = CAST(past_iter);
  uint32_t _curr = CAST(current_iter);
  uint32_t _age  = CAST(age);
  uint32_t _conf = CAST(confidence);
  if(_tag != 0 || _past != 0 || _curr != 0 || _age != 0 || _conf != 0) {
    not_default = 1;
  }

  if(!filter || (filter && not_default == 1)) {
    os<<"-I: i:0x"<<HEX(2,id);
    os<<" tag:0x"<<HEX(4,_tag);
    os<<" pst:" <<DEC<<_past;
    os<<" cur:" <<DEC<<_curr;
    os<<" age:" <<DEC<<_age;
    os<<" cnf:" <<DEC<<_conf<<std::endl;
  }
  return not_default;
}

// ====================================================================
void LoopPred::dump(bool filter,std::ostream &os)
{
  os<<"-I: #ENTRIES : "<<DEC<<ENTRIES<<std::endl;
  os<<"-I: last seed: "<<DEC<<CAST(seed)<<std::endl;

  int not_default = 0;

  for(size_t i=0;i<ENTRIES;++i) {
    //os<<"-I: Entry "<<i<<std::endl;
    not_default += table[i].dump_entry(i,filter,os);
  }

  os<<"-I: non-zero entries: " <<not_default<<endl;

}

// --------------------------------------------------------------------
// Intialises the predictor
// --------------------------------------------------------------------
void LoopPred::init()
{
    seed = 0;
    for (int i = 0; i < ENTRIES; i++)
    {
        table[i].tag = 0;
        table[i].past_iter = 0;
        table[i].current_iter = 0;
        table[i].age = 0;
        table[i].confidence = 0;
    }
}

// Predicts based on the current pc
uint8_t LoopPred::get_pred(uint64_t pc)
{
    hit = -1;
    ind = (pc & ((1 << LOGIND) - 1)) << LOGWAY;         // Calculate index
    ptag = (pc >> LOGIND) & ((1 << TAGSIZE) - 1);       // Calculate tag

(*lp_os)<<endl;
(*lp_os)<<"-I: 19 sh_pc   "<<HEX(16,pc)<<endl;
(*lp_os)<<"-I: 19 index   "<<HEX(16,ind)<<endl;
(*lp_os)<<"-I: 19 ptag    "<<HEX(16,ptag)<<endl;
(*lp_os)<<"-I: 19 tst_idx "<<DEC<<tst_idx<<endl; //#19

    for (int i = ind; i < ind + WAY; i++)
    {
        // If a matching block is found, set hit and valid values
        // Return based on current and past counts of iterations
        if (table[i].tag == ptag)
        {
            hit = i;
            is_valid = (table[i].confidence == 3);
            if (table[i].current_iter + 1 == table[i].past_iter)
            {
                loop_pred = 0;

//(*lp_os)<<"-I: 21 hit index "<<HEX(4,i)<<" loop_pred 0"<<endl; //#21
(*lp_os)<<"-I: 21 hit index "<<HEX(4,i)
        <<" cur_itr+1 "<<DEC<<(table[i].current_iter + 1)
        <<" past_itr "<<DEC<<(table[i].past_iter)
        <<" loop_pred 0"<<endl; //#21


++tst_idx;

                return 0;
            }
            loop_pred = 1;

//(*lp_os)<<"-I: 22 hit index "<<HEX(4,i)<<" loop_pred 1"<<endl; //#22
(*lp_os)<<"-I: 22 hit index "<<HEX(4,i)
        <<" cur_itr+1 "<<DEC<<(table[i].current_iter + 1)
        <<" past_itr "<<DEC<<(table[i].past_iter)
        <<" loop_pred 1"<<endl; //#22

++tst_idx;

            return 1;
        }
    }

(*lp_os)<<"-I: 23 miss"<<endl; //#23
++tst_idx;

    // No matching entry found in table; return false
    is_valid = false;
    loop_pred = 0;
    return 0;
}

// Updates the predictor table based on the prediction and actually taken/not taken branch
void LoopPred::update_entry(uint8_t taken, uint8_t tage_pred)
{

(*lp_os)<<"-I: 20 update"
        <<" taken "    <<CAST(taken)
        <<" tage_pred "<<CAST(tage_pred)
        <<" loop_pred "<<CAST(loop_pred)
        <<" hit "      <<DEC<<(hit>0)<<endl; //#20

//bool debug = false;
//int index = ind + CAST(hit);

    if (hit >= 0)
    {
//if((CAST(ind) + CAST(hit)) == 0x55) debug = true;
//        Entry &entry = table[ind + hit];
//        Entry &entry = table[hit];
        Entry &entry = table[ind + (hit&0x3)];
        if (is_valid)
        {
            // If the predicton was wrong, free the entry
            if (taken != loop_pred)
            {

(*lp_os)<<"-I: -5 update taken != loop_pred"<<endl; //#5
                entry.past_iter = 0;
                entry.age = 0;
                entry.confidence = 0;
                entry.current_iter = 0;
//if(debug) cout<<"-I: 0x55 current_iter = 0"<<endl;
                return;
            }

            if (taken != tage_pred)
            {

(*lp_os)<<"-I: -6 update taken != tage_pred"<<endl; //#6

                if (entry.age < AGE) {
                    entry.age++;
                }
            }
        }

        entry.current_iter++;
//cout<<"-I:  "<<HEX(4,index)<<" current_iter ++, "<<CAST(entry.current_iter)<<endl;
        entry.current_iter &= ((1 << ITERSIZE) - 1);

        // If the iteration is greater than what was seen last time, free the entry
        if (entry.current_iter > entry.past_iter)
        {

(*lp_os)<<"-I: -7 update curr_itr > past_iter"<<endl; //#7

            entry.confidence = 0;
            if (entry.past_iter != 0)
            {
(*lp_os)<<"-I: -8 update past iter != 0"<<endl; //#8
                entry.past_iter = 0;
                entry.age = 0;
                entry.confidence = 0;
            }
        }

        if (!taken)
        {
            if (entry.current_iter == entry.past_iter)
            {
(*lp_os)<<"-I: -9 update curr_itr == past_iter increase conf"<<endl; //#9
                // Increase the confidence if correct
                if (entry.confidence < 3) {
(*lp_os)<<"-I: 10 update cnf < 3"<<endl; //#10
                    entry.confidence++;
                }
 
                // We do not care for loops with < 3 iterations
                if ((entry.past_iter > 0) && (entry.past_iter < 3))
                {
(*lp_os)<<"-I: 11 update clear on small loop"<<endl; //#11
                    entry.past_iter = 0;
                    entry.age = 0;
                    entry.confidence = 0;
                }
            }
            else
            {
                // Set the newly allocated entry
                if (entry.past_iter == 0)
                {
(*lp_os)<<"-I: 12 update set new alloc entry"<<endl; //#12
                    entry.confidence = 0;
                    entry.past_iter = entry.current_iter;
                }
                // else free the entry
                else
                {
(*lp_os)<<"-I: 13 update set free alloc entry"<<endl; //#13
                    entry.past_iter = 0;
                    entry.age = 0;
                    entry.confidence = 0;
                }
            }
(*lp_os)<<"-I: 14 update clear cur itr"<<endl; //#14
            entry.current_iter = 0;
        }
    }
    // If the branch is taken but there is no entry, we must allocate one entry in the table
    else if (taken)
    {
(*lp_os)<<"-I: 15 update taken no entry"<<endl; //#15
        seed = (seed + 1) & 3;
        for (int i = 0; i < WAY; i++)
        {
            int j = ind + ((seed + i) & 3);
            if (table[j].age == 0)
            {
(*lp_os)<<"-I: 16 update alloc" //#16
        <<" seed " << DEC<<CAST(seed)
        <<" ind "  << HEX(2,CAST(ind))
        <<" idx "  << HEX(2,CAST(ind>>2))
        <<" wu "   << DEC<<CAST(seed+i) //'way used'
        <<" age "  << DEC<<CAST(table[j].age)
        //<<" j "
        <<endl;

                table[j].tag = ptag;
                table[j].past_iter = 0;
                table[j].current_iter = 1;
                table[j].age = AGE;
                table[j].confidence = 0;
                break;
            }
            else if (table[j].age > 0) {
(*lp_os)<<"-I: 17 update decr age"<<endl; //#17
                table[j].age--;
            }
        }
    }
    else {

(*lp_os)<<"-I: 18 update !hit !taken"<<endl; //#18

    }
}

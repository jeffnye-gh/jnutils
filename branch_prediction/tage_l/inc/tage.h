#pragma once
#include "ooo_cpu.h"

#include <cmath>
#include <iostream>

#define Tag uint16_t
#define Index uint16_t
#define Path uint64_t
#define History uint64_t
#define TAGE_BIMODAL_TABLE_SIZE 16384
#define TAGE_MAX_INDEX_BITS 12
#define TAGE_NUM_COMPONENTS 12 // TODO
#define TAGE_BASE_COUNTER_BITS 2
#define TAGE_COUNTER_BITS 3
#define TAGE_USEFUL_BITS 2
//#define TAGE_GLOBAL_HISTORY_BUFFER_LENGTH 1024
#define TAGE_GLOBAL_HISTORY_BUFFER_LENGTH 640
#define TAGE_FOLDED_HISTORY_BUFFER_LENGTH 64

//#define TAGE_PATH_HISTORY_BUFFER_LENGTH 32
#define TAGE_PATH_HISTORY_BUFFER_LENGTH 64

#define TAGE_MIN_HISTORY_LENGTH 4
#define TAGE_HISTORY_ALPHA 1.6
#define TAGE_RESET_USEFUL_INTERVAL 512000

const uint8_t TAGE_INDEX_BITS[TAGE_NUM_COMPONENTS] = {10, 10, 11, 11, 11, 11, 10, 10, 10, 10, 9, 9};
const uint8_t TAGE_TAG_BITS[TAGE_NUM_COMPONENTS] = {7, 7, 8, 8, 9, 10, 11, 12, 12, 13, 14, 15};

struct tage_predictor_table_entry
{
    uint8_t ctr; // The counter on which prediction is based Range - 0-7
    Tag tag; // Stores the tag
    uint8_t useful; // Variable to store the usefulness of the entry Range - 0-3
//  int dump(int,int,bool filter,std::ostream &os=std::cout);
  int dump_final_tpt_entry(int,int,int,bool,std::ostream &os=std::cout);
  int dump_tpt_entry(int,int,int,bool,int64_t,std::ostream &os=std::cout);

};

class Tage
{
private:
    /* data */
    int num_branches; // Stores the number of branch instructions since the last useful reset
    uint8_t bimodal_table[TAGE_BIMODAL_TABLE_SIZE]; // Array represent the counters of the bimodal table
    struct tage_predictor_table_entry predictor_table[TAGE_NUM_COMPONENTS][(1 << TAGE_MAX_INDEX_BITS)];
    uint8_t global_history[TAGE_GLOBAL_HISTORY_BUFFER_LENGTH]; // Stores the global branch history
    uint8_t path_history[TAGE_PATH_HISTORY_BUFFER_LENGTH]; // Stores the last bits of the last N branch PCs
    uint8_t use_alt_on_na; // 4 bit counter to decide between alternate and provider component prediction
    int component_history_lengths[TAGE_NUM_COMPONENTS]; // History lengths used to compute hashes for different components
    uint8_t tage_pred, pred, alt_pred; // Final prediction , provider prediction, and alternate prediction
    int pred_comp, alt_comp; // Provider and alternate component of last branch PC
    int STRONG; //Strength of provider prediction counter of last branch PC

public:
    void init();  // initialise the member variables
    uint8_t predict(uint64_t ip);  // return the prediction from tage
    void update(uint64_t ip, uint8_t taken);  // updates the state of tage

    Index get_bimodal_index(uint64_t ip);   // helper hash function to index into the bimodal table
    Index get_predictor_index(uint64_t ip, int component);   // helper hash function to index into the predictor table using histories
    Tag get_tag(uint64_t ip, int component);   // helper hash function to get the tag of particular ip and component
    int get_match_below_n(uint64_t ip, int component);   // helper function to find the hit component strictly before the component argument
    void ctr_update(uint8_t &ctr, int cond, int low, int high);   // counter update helper function (including clipping)
    uint8_t get_prediction(uint64_t ip, int comp);   // helper function for prediction
    Path get_path_history_hash(int component);   // hepoer hash function to compress the path history
    History get_compressed_global_history(int inSize, int outSize); // Compress global history of last 'inSize' branches into 'outSize' by wrapping the history

  void dump(int,bool,bool,std::ostream &os=std::cout);
  void dump_history(int,bool,bool,std::ostream &os=std::cout);
  void dump_bimodal_table(bool,bool,std::ostream &os=std::cout);
  void dump_pred_tables(int,bool,bool,std::ostream &os=std::cout);
  void dump_comp_hist_length(std::ostream &os=std::cout);

    Tage();
    ~Tage();
};

//X void Tage::init()
//X {
//X     /*
//X     Initializes the member variables
//X     */
//X     use_alt_on_na = 8;
//X     tage_pred = 0;
//X     for (int i = 0; i < TAGE_BIMODAL_TABLE_SIZE; i++)
//X     {
//X         bimodal_table[i] = (1 << (TAGE_BASE_COUNTER_BITS - 1)); // weakly taken
//X     }
//X     for (int i = 0; i < TAGE_NUM_COMPONENTS; i++)
//X     {
//X         for (int j = 0; j < (1 << TAGE_INDEX_BITS[i]); j++)
//X         {
//X             predictor_table[i][j].ctr = (1 << (TAGE_COUNTER_BITS - 1)); // weakly taken
//X             predictor_table[i][j].useful = 0;                           // not useful
//X             predictor_table[i][j].tag = 0;
//X         }
//X     }
//X 
//X     double power = 1;
//X     for (int i = 0; i < TAGE_NUM_COMPONENTS; i++)
//X     {
//X         component_history_lengths[i] = int(TAGE_MIN_HISTORY_LENGTH * power + 0.5); // set component history lengths
//X         power *= TAGE_HISTORY_ALPHA;
//X     }
//X 
//X     num_branches = 0;
//X }
//X 
//X uint8_t Tage::get_prediction(uint64_t ip, int comp)
//X {
//X     /*
//X     Get the prediction according to a specific component 
//X     */
//X     if(comp == 0) // Check if component is the bimodal table
//X     {
//X         Index index = get_bimodal_index(ip); // Get bimodal index
//X         return bimodal_table[index] >= (1 << (TAGE_BASE_COUNTER_BITS - 1));
//X     }
//X     else
//X     {
//X         Index index = get_predictor_index(ip, comp); // Get component-specific index
//X         return predictor_table[comp - 1][index].ctr >= (1 << (TAGE_COUNTER_BITS - 1));
//X     }
//X }

//X uint8_t Tage::predict(uint64_t ip)
//X {
//X     pred_comp = get_match_below_n(ip, TAGE_NUM_COMPONENTS + 1); // Get the first predictor from the end which matches the PC
//X     alt_comp = get_match_below_n(ip, pred_comp); // Get the first predictor below the provider which matches the PC 
//X 
//X     //Store predictions for both components for use in the update step
//X     pred = get_prediction(ip, pred_comp); 
//X     alt_pred = get_prediction(ip, alt_comp);
//X 
//X     if(pred_comp == 0)
//X         tage_pred = pred;
//X     else
//X     {
//X         Index index = get_predictor_index(ip, pred_comp);
//X         STRONG = abs(2 * predictor_table[pred_comp - 1][index].ctr + 1 - (1 << TAGE_COUNTER_BITS)) > 1;
//X         if (use_alt_on_na < 8 || STRONG) // Use provider component only if USE_ALT_ON_NA < 8 or the provider counter is strong
//X             tage_pred = pred;
//X         else
//X             tage_pred = alt_pred;
//X     }
//X     return tage_pred;
//X }
//X 
//X void Tage::ctr_update(uint8_t &ctr, int cond, int low, int high)
//X {
//X     /*
//X     Function to update bounded counters according to some condition
//X     */
//X     if(cond && ctr < high)
//X         ctr++;
//X     else if(!cond && ctr > low)
//X         ctr--;
//X }

//X void Tage::update(uint64_t ip, uint8_t taken)
//X {
//X     /*
//X     function to update the state (member variables) of the tage class
//X     */
//X     if (pred_comp > 0)  // the predictor component is not the bimodal table
//X     {
//X         struct tage_predictor_table_entry *entry = &predictor_table[pred_comp - 1][get_predictor_index(ip, pred_comp)];
//X         uint8_t useful = entry->useful;
//X 
//X         if(!STRONG)
//X         {
//X             if (pred != alt_pred)
//X                 ctr_update(use_alt_on_na, !(pred == taken), 0, 15);
//X         }
//X 
//X         if(alt_comp > 0)  // alternate component is not the bimodal table
//X         {
//X             struct tage_predictor_table_entry *alt_entry = &predictor_table[alt_comp - 1][get_predictor_index(ip, alt_comp)];
//X             if(useful == 0)
//X                 ctr_update(alt_entry->ctr, taken, 0, ((1 << TAGE_COUNTER_BITS) - 1)); // update ctr for alternate predictor if useful for predictor is 0
//X         }
//X         else
//X         {
//X             Index index = get_bimodal_index(ip);
//X             if (useful == 0)
//X                 ctr_update(bimodal_table[index], taken, 0, ((1 << TAGE_BASE_COUNTER_BITS) - 1));  // update ctr for alternate predictor if useful for predictor is 0
//X         }
//X 
//X         // update u
//X         if (pred != alt_pred)
//X         {
//X             if (pred == taken)
//X             {
//X                 if (entry->useful < ((1 << TAGE_USEFUL_BITS) - 1))
//X                     entry->useful++;  // if prediction from preditor component was correct
//X             }
//X             else
//X             {
//X                 if(use_alt_on_na < 8)
//X                 {
//X                     if (entry->useful > 0)
//X                         entry->useful--;  // if prediction from altpred component was correct
//X                 } 
//X             }
//X         }
//X 
//X         ctr_update(entry->ctr, taken, 0, ((1 << TAGE_COUNTER_BITS) - 1));  // update ctr for predictor component
//X     }
//X     else
//X     {
//X         Index index = get_bimodal_index(ip);
//X         ctr_update(bimodal_table[index], taken, 0, ((1 << TAGE_BASE_COUNTER_BITS) - 1));  // update ctr for predictor if predictor is bimodal
//X     }
//X 
//X     // allocate tagged entries on misprediction
//X     if (tage_pred != taken)
//X     {
//X         long rand = random();
//X         rand = rand & ((1 << (TAGE_NUM_COMPONENTS - pred_comp - 1)) - 1);  
//X         int start_component = pred_comp + 1;
//X 
//X         //compute the start-component for search
//X         if (rand & 1)  // 0.5 probability
//X         {
//X             start_component++;
//X             if (rand & 2)  // 0.25 probability
//X                 start_component++;
//X         }
//X 
//X         //Allocate atleast one entry if no free entry
//X         int isFree = 0;
//X         for (int i = pred_comp + 1; i <= TAGE_NUM_COMPONENTS; i++)
//X         {
//X             struct tage_predictor_table_entry *entry_new = &predictor_table[i - 1][get_predictor_index(ip, i)];
//X             if (entry_new->useful == 0)
//X                 isFree = 1;
//X         }
//X         if (!isFree && start_component <= TAGE_NUM_COMPONENTS)
//X             predictor_table[start_component - 1][get_predictor_index(ip, start_component)].useful = 0;
//X         
//X         
//X         // search for entry to steal from the start-component till end
//X         for (int i = start_component; i <= TAGE_NUM_COMPONENTS; i++)
//X         {
//X             struct tage_predictor_table_entry *entry_new = &predictor_table[i - 1][get_predictor_index(ip, i)];
//X             if (entry_new->useful == 0)
//X             {
//X                 entry_new->tag = get_tag(ip, i);
//X                 entry_new->ctr = (1 << (TAGE_COUNTER_BITS - 1));
//X                 break;
//X             }
//X         }
//X     }
//X 
//X     // update global history
//X     for (int i = TAGE_GLOBAL_HISTORY_BUFFER_LENGTH - 1; i > 0; i--)
//X         global_history[i] = global_history[i - 1];
//X     global_history[0] = taken;
//X 
//X     // update path history
//X     for (int i = TAGE_PATH_HISTORY_BUFFER_LENGTH - 1; i > 0; i--)
//X         path_history[i] = path_history[i - 1];
//X     path_history[0] = ip & 1;
//X     
//X     // graceful resetting of useful counter
//X     num_branches++;
//X     if (num_branches % TAGE_RESET_USEFUL_INTERVAL == 0)
//X     {
//X         num_branches = 0;
//X         for (int i = 0; i < TAGE_NUM_COMPONENTS; i++)
//X         {
//X             for (int j = 0; j < (1 << TAGE_INDEX_BITS[i]); j++)
//X                 predictor_table[i][j].useful >>= 1;
//X         }
//X     }
//X }

//X Index Tage::get_bimodal_index(uint64_t ip)
//X {
//X     /*
//X     Return index of the PC in the bimodal table using the last K bits
//X     */
//X     return ip & (TAGE_BIMODAL_TABLE_SIZE - 1);
//X }
//X 
//X Path Tage::get_path_history_hash(int component)
//X {
//X     /*
//X     Use a hash-function to compress the path history
//X     */
//X     Path A = 0;
//X     
//X     int size = component_history_lengths[component - 1] > 16 ? 16 : component_history_lengths[component-1]; // Size of hash output
//X     for (int i = TAGE_PATH_HISTORY_BUFFER_LENGTH - 1; i >= 0; i--)
//X     {
//X         A = (A << 1) | path_history[i]; // Build the bit vector a using the path history array
//X     }
//X 
//X     A = A & ((1 << size) - 1);
//X     Path A1;
//X     Path A2;
//X     A1 = A & ((1 << TAGE_INDEX_BITS[component - 1]) - 1); // Get last M bits of A
//X     A2 = A >> TAGE_INDEX_BITS[component - 1]; // Get second last M bits of A
//X 
//X     // Use the hashing from the CBP-4 L-Tage submission
//X     A2 = ((A2 << component) & ((1 << TAGE_INDEX_BITS[component - 1]) - 1)) + (A2 >> abs(TAGE_INDEX_BITS[component - 1] - component));
//X     A = A1 ^ A2;
//X     A = ((A << component) & ((1 << TAGE_INDEX_BITS[component - 1]) - 1)) + (A >> abs(TAGE_INDEX_BITS[component - 1] - component));
//X     
//X     return (A);
//X }
//X 
//X History Tage::get_compressed_global_history(int inSize, int outSize)
//X {
//X     /*
//X     Compress global history of last 'inSize' branches into 'outSize' by wrapping the history
//X     */
//X     History compressed_history = 0; // Stores final compressed history
//X     History temporary_history = 0; // Temorarily stores some bits of history
//X     int compressed_history_length = outSize;
//X     for (int i = 0; i < inSize; i++)
//X     {
//X         if (i % compressed_history_length == 0)
//X         {
//X             compressed_history ^= temporary_history; // XOR current segment into the compressed history
//X             temporary_history = 0;
//X         }
//X         temporary_history = (temporary_history << 1) | global_history[i]; // Build history bit vector
//X     }
//X     compressed_history ^= temporary_history;
//X     return compressed_history;
//X }

//X Index Tage::get_predictor_index(uint64_t ip, int component)
//X {
//X     /*
//X     Get index of PC in a particular predictor component
//X     */
//X     Path path_history_hash = get_path_history_hash(component); // Hash of path history
//X 
//X     // Hash of global history
//X     History global_history_hash = get_compressed_global_history(component_history_lengths[component - 1], TAGE_INDEX_BITS[component - 1]);
//X 
//X     return (global_history_hash ^ ip ^ (ip >> (abs(TAGE_INDEX_BITS[component - 1] - component) + 1)) ^ path_history_hash) & ((1 << TAGE_INDEX_BITS[component-1]) - 1);
//X }
//X 
//X Tag Tage::get_tag(uint64_t ip, int component)
//X {
//X     /*
//X     Get tag of a PC for a particular predictor component
//X     */
//X     History global_history_hash = get_compressed_global_history(component_history_lengths[component - 1], TAGE_TAG_BITS[component - 1]);
//X     global_history_hash ^= get_compressed_global_history(component_history_lengths[component - 1], TAGE_TAG_BITS[component - 1] - 1);
//X     
//X     return (global_history_hash ^ ip) & ((1 << TAGE_TAG_BITS[component - 1]) - 1);
//X }

//X int Tage::get_match_below_n(uint64_t ip, int component)
//X {
//X     /*
//X     Get component number of first predictor which has an entry for the IP below a specfic component number
//X     */
//X     for (int i = component - 1; i >= 1; i--)
//X     {
//X         Index index = get_predictor_index(ip, i);
//X         Tag tag = get_tag(ip, i);
//X 
//X         if (predictor_table[i - 1][index].tag == tag) // Compare tags at a specific index
//X         {
//X             return i;
//X         }
//X     }
//X 
//X     return 0; // Default to bimodal in case no match found
//X }
//X 
//X Tage::Tage()
//X {
//X }
//X 
//X Tage::~Tage()
//X {
//X }

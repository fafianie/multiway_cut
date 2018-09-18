#include <string>
#include <random>

class Galois
{
  public:
    std::mt19937 gen; //protected
    int w; //protected
    int mode; //dropped
    uint64_t add(uint64_t, uint64_t); //shared
    uint64_t multiply(uint64_t, uint64_t); //abstract
    uint64_t naive_multiply(uint64_t, uint64_t);
    uint64_t table_multiply(uint64_t, uint64_t);
    uint64_t logtb_multiply(uint64_t, uint64_t);
    uint64_t clmul_multiply(uint64_t, uint64_t);
    uint64_t divide(uint64_t, uint64_t); //abstract
    uint64_t naive_divide(uint64_t, uint64_t); 
    uint64_t table_divide(uint64_t, uint64_t);
    uint64_t logtb_divide(uint64_t, uint64_t);
    uint64_t clmul_divide(uint64_t, uint64_t);
    uint64_t inverse(uint64_t); //shared method
    uint64_t log(uint64_t); //shared
    uint64_t ilog(uint64_t); //shared
    uint64_t uniform_random_element(); //shared method
    void seed(); //call from constructor

    void set_mode_naive(); //replaced by constructors
    void set_mode_table();
    void set_mode_logtb();
    void set_mode_pcmul();
    void create_table();
    void create_logtb(); //replaced by constructors
    void set_w(int); //replaced by constructors
    std::string to_string(uint64_t); //shared method

    static const int NAIVE = 0; //dropped
    static const int TABLE = 1;
    static const int LOGTB = 2;
    static const int CLMUL = 3;

    uint64_t** m_table; //private for implementations
    uint64_t** d_table;
    uint64_t*  logtb;
    uint64_t*  ilogtb;
};
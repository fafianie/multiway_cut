#include <iostream>
#include <string>
#include <bitset>
//#include <wmmintrin.h>
#include <stdio.h>
#include <cstdint>
#include <chrono>
#include <cstring>

#include "reader.h"
#include "tutte.h"
#include "preprocessor.h"
#include "compression.h"
#include "static.cpp"

using namespace std;
using namespace std::chrono;

void cpuid(unsigned info, unsigned *eax, unsigned *ebx, unsigned *ecx, unsigned *edx)
{
    __asm__(
        "cpuid;"                                            /* assembly code */
        :"=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx) /* outputs */
        :"a" (info)                                         /* input: info into eax */
                                                            /* clobbers: none */
    );
}

void pcmulsup()
{
  cout << endl << "  CPUID TEST" << endl << endl;

  unsigned int eax, ebx, ecx, edx;
  int i;

  bool sup;
 
  for (i = 0; i < 6; ++i)
  {
    cpuid(i, &eax, &ebx, &ecx, &edx);
    printf("eax=%i: %#010x %#010x %#010x %#010x\n", i, eax, ebx, ecx, edx);
    if (i == 1) sup = ecx & pw[1];
  }

  cout << endl << "  PCLMULQDQ SUPPORT: ";
  if (sup) cout << "YES";
  else cout << "NO";
  cout << endl;

}

void statics()
{
  cout << endl << "  STATICS" << endl << endl;

  Galois g;
  g.set_w(64);
  for (int i = 0; i < 65; i++)
  {
   cout << "primpoly[" << i << "]";
   if (i < 10) cout << " ";
   cout << " = " << g.to_string(primpoly[i]) << endl; 
  }
  cout << endl;
  for (int i = 0; i < 65; i++)
  {
    cout << "pw[" << i << "]";
    if (i < 10) cout << " ";
    cout <<  " = " << g.to_string(pw[i]) << endl;
  }
  cout << endl;
  for (int i = 0; i < 65; i++)
  {
    cout << "pwm1[" << i << "]";
    if (i < 10) cout << " ";
    cout << " = " << g.to_string(pwm1[i]) << endl;
  }
  cout << endl;
}

void pcmul_test(int count)
{
  cout << endl << "  PCLMUL test\n";

  Galois g;
  g.set_w(64);
  g.seed();

  uint64_t* arg1 = new uint64_t[count];
  uint64_t* arg2 = new uint64_t[count];
  uint64_t* nmul = new uint64_t[count];
  uint64_t* cmul = new uint64_t[count];
  uint64_t* ndiv = new uint64_t[count];
  uint64_t* cdiv = new uint64_t[count];

  cout << endl;

  for (int i = 0; i < count; i++)
  {
    cout << "  SEEDING " << i; 
    arg1[i] = g.uniform_random_element();
    arg2[i] = g.uniform_random_element();
    cout << "\r";
  }
  cout << "  SEEDING DONE          " << endl;
 
  g.set_mode_naive();
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  for (int i = 0; i < count; i++)
  {
    cout << "  N_MUL " << i;
    nmul[i] = g.multiply(arg1[i], arg2[i]);
    cout << "\r";
  }
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  cout << "  N_MUL DONE IN TIME: " << duration << "                             " << endl;
 
  g.set_mode_pcmul();
  high_resolution_clock::time_point t3 = high_resolution_clock::now();
  for (int i = 0; i < count; i++)
  {
    cout << "  C_MUL " << i;
    cmul[i] = g.multiply(arg1[i], arg2[i]);
    cout << "\r";
  }
  high_resolution_clock::time_point t4 = high_resolution_clock::now();
  auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>( t4 - t3 ).count();
  cout << "  C_MUL DONE IN TIME: " << duration2 << "                             " << endl;

  g.set_mode_naive();
  high_resolution_clock::time_point t5 = high_resolution_clock::now();
  for (int i = 0; i < count; i++)
  {
    cout << "  N_DIV " << i;
    ndiv[i] = g.divide(arg1[i], arg2[i]);
    cout << "\r";
  }
  high_resolution_clock::time_point t6 = high_resolution_clock::now();
  auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>( t6 - t5 ).count();
  cout << "  N_DIV DONE IN TIME: " << duration3 << "                             " << endl;

  g.set_mode_pcmul();
  high_resolution_clock::time_point t7 = high_resolution_clock::now();
  for (int i = 0; i < count; i++)
  {
    cout << "  C_DIV " << i;
    cdiv[i] = g.divide(arg1[i], arg2[i]);
    cout << "\r";
  }
  high_resolution_clock::time_point t8 = high_resolution_clock::now();
  auto duration4 = std::chrono::duration_cast<std::chrono::microseconds>( t8 - t7 ).count();
  cout << "  C_DIV DONE IN TIME: " << duration4 << "                             " << endl << endl;

  int mfaults = 0;
  int dfaults = 0;
  for (int i = 0; i < count ; i++)
  {
    cout << "  CHECK FOR FAULT IN " << i;
    if (nmul[i] != cmul[i]) mfaults++;
    if (ndiv[i] != cdiv[i]) dfaults++;
    cout << "\r";   
  }
  cout << "  MUL FAULTS: " << mfaults << "                 " << endl;
  cout << "  DIV FAULTS: " << dfaults << "                 " << endl << endl;
}

uint64_t evaluate(Tutte t, Galois g, int nodes, int terminals)
{
  uint64_t result = 0;
  uint64_t **p6;
  Gauss gs;

  for (int i = 0; i < pw[terminals-1]; i++)
  { 
    cout << "\r" << "  PROCESSING ORIENTATION: " << (i+1) << " / " << (1 << (terminals-1)) << "    ";
    p6 = t.orientation(i);
    result = g.add(result, gs.determinant(g, nodes, p6));
  }
  cout << "\r";
  return result;
}

uint64_t compress_eval(Tutte t, Galois g, int nodes, int terminals)
{
  uint64_t result = 0;
  uint64_t **p6;
  Gauss gs;

  Compression comp;
  comp.initiate(g, nodes, terminals, t.matrix);
  comp.compress(g);

  for (int i = 0; i < pw[terminals-1]; i++)
  {
    cout << "\r" << "  PROCESSING ORIENTATION: " << (i+1) << " / " << (1 << (terminals-1)) << "    ";
    p6 = comp.orientation(g,  i);
    result = g.add(result, gs.determinant(g, terminals*3, p6));
  }
  cout << "\r";
  return result;
}

uint64_t est_eval(Galois g, int nodes, int terminals, int** adjacency, int time)
{
  Tutte t;
  t.initiate(nodes, terminals, g.w, adjacency);
  
  uint64_t result = 0;
  uint64_t **p6;
  Gauss gs;

  int i = 0;
  auto duration = 0;
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  high_resolution_clock::time_point t2;
  
  while ((duration < time) && (i < pw[terminals-1]))
  {
    cout << "\r" << "  PROCESSING ORIENTATION: " << (i+1) << " / " << (1 << (terminals-1)) << "    ";
    p6 = t.orientation(i);
    result = g.add(result, gs.determinant(g, nodes, p6));   
    i++;
    t2 = high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout << "\r";
  }
  cout << "                                                                              " << "\r";
  if (duration < time)
  {
    cout << "  EVALUATION DONE IN TIME: " << duration << endl; 
  }
  else
  {
    cout << "  EVALUATION UP TO : " << (i+1) << " / " << pw[terminals-1];
    uint64_t step_time = duration/(i+1);
    uint64_t eta = step_time * pw[terminals-1];
    cout << "  ETA: " << eta << endl;
  }
  return result;
}

uint64_t est_comp_eval(Galois g, int nodes, int terminals, int** adjacency, int time)
{
  Tutte t;
  t.initiate(nodes, terminals, g.w, adjacency);

  uint64_t result = 0;
  uint64_t **p6;
  Gauss gs;

  int i = 0;
  auto duration = 0;
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  high_resolution_clock::time_point t2;

  Compression comp;
  comp.initiate(g, nodes, terminals, t.matrix);
  comp.compress(g);
  
  t2 = high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

  if (duration < time)
  { 
    auto duration2 = 0;
    high_resolution_clock::time_point t3;
    while (((duration+duration2) < time) && (i < pw[terminals-1]))
    {
      cout << "\r" << "  PROCESSING ORIENTATION: " << (i+1) << " / " << (1 << (terminals-1)) << "    ";
      p6 = comp.orientation(g, i);
      result = g.add(result, gs.determinant(g, terminals*3, p6));   
      i++;
      t3 = high_resolution_clock::now();
      duration2 = std::chrono::duration_cast<std::chrono::microseconds>( t3 - t2 ).count();
      cout << "\r";
    }
    cout << "                                                                              " << "\r";
    if ((duration+duration2) < time)
    {
      cout << "  COMP + EVALUATION DONE IN TIME: " << duration << endl; 
    }
    else
    {
      cout << "  COMP + EVALUATION UP TO : " << (i+1) << " / " << pw[terminals-1];
      uint64_t step_time = duration2/(i+1);
      uint64_t eta = duration+(step_time * pw[terminals-1]);
      cout << "  ETA: " << eta << endl;
    } 
  }
  else 
  { 
    cout << "  COMPRESSION IN TIME: " << duration << endl;
  }
  return result;
}

void test_equiv(Galois g, Galois gn, Galois gt, Galois gl, int count, int nodes, int terminals, int w, int** adjacency)
{
  Tutte t;
 
  int df = 0;
  for (int i = 0; i < count; i++)
  {
    cout << "i: " << i << endl;
 
    t.initiate(nodes, terminals, w, adjacency);

    uint64_t ne = evaluate(t, gn, nodes, terminals);
    uint64_t nc = compress_eval(t, gn, nodes, terminals);
    uint64_t te = evaluate(t, gt, nodes, terminals);
    uint64_t tc = compress_eval(t, gt, nodes, terminals);
    uint64_t le = evaluate(t, gl, nodes, terminals);
    uint64_t lc = compress_eval(t, gl, nodes, terminals);
    cout << "n" << ": eval= " << g.to_string(ne) << " comp= " << g.to_string(nc) << endl;
    cout << "t" << ": eval= " << g.to_string(te) << " comp= " << g.to_string(tc) << endl;
    cout << "l" << ": eval= " << g.to_string(le) << " comp= " << g.to_string(lc) << endl;

    
    if ((ne != nc) || (te != tc) || (le != lc))
    {
      cout << " found diff" << endl;
      df++;
     // i += 10000;
    }
   }
   cout << endl << "  DIFF: " << df << endl << endl;
}

Preprocessor initiate(string path)
{
  Reader r;
  r.read(path);

  int **p = r.adjacency;
  int nodes = r.nodes;
  int edges = r.edges;
  int terminals = r.terminals;
  vector<int> termlist = r.termlist;

  cout << "  " << path << " N: " << nodes << " E: " << edges << " T: " << terminals << endl;

  Preprocessor pre;
  pre.nodes = nodes;
  pre.terminals = terminals;
  pre.termlist = termlist;
  pre.adjacency = p;
  pre.reorder();
  pre.subdivide();
  pre.split();
  pre.addloops();

  return pre;
}

uint64_t est_eval_instance(string path, Galois g, int time)
{
  Preprocessor pre = initiate(path);
  return est_eval(g, pre.nodes, pre.terminals, pre.adjacency, time);
  cout << endl;
}

uint64_t est_comp_eval_instance(string path, Galois g, int time)
{
  Preprocessor pre = initiate(path);
  return est_comp_eval(g, pre.nodes, pre.terminals, pre.adjacency, time);
  cout << endl;
}

int main()
{
  pcmulsup();
  //pcmul_test(10000);

  //statics();

  //SETTINGS
  /*int w = 4;
  Galois g;
  g.set_w(w);
  g.seed();
  g.set_mode_table();*/
 /*
  //READ FILE
  Reader r;
  r.read("../instances/rand200.dgf");
  //r.read("../instances/twoxantiwheel5.dgf");
  //r.read("../instances/big.dgf");

  int **p = r.adjacency;
  int nodes = r.nodes;
  int edges = r.edges;
  int terminals = r.terminals;
  vector<int> termlist = r.termlist;

  cout << "  INSTANCE: " << endl;
  cout << "  NODES: " << nodes << endl;
  cout << "  EDGES: " << edges << endl;
  cout << "  TERMS: " << terminals << endl;
  
  //PREPROCESSING
  Preprocessor pre;
  pre.nodes = nodes;
  pre.terminals = terminals;
  pre.termlist = termlist;
  pre.adjacency = p;

  int **p2 = pre.reorder();
  int **p3 = pre.subdivide();
  int **p4 = pre.split();
  int **p5 = pre.addloops();*/

  int w = 12;
  Galois g, gn, gt, gl;
  g.set_w(w);
  gn.set_w(w);
  gt.set_w(w);
  gl.set_w(w);
  gn.seed();
  gt.seed();
  gl.seed();
  //gn.set_mode_naive();
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  gt.set_mode_table();
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  cout << "  TABLE CREATED IN TIME: " << duration << endl;
  //gl.set_mode_logtb();
  //g.set_mode_pcmul();
  //cout << endl << "  RESULT: " << est_eval_instance("../instances/cluster.dgf", g, 600000000) << endl; 
  //test_equiv(g, gn, gt, gl, 1, pre.nodes, pre.terminals, 4, pre.adjacency);

  //est_eval(gt, pre.nodes, pre.terminals, pre.adjacency, 600000000);
  /*est_eval_instance("../instances/rand100.dgf", g, 600000000);
  est_eval_instance("../instances/rand200.dgf", g, 600000000);
  est_eval_instance("../instances/rand300.dgf", g, 600000000);
  est_eval_instance("../instances/rand400.dgf", g, 600000000);
  est_eval_instance("../instances/rand500.dgf", g, 600000000);
  est_eval_instance("../instances/rand600.dgf", g, 600000000);
  est_eval_instance("../instances/rand700.dgf", g, 600000000);
  est_eval_instance("../instances/rand800.dgf", g, 600000000);
  est_eval_instance("../instances/rand900.dgf", g, 600000000);
  est_eval_instance("../instances/rand1000.dgf", g, 600000000); 
  est_comp_eval_instance("../instances/rand100.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand200.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand300.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand400.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand500.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand600.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand700.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand800.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand900.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand1000.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand1100.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand1200.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand1300.dgf", g, 600000000);*/
 /* est_comp_eval_instance("../instances/rand1400.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand1500.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand1600.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand1700.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand1800.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand1900.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand2000.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand2100.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand2200.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand2300.dgf", g, 600000000);
  est_comp_eval_instance("../instances/rand2400.dgf", g, 600000000);*/

  /*//INITIALIZE TUTTE MATRIX
  Tutte t;
  t.initiate(pre.nodes, pre.terminals, w, pre.adjacency);

  uint64_t ne = evaluate(t, gt, pre.nodes, pre.terminals);

  cout << " WTF" << endl;

  uint64_t result = 0;
  uint64_t **p6;
  Gauss gs;

  for (int i = 0; i < pw[pre.terminals-1]; i++)
  { 
    cout << "\r" << "  PROCESSING ORIENTATION: " << (i+1) << " / " << (1 << (pre.terminals-1)) << "    ";
    p6 = t.orientation(i);
    result = gt.add(result, gs.determinant(gt, pre.nodes, p6));
  }
  cout << "\r";
  
/*
  //NORMAL NAIVE EVALUATION
  high_resolution_clock::time_point t1 = high_resolution_clock::now(); 
  uint64_t result = evaluate(t, g, pre.nodes, pre.terminals);
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

  //NAIVE COMPRESSION + EVALUATION
  high_resolution_clock::time_point t3 = high_resolution_clock::now();
  uint64_t result2 = compress_eval(t, g, pre.nodes, pre.terminals);
  high_resolution_clock::time_point t4 = high_resolution_clock::now();
  auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>( t4 - t3 ).count();
*/
 // g.set_mode_pcmul();
/*
  //NORMAL PCMUL EVALUATION
  high_resolution_clock::time_point t5 = high_resolution_clock::now(); 
  uint64_t result3 = evaluate(t, g, pre.nodes, pre.terminals);
  high_resolution_clock::time_point t6 = high_resolution_clock::now();
  auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>( t6 - t5 ).count();

  //PCMUL COMPRESSION + EVALUATION
  high_resolution_clock::time_point t7 = high_resolution_clock::now();
  uint64_t result4 = compress_eval(t, g, pre.nodes, pre.terminals);
  high_resolution_clock::time_point t8 = high_resolution_clock::now();
  auto duration4 = std::chrono::duration_cast<std::chrono::microseconds>( t8 - t7 ).count();

  //RESULT
  //cout << "         NAIVE EVAL TIME: " << duration << "           " << endl;
  //cout << "    NAIVE COMP+EVAL TIME: " << duration2 << endl;
  cout << "         PCMUL EVAL TIME: " << duration3 << endl;
  cout << "    PCMUL COMP+EVAL TIME: " << duration4 << endl << endl; 
  //cout << "       NAIVE EVAL RESULT: " << g.to_string(result) << endl;
  //cout << "  NAIVE COMP+EVAL RESULT: " << g.to_string(result2) << endl;
  cout << "       PCMUL EVAL RESULT: " << g.to_string(result3) << endl;
  cout << "  PCMUL COMP+EVAL RESULT: " << g.to_string(result4) << endl << endl;

 /**//*
  
  cout << "comp " << endl;
 
  uint64_t result = 0;
  uint64_t **p6;
  Gauss gs;

  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  for (int i = 0; i < pw[terminals-1]; i++)
  {
    cout << "\r" << "  PROCESSING ORIENTATION: " << (i+1) << " / " << (1 << (terminals-1)) << "    ";
    p6 = t.orientation(i);
    result = g.add(result, gs.determinant(g, pre.nodes, p6));
  }
  cout << "\r";
  high_resolution_clock::time_point t3 = high_resolution_clock::now();
  auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>( t3 - t2 ).count();
  
  cout << "  DONE                                                                             " << "\r";
  cout << "  PCMUL  EVALUATION TIME: " << duration2 << endl;
  cout << "                          " << 600000000 << endl << endl;

  /**/
 // random_instance(2100, 50000, 12, "../instances/rand3000sparse.dgf");
  
  /*
  InstanceGen ig;

 // ig.no_disjoint_instance(100, 2000, 8);
 // ig.no_spider_instance(50, 270, 10, 4);
  ig.random_connected_instance(250, 5000, 21);

  Writer wr;

  wr.write("../instances/rand.dgf", "random", "random instance", ig.nodes, ig.edges, ig.terminals, ig.termlist, ig.adjacency);

  //TODO: return a connected instance*/

  return 0;
}





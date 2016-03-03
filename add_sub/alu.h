#ifndef ALU
#define ALU

#include <systemc.h>

#include <iostream>
using namespace std;


SC_MODULE(alu) {
    sc_in<bool> clk;
    sc_in<sc_uint<16> > ain, bin;
    sc_in<bool> ci;
    sc_in<sc_unit<4>> control;
    sc_in<sc_uint<16> > sum;
    sc_in<bool> co;
    sc_uint<16> sum_add,sum_sub,sum_xor,sum_or,sum_nota,sum_stl;
    bool zflag,oflag,lflag;


    void ADD() {
      add_sub adder("add_sub");
      adder.ain(ain);
      adder.bin(bin);
      adder.ci(ci);
      adder.as(false);
      adder.sum(sum_add);
      adder.co(co);
      adder.zflag(zflag);
      adder.oflag(oflag);
      adder.lflag(lflag);

    }

    void SUB() {
      add_sub adder("add_sub");
      adder.ain(ain);
      adder.bin(bin);
      adder.ci(ci);
      adder.as(true);
      adder.sum(sum_sub);
      adder.co(co);
      adder.zflag(zflag);
      adder.oflag(oflag);
      adder.lflag(lflag);
    }
    return XOR(sc_unit<16> ain, sc_unit<16> bin) {
       return ain ^ bin ;
    }

    void AND(/* arguments */) {
      /* code */
      sum_add = ain & bin ;
    }
    void OR(/* arguments */) {
      /* code */
      sum_or = ain | bin ;
    }
    void NOTA(/* arguments */) {
      /* code */
    sum_nota = ~ain ;
    }
    void STL(/* arguments */) {
      /* code */
      add_sub adder("add_sub");
      adder.ain(ain);
      adder.bin(bin);
      adder.ci(ci);
      adder.as(false);
      adder.sum(sum_add);
      adder.co(co);
      adder.zflag(zflag);
      adder.oflag(oflag);
      adder.lflag(lflag);
      sum_stl[0] = oflag ;

    }

    void run(/* arguments */) {
      sum_xor = XOR(ain,bin);
      ADD();
      SUB();
      OR();
      AND();
      STL();
      NOTA();
      if(control.read()[0]){
        sum=sum_or;
      }
    }

    SC_CTOR(add_sub) {
      SC_METHOD(run);
      sensitive << ain << bin << ci << as;
    }



};


#endif

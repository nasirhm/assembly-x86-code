#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

//two mem structs one of them being CPU and 
//3 levels of cache and a main;

//load instructions will load memory addresses into register
// mem structure:
 // A single CPU reg
 // a !kb level i cache 
    //--> it has 1 set 4 lines
    //256 bytes per line takes 1 cycle to get in

// level-2 , 64KB, 64 lines with each line having 1K bytes.
//takes 10 cycles.

//1MB lev - 3 cache, 1 set 256 lines 4k bytes, this has 100 cycles.

//if lev 3 is executed lev-2 and lev-1 need not be considered.

// wors case yougo on main whihc takes 1000 cycles.

//lines and loading;-

  // if there is a hit the age on the line gets reset
  //if no hit then a whole line of memry gets pulled and replaces the 
  //empty space or the least recently used line. 

  //each line needs to store start nd end addrres.
  //newly loaded lines are age set 0
  // every cache access hit or miss raises age of all of them

  // plan 2 classes with name line and class
  // line class will have being address, 
  //end address.
  //line size,
  //age
  //and cycle

// cache will have
// line vector with size of lines

//check if address is in a line



//we might also include the load function here
// load will pull an address and store its begining and last
//if no hit
// if there is a hit just decrease the hit age to zero
// depending upon where we hit increase the cycle.

// if there is a miss then load the address on either an empty space 
// or LRU

class Cache{
	struct Line{
		uint64_t tag;
		bool in_range;
		int recen_use;

		Line(): tag(0), in_range(false), recen_use(0) {}
	};

	vector <Line> lines;
	int line_size;
	int cycle;
	int line_amt;

	int getTaggie(uint64_t address)
	{
		return address/line_size;
	}

	public:

	Cache(int line_amount, int line_sz, int ind_cycles)
	: lines(line_amount), line_size(line_sz), cycle(ind_cycles), line_amt(line_amount) {}

bool hit(uint64_t address, int& cycles, int counter)
{
	uint64_t  taggie = getTaggie(address);
	int recent = 0;
	int time = lines[0].recen_use;

	for(int i = 0; i < line_amt; ++i)
	{
		if(lines[i].in_range && lines[i].tag == taggie)
		{
			lines[i].recen_use = counter;
			cycles += cycle;
			return true;
		}
		if(lines[i].recen_use < time)
		{
			time = lines[i].recen_use;
			recent = i;
		}
	}


      lines[recent].tag = taggie;
      lines[recent].in_range = true;
      lines[recent].recen_use = counter;
      cycles += cycle;
      return false;

}





};




class Systemarch{

Cache l1, l2, l3;
uint64_t cpu_regx;
int tot_cycles;
int counter;

public:

  Systemarch(): l1(4, 256, 1), l2(64, 1024, 10), l3(256, 4096, 100), tot_cycles(0), counter(0) {}


  void load(uint64_t address)
  {
  	counter++;
  	if(!l1.hit(address, tot_cycles, counter))
  	
  		if(!l2.hit(address, tot_cycles, counter))
  		
  			if(!l3.hit(address, tot_cycles, counter))
  	           tot_cycles += 1000;

  	cpu_regx = address;	
  	
  }

void print_Cycles() const {
	cout << "tot cycles = "<< tot_cycles << endl;
}



	
};

int main()
{
	Systemarch cpu;
	vector <uint64_t> address = {
		0x1000, 0x1024, 0x1599, 0x100, 0x10245, 0x10246, 0x10247,
		0x10247, 0x1600, 0x1601, 0x1700};

	for (auto add: address){
		cpu.load(add);
	}	

	cpu.print_Cycles();

	return 0;
	
}

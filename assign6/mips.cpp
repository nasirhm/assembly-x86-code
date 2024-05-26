#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <iomanip>

using namespace std; 
enum Type{
	r_ins,
	i_ins,
	j_ins,
};
struct Ins{
	Type type;
	uint32_t op;
	uint32_t rs;
	uint32_t rt;
	uint32_t rd;
	int16_t immdt;
	uint32_t add;
};

void decode(uint32_t ins, Ins &decd)
{
	decd.op = (ins >> 26) & 0x3F;
	if(decd.op == 0 )
	{
		decd.type = r_ins;
		decd.rs = (ins >> 21) & 0x1F;
		decd.rt = (ins >> 16) & 0x1F;
		decd.rd = (ins >> 11) & 0x1F;
	}
	else if(decd.op == 2 || decd.op == 3)
	{
		decd.type = j_ins;
		decd.add = ins & 0x3FFFFFF;
	}
	else
	{
		decd.type = i_ins;
		decd.rs = (ins >> 21) & 0x1F;
		decd.rt = (ins >> 16) & 0x1F;
		decd.immdt = ins & 0xFFFF;
	}
}


void prnt_ins(const Ins &truction)
{
	switch(truction.type)
	{
		case r_ins:
		cout << "R| code" << truction.op
		<<", rs:" << truction.rs << ", rt:"<< truction.rt
		<<", rd:"<<truction.rd << endl;
		break;

		case i_ins:
		cout<< "I | code: "<< truction.op
		<<", rs:"<< truction.rs << ", rt:"
		<< truction.rt << "immidiate: " << truction.immdt << endl;
		break;

		case j_ins:
		cout << "J | op: " << truction.op
		<< ", add:" << truction.add << endl;
		break;
	}
}


int main()
{
	ifstream input("mips-test.bin", ios::binary);
	if(!input.is_open())
	{
		cerr << "Error opening new" << endl;
		return 1;
	}

	vector <uint32_t> instructions;
	while(!input.eof())
	{
		uint32_t instruction = 0;
		input.read(reinterpret_cast<char *>(&instruction),
		sizeof(instruction));
		if(input.gcount() == sizeof(instruction))
		{
			instruction = ((instruction >> 24) & 0x000000FF) |
			              ((instruction >> 8) & 0x0000FF00) |
			              ((instruction >> 8) & 0x00FF0000) |
			              ((instruction << 24) & 0xFF000000);
			              instructions.push_back(instruction);
		}
	}

	input.close();

	for(const auto &instruction : instructions)
	{
         Ins decoded;
         decode(instruction, decoded);
         prnt_ins(decoded);		
	}

	return 0;
}

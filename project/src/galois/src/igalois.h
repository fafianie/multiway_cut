#include "stdafx.h"

class IGalois 
{
	public:
		IGalois(); //also deal with destructor abstractly
		uint64_t add(uint64_t, uint64_t);
		virtual uint64_t multiply(uint64_t, uint64_t);
		virtual uint64_t divide(uint64_t, uint64_t);
		uint64_t inverse(uint64_t); 
		uint64_t log(uint64_t); //shared or local?
		uint64_t ilog(uint64_t); //shared or local?
		uint64_t uniform_random_element();
		std::string to_string(uint64_t);
		
	protected:
		std::mt19937 gen;
		int w;

}
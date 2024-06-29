#ifndef BINARY_HASH_LARGER_HPP	
#define BINARY_HASH_LARGER_HPP

#include <vector>

static inline unsigned BITNUM = 8 * sizeof(unsigned);

class Binary_Hash_Larger
{
private:
	static inline unsigned max_section = 0;
	
	unsigned section;
	std::vector<unsigned> group;

public:
	Binary_Hash_Larger();
	Binary_Hash_Larger(const Binary_Hash_Larger& binhash);
	Binary_Hash_Larger(void* value);

	void insert(void* value);
	void erase(void* value);
	void reserve(std::size_t size);
	bool contains(void* value);
	void clear();
	std::size_t size();
};


Binary_Hash_Larger::Binary_Hash_Larger()
{
	this->section = 0;
	this->group = std::vector<unsigned>(1, 0);
}

Binary_Hash_Larger::Binary_Hash_Larger(const Binary_Hash_Larger& binhash)
{
	this->section = binhash.section;
	this->group = binhash.group;
}

Binary_Hash_Larger::Binary_Hash_Larger(void* value)
{
	if (this->max_section < *(unsigned*)value / BITNUM)
	{
		this->max_section = *(unsigned*)value / BITNUM;
	}
	
	this->section = *(unsigned*)value / BITNUM;
	this->group = std::vector<unsigned>(1, 0);
	this->group[0] |= (1 << *(unsigned*)value % BITNUM);
}

void Binary_Hash_Larger::insert(void* value)
{
	if (this->max_section < *(unsigned*)value / BITNUM)
	{
		this->max_section = *(unsigned*)value / BITNUM;
	}
	
	if (this->section == 0 || this->section == *(unsigned*)value)
	{
		if (this->group.size() < *(unsigned*)value / BITNUM + 1)
		{
			this->group.resize(*(unsigned*)value / BITNUM + 1);
		}
		this->group[*(unsigned*)value / BITNUM] |= (1 << *(unsigned*)value % BITNUM);
	}
	else
	{
		this->group.resize(*(unsigned*)value / BITNUM + 1);
		this->group[this->section] = this->group[0];
		this->group[0] = 0;
		this->section = 0;
		this->group[*(unsigned*)value / BITNUM] |= (1 << *(unsigned*)value % BITNUM);
	}
}

void Binary_Hash_Larger::erase(void* value)
{
	if (*(unsigned*)value / BITNUM + 1 <= this->group.size())
	{
		this->group[*(unsigned*) value / BITNUM] ^= (this->contains(value)) ? (1 << *(unsigned*)value % BITNUM) : 0;
	}
}

void Binary_Hash_Larger::reserve(std::size_t size)
{
	this->group.reserve(size / BITNUM + 1);
	if (this->section != 0)
	{
    this->group[this->section] = this->group[0];
    this->group[0] = 0;
 		this->section = 0;
	}
}

bool Binary_Hash_Larger::contains(void* value)
{
	if (*(unsigned*)value / BITNUM + 1 > this->group.size() && *(unsigned*)value / BITNUM + 1 > this->section)
	{
		return false;
	}
	else
	{
		if (this->section == 0)
		{
			return ((this->group[*(unsigned*)value / BITNUM] >> (*(unsigned*)value % BITNUM)) & 1 == 1) ? true : false;
		}
		else
		{
			return ((this->group[0] >> (*(unsigned*)value % BITNUM)) & 1 == 1) ? true : false;
		}
	}
}

void Binary_Hash_Larger::clear()
{
	this->max_section = 0;
	this->section = 0;
	this->group.clear();
}

std::size_t Binary_Hash_Larger::size()
{
	std::size_t count = 0;
	for (std::size_t n = 0, k = 1; n < this->group.size(); ++k)
	{
		if (this->group[n] != 0)
		{
			n += ((k %= BITNUM) == 0) ? 1 : 0;
			count += ((this->group[n] >> k) & 1 == 1) ? 1 : 0;
		}
		else
		{
			++n;
		}
	}
	return count;
}

#endif //BINARY_HASH_LARGER_HPP

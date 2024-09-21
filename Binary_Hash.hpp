#ifndef BINARY_HASH_HPP	
#define BINARY_HASH_HPP

#include <vector>

class Binary_Hash
{
private:
	unsigned short section;
	std::vector<unsigned char> group;

public:
	Binary_Hash();
	Binary_Hash(const Binary_Hash& binhash);
	Binary_Hash(void* value);

	void insert(void* value);
	void erase(void* value);
	void reserve(std::size_t size);
	bool contains(void* value);
	void clear();
	std::size_t size();
};


inline Binary_Hash::Binary_Hash()
{
	this->section = 0;
	this->group = std::vector<unsigned char>(1, 0);
}

inline Binary_Hash::Binary_Hash(const Binary_Hash& binhash)
{
	this->section = binhash.section;
	this->group = binhash.group;
}

inline Binary_Hash::Binary_Hash(void* value)
{
	this->section = *(unsigned*)value / 8;
	this->group = std::vector<unsigned char>(1, 0);
	this->group[0] |= (1 << *(unsigned*)value % 8);
}

inline void Binary_Hash::insert(void* value)
{
	if (this->section == 0 || this->section == *(unsigned*)value)
	{
		if (this->group.size() < *(unsigned*)value / 8 + 1)
		{
			this->group.resize(*(unsigned*)value / 8 + 1);
		}
		this->group[*(unsigned*)value / 8] |= (1 << *(unsigned*)value % 8);
	}
	else
	{
		this->group.resize(*(unsigned*)value / 8 + 1);
		this->group[this->section] = this->group[0];
		this->group[0] = 0;
		this->section = 0;
		this->group[*(unsigned*)value / 8] |= (1 << *(unsigned*)value % 8);
	}
}

inline void Binary_Hash::erase(void* value)
{
	if (*(unsigned*)value / 8 + 1 <= this->group.size())
	{
		this->group[*(unsigned*) value / 8] ^= (this->contains(value)) ? (1 << *(unsigned*)value % 8) : 0;
	}
}

inline void Binary_Hash::reserve(std::size_t size)
{
	this->group.reserve(size / 8 + 1);
	if (this->section != 0)
	{
    this->group[this->section] = this->group[0];
    this->group[0] = 0;
 		this->section = 0;
	}
}

inline bool Binary_Hash::contains(void* value)
{
	if (((*(unsigned*)value / 8 + 1) > this->group.size()) && ((*(unsigned*)value / 8 + 1) > this->section))
	{
		//make sure that the number is in bounds of list before checking in the vectors
		return false;
	}
	else
	{
		if (this->section == 0)
		{
			//if section starts at 0, then there is no offset. Scroll through indices at mod 8
			return ((((this->group[*(unsigned*)value / 8] >> (*(unsigned*)value % 8))) & 1) == 1) ? true : false;
		}
		else
		{
			//if section doesn't start at 0, then the number will be in this region
			return ((((this->group[0] >> ((*(unsigned*)value % 8))) & 1) == 1)) ? true : false;
		}
	}
}

inline void Binary_Hash::clear()
{
	this->section = 0;
	this->group.clear();
}

inline std::size_t Binary_Hash::size()
{
	std::size_t count = 0;
	for (std::size_t n = 0, k = 1; n < this->group.size(); ++k)
	{
		if (this->group[n] != 0)
		{
			n += ((k %= 8) == 0) ? 1 : 0;
			count += (((this->group[n] >> k) & 1) == 1) ? 1 : 0;
		}
		else
		{
			++n;
		}
	}
	return count;
}

#endif //BINARY_HASH_HPP

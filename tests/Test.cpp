#include "../Binary_Hash.hpp"
#include "../Binary_Hash_Larger.hpp"
#include <iostream>
#include <unordered_set>
#include <set>
#include <chrono>
#include <string>
using namespace std;

void Binary_Hash_speed(unsigned);
void Binary_Hash_Larger_speed(unsigned);
void unordered_set_speed(unsigned);
void set_speed(unsigned);

int main(int argc, const char* argv[])
{
	bool insertion_test = false;
	//INSERTION TEST
	if (argc != 1 && string(argv[1]) == "insertion-test")
	{
		Binary_Hash hash;
		
		for (unsigned n = 8; n < 19; ++n)
		{
			cout << "Test: " << n << endl;
			cout << "Does it contain " << n << "?\t";
			if (hash.contains(&n))
			{
				cout << "ERROR. Should not contain " << n << endl;
			}
			else
			{
				cout << "No" << endl;
			}

			cout << "Adding value " << n << endl;
			hash.insert(&n);
			if (hash.contains(&n))
			{
				cout << "Value successfully added" << endl;
			}
			else
			{
				cout << "Error has occurred" << endl;
			}
			cout << endl;
		}

		cout << "Total number of values added: " << hash.size() << endl;
		cout << endl;

		for (unsigned n = 0; n < 19; ++n)
		{
			cout << "Double check to see if " << n << " is accessible" << endl;
			if (hash.contains(&n))
			{
				cout << "Contains " << n << endl;
			}
			else
			{
				cout << n << " is not accessible" << endl;
			}
			cout << endl;
		}
		cout << "Clearing all values... ";
		hash.clear();
		cout << "Hash class size: " << hash.size() << endl;
		cout << endl;

		insertion_test = true;
	}

  //Speed Test
	unsigned size = 0;
	if (argc == 1 && insertion_test == false)
	{
		size = 500000;
	}
	else
	{
		size = (unsigned)stoi(string(argv[1]));
	}

	//size ^= ~size;
	//size >>= 8;

	Binary_Hash_speed(size);
	Binary_Hash_Larger_speed(size);
	unordered_set_speed(size);
	set_speed(size);
	return 0;
}


void Binary_Hash_speed(unsigned size)
{
	Binary_Hash hash;
	auto start = chrono::high_resolution_clock::now();
	for (unsigned n = 0; n < size; ++n)
	{
		hash.insert(&n);
	}
	auto stop = chrono::high_resolution_clock::now();
	cout << "Binary Hash Execution Time:\t" << chrono::duration_cast<chrono::microseconds>(stop - start).count() << "\tmicroseconds" << endl;
}

void Binary_Hash_Larger_speed(unsigned size)
{
	Binary_Hash_Larger hash;
	auto start = chrono::high_resolution_clock::now();
	for (unsigned n = 0; n < size; ++n)
	{
		hash.insert(&n);
	}
	auto stop = chrono::high_resolution_clock::now();
	cout << "Binary Hash (L) Execution Time:\t" << chrono::duration_cast<chrono::microseconds>(stop - start).count() << "\tmicroseconds" << endl;
}

void unordered_set_speed(unsigned size)
{
	unordered_set<unsigned> u_set;
	auto start = chrono::high_resolution_clock::now();
	for (unsigned n = 0; n < size; ++n)
	{
		u_set.insert(n);
	}	
	auto stop = chrono::high_resolution_clock::now();
	cout << "Unordered Set Execution Time:\t" << chrono::duration_cast<chrono::microseconds>(stop - start).count() << "\tmicroseconds" << endl;
}

void set_speed(unsigned size)
{
	set<unsigned> Set;
	auto start = chrono::high_resolution_clock::now();
	for (unsigned n = 0; n < size; ++n)
	{
		Set.insert(n);
	}	
	auto stop = chrono::high_resolution_clock::now();
	cout << "Ordered Set Execution Time:\t" << chrono::duration_cast<chrono::microseconds>(stop - start).count() << "\tmicroseconds" << endl;
}
	

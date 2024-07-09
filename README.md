A minimal hashing function for serialized items.

Within the class, 'unsigned char' data type is used since it is the only data type that is standardized by C++. Benchmarking between a larger data type seems to indicate that 8-bits is the quickest.

When inputting any integer type of data, the 'void * value' pointer reads all inputs as unsigned binary strings. Each 'std::vector<unsigned char>' index can group 8 values at a time.
Any given value is indexed as 'group[value / 8]' and grouped by flipping the bit corresponding to 'value % 8'

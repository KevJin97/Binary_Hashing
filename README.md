A minimal hashing function for indexed items. 'unsigned short section' is used in the event that only larger values are grouped together in order to save space. This can probably be optimized further by switching from 'char' type or improving the functionality of the indicator to handle more than one range.

When inputting any integer type of data, the 'void * value' pointer reads all inputs as unsigned binary strings. Each 'std::vector<unsigned char>' index can group 8 values.

Any given value is indexed as 'group[value / 8]' and grouped by flipping the bit corresponding to 'value % 8'

After testing the Larger ranged variation of the class, it was shown to exceed the 8-bit version by a non-marginal amount.
TODO: Ensure that the 'contains' function is operating as expected
TODO: Implement various default sizes of the hash function


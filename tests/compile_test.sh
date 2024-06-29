mkdir -p exe_files
g++ -O0 -o exe_files/Binary_Hash_Test.out0 Test.cpp ../Binary_Hash.hpp ../Binary_Hash_Larger.hpp
g++ -O1 -o exe_files/Binary_Hash_Test.out1 Test.cpp ../Binary_Hash.hpp ../Binary_Hash_Larger.hpp
g++ -O2 -o exe_files/Binary_Hash_Test.out2 Test.cpp ../Binary_Hash.hpp ../Binary_Hash_Larger.hpp
g++ -O3 -o exe_files/Binary_Hash_Test.out3 Test.cpp ../Binary_Hash.hpp ../Binary_Hash_Larger.hpp
echo -e "\e[93mOptimization Level 0:\e[0m"
./exe_files/Binary_Hash_Test.out0
echo -e "\e[93mOptimization Level 1:\e[0m"
./exe_files/Binary_Hash_Test.out1
echo -e "\e[93mOptimization Level 2:\e[0m"
./exe_files/Binary_Hash_Test.out2
echo -e "\e[93mOptimization Level 3:\e[0m"
./exe_files/Binary_Hash_Test.out3

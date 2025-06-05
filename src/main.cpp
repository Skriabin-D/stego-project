#include <iostream>
#include "encoding/Hamming.hpp"
#include "embedding_extracting/lsb_dct.hpp"
#include "embedding_extracting/pvd.hpp"
#include <string>
#include <vector>

int main() {
	std::string message;
	std::getline(std::cin, message);
	std::vector<uint8_t> bitseq;

	bitseq = stringToBitSequence(message);
	bitseq = encodeBitSequence(bitseq);

	embed_pvd("D:/stego_project/resourses/input.png", bitseq, "D:/stego_project/resourses/output.png");
}
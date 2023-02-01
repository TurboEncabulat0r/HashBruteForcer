#include <iostream>
#include "hash-library/sha256.h"
#include <chrono>
#include <ctime>    
#include <cmath>

#define LENGTH 8
#define TRIES_PER_PRINT 1000000


std::string input;
std::string in;

unsigned long long int combos;
unsigned int tries;
unsigned int triesRequired = 0;

SHA256 sha256;

auto start = std::chrono::system_clock::now();
double temptime = 0;



std::string encrypt(std::string key) 
{ 
  return sha256(key);
}

// counts up the string, there might be a better way to to do this but i cant be bothered
std::string add(std::string str) {
  std::string l = str;

  if (l[l.length() - 1] != 'z') {
    l[l.length() - 1] += 1;
  } else {

    for (int i = LENGTH - 1; i >= 0; i--) {
      if (i - 1 >= 0) {
        if (l[i] == 'z') {
          l[i - 1] += 1;
          l[i] = 'a';
        }
      } else {
        break;
      }
    }
  }

  return l;
}

void crack() {
  std::string cur;

  for (int i = 0; i < LENGTH; i++) {
    cur += 'a';
  }
  std::cout << "starting with value " + cur << std::endl;
  std::cout << "printing out every " << TRIES_PER_PRINT << " tries" << std::endl;



  while (true) {
    
    if (encrypt(cur) == input) {
      std::cout << "solved! input text is " << cur << std::endl;
      break;
    }
    else {
          
      if (tries >= triesRequired) {

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> seconds = end-start;
        auto sec = seconds.count();

        std::cout << "_______________________" << std::endl;
        std::cout << "time elapsed: " << floor(sec/3600) << ":" << (int)floor(sec/60) % 60 << ":" << (int)round(sec) % 60 << std::endl; 
        unsigned long long int timeleft = (combos - tries) / TRIES_PER_PRINT/(sec-temptime);
        std::cout << "time left: " << floor(timeleft/3600) << ":" << (int)floor(timeleft/60) % 60 << ":" << (int)round(timeleft) % 60 << std::endl; 
        std::cout << "tries: " << tries << std::endl;
        std::cout << "hashes per second: " << (TRIES_PER_PRINT/(sec-temptime)) << std::endl;
        std::cout << "current string: " << cur << std::endl;

        temptime = sec;
        triesRequired += TRIES_PER_PRINT;
      }
      tries += 1;
    }

    if (cur == "zzzzzzzz") {
      std::cout << "failed to crack hash" << std::endl;
      break;
    }

    cur = add(cur);
  }
}

int main() {
  std::cout << "hash to crack: ";
  std::cin >> input;

  std::cout << "starting with input: " << input << std::endl;
  combos = pow(26, 8);
  std::cout << "max combos: " << combos << "\n" << std::endl;
  start = std::chrono::system_clock::now();
  crack();
  return 0;
}
// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2021

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <map>

using namespace std;

// A simple class; each object holds four public fields
class Data {
 public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename);
  if (!input) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData:l) {
    output << pData->lastName << " "
           << pData->firstName << " "
           << pData->ssn << "\n";
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.\n";

  cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

bool compareFirstName(Data* first, Data* last) {
  return first->firstName.compare(last->firstName) < 0;
}

bool compareLastName(Data* first, Data* last) {
  return first->lastName < last->lastName;
}

bool compareSSN(Data* first, Data* last) {
  return first->ssn < last->ssn;
}

bool compare(Data* first, Data* last) {
  int comp = first->lastName.compare(last->lastName);
  if (comp != 0)
    return comp < 0;
  comp = first->firstName.compare(last->firstName);
  if (comp != 0)
    return comp < 0;
  return first->ssn.compare(last->ssn) < 0;
}

bool compareFirstNameSSNOnly(Data* first, Data* last) {
  int comp = first->firstName.compare(last->firstName);
  if (comp != 0)
    return comp < 0;
  return first->ssn.compare(last->ssn) < 0;
}

void sortBySSN(list<Data *> &l) {
  int BUCKET_SIZE = 10;
  list<Data *> buckets[BUCKET_SIZE];
  for (int i = 10; i >= 0; i--) {
    if (i == 3 || i == 6)
      continue;
    for (auto it = l.begin(); it != l.end(); it++) {
      buckets[(*it)->ssn.at(i) - '0'].push_back(*it);
    }
    l.clear();
    for (int k = 0; k < BUCKET_SIZE; k++) {
      auto nl = buckets[k];
      for (auto it = nl.begin(); it != nl.end(); it++) {
        l.push_back(*it);
      }
      nl.clear();
    }
  }
}

int longestLastName(list<Data *> &l) {
  int max = 0;
  for (auto it = l.begin(); it != l.end(); it++) {
    int value = (*it)->lastName.length();
    if (value > max)
      max = value;
  }
  return max;
}

void sortByLastName(list<Data *> &l) {
  int BUCKET_SIZE = 27;
  list<Data *> buckets[BUCKET_SIZE];
  int MAX_LENGTH = longestLastName(l);
  for (int i = MAX_LENGTH - 1; i >= 0; i--) {
    for (auto it = l.begin(); it != l.end(); it++) {
      string lastName = (*it)->lastName;
      if (lastName.size() <= i) {
        buckets[27].push_back(*it);
        continue;
      }
      buckets[lastName.at(i) - 'A'].push_back(*it);
    }
    l.clear();
    for (int k = 0; k < BUCKET_SIZE; k++) {
      auto nl = buckets[k];
      for (auto it = nl.begin(); it != nl.end(); it++) {
        l.push_back(*it);
      }
      nl.clear();
    }
  }
}

int longestFirstName(list<Data *> &l) {
  int max = 0;
  for (auto it = l.begin(); it != l.end(); it++) {
    int value = (*it)->firstName.length();
    if (value > max)
      max = value;
  }
  return max;
}



void sortByFirstName(list<Data *> &l) {
  int BUCKET_SIZE = 27;
  list<Data *> buckets[BUCKET_SIZE];
  int MAX_LENGTH = longestFirstName(l);
  for (int i = MAX_LENGTH - 1; i >= 0; i--) {
    for (auto it = l.begin(); it != l.end(); it++) {
      string firstName = (*it)->firstName;
      if (firstName.size() <= i) {
        buckets[27].push_back(*it);
        continue;
      }
      buckets[firstName.at(i) - 'A'].push_back(*it);
    }
    l.clear();
    for (int k = 0; k < BUCKET_SIZE; k++) {
      auto nl = buckets[k];
      for (auto it = nl.begin(); it != nl.end(); it++) {
        l.push_back(*it);
      }
      nl.clear();
    }
  }
}

const int AFS_RADIX=27;
const int LONGEST_NAME = 20;

enum field {
  lastName = 1,
  firstName = 2,
  ssn = 3,
};

struct nameLengths {
  int firstName = 0;
  int lastName = 0;
};

string* getVal(Data * d, field f) {
  switch (f) {
    case lastName:
      return &d->lastName;
    case firstName:
      return &d->firstName;
  }
  return &d->ssn;
}

char valueAt(Data * d, field type, int pos) {
  string *str = getVal(d, type);
  if (str->length() > pos) {
    return str->at(pos) - 'A' + 1;
  }
  return 0;
}

nameLengths longestName(list<Data *> &l) {
  nameLengths n;
  for (auto it = l.begin(); it != l.end(); it++) {
    int fn = (*it)->firstName.length();
    int ln = (*it)->lastName.length();
    if (fn > n.firstName)
      n.firstName = fn;
    if(ln > n.lastName)
      n.lastName = ln;
  }
  return n;
}

size_t longestNameType(list<Data *> &l, field type) {
  int max = 0;
  for (auto it = l.begin(); it != l.end(); it++) {
    int value = getVal(*it, type)->length();
    if (value > max)
      max = value;
  }
  return max;
}

void _afsSwapAll(vector<Data *> &v, int* offsets, int start, int digit, field type) {
  int i = start;
  int nf[AFS_RADIX] = {};
  int current_block = 0;
  copy(offsets, offsets + AFS_RADIX, begin(nf));
  while (current_block < AFS_RADIX - 1) {
    if (i >= start + offsets[current_block + 1]) {
      current_block += 1;
      continue;
    }
    char val = valueAt(v[i], type, digit);
    if (val == current_block) {
      i += 1;
      continue;
    }
    auto swap_to = start + nf[val];
    auto tmp = v[swap_to];
    v[swap_to] = v[i];
    v[i] = tmp;
    nf[val] += 1;
  }
}

void _afsOffsets (vector<Data *> &v, int start, int end, int digit, int* offsets, field type) {
  int counts[AFS_RADIX] = {};
  for (int i = start; i < end; i++) {
    counts[valueAt(v[i], type, digit)] += 1;
  }
  long sum = 0;
  for (int i = 0; i < AFS_RADIX + 1; i++) {
    offsets[i] = sum;
    sum += counts[i];
  }
}

void _recurseAmericanFlagSort(vector <Data *> &v, map<int, bool> *allOffsets, int start, int end, int digit, int max, field type) {
  int offsets[AFS_RADIX + 1] = {};
  _afsOffsets(v, start, end, digit, offsets, type);
  _afsSwapAll(v, offsets, start, digit, type);
  if (allOffsets != nullptr) {
    for (int i = 0; i < AFS_RADIX; i++) {
      (*allOffsets)[offsets[i] + start] = true;
    }
  }
  if (digit == max) {
    return;
  }
  for (int i = 0; i < AFS_RADIX; i++) {
    if (offsets[i + 1] - 1000 < offsets[i]) {
      if (offsets[i + 1] != offsets[i]) {
        auto b = v.begin() + start + offsets[i];
        auto l = v.begin() + start + offsets[i + 1];
        sort(b, l, compareLastName);
        for (auto it = b + 1; it != l; it++) {
          if (getVal(*it, type)->compare(*getVal(*prev(it), type)) != 0) {
            (*allOffsets)[it - v.begin()] = true;
          }
        }
      }
      continue;
    }
    _recurseAmericanFlagSort(v, allOffsets, start + offsets[i], start + offsets[i + 1], digit + 1, max, type);
  }
}


void americanFlagSort(list <Data *> &l, vector<Data *> &v, map<int, bool> *offsets, int start, int end, field type) {
  int max = longestNameType(l, type);
  _recurseAmericanFlagSort(v, offsets, start, end, 0, max, type);
}

void sortDataList(list<Data *> &l) {
  // Fill this in


  // Radix sort try
//  sortBySSN(l);
//  sortByFirstName(l);
//  sortByLastName(l);

  // American Flag Sort first try
  map<int, bool> offsets;
  offsets[0] = true;
  offsets[l.size()] = true;
  vector<Data *> v;
  v.reserve(l.size());
  copy(l.begin(), l.end(), back_inserter(v));
  americanFlagSort(l, v, &offsets, 0, l.size(), field::lastName);
  auto beginning = v.begin();
  list<int> offsetsLists;
  for (auto const &m: offsets) {
    offsetsLists.push_back(m.first);
  }
  auto endOffsets = prev(offsetsLists.end());
  for (auto it = offsetsLists.begin(); it != endOffsets; it++) {
    auto n = *next(it);
    auto b = *it;
    if (true || b + 50 > n) {
      if (b + 1 != n) {
        auto be = beginning + b;
        auto la = beginning + n;
//        sort(beginning + b, beginning + n, compareFirstName);
        sort(be, la, compareFirstNameSSNOnly);
//        for (auto it = be + 1; it != la; it++) {
//          if ((*it)->firstName != (*prev(it))->firstName) {
//            offsets[it - beginning] = true;
//          }
//        }
      }
    } else {
      americanFlagSort(l, v, &offsets, b, n, field::firstName);
    }
  }

//  list <int> offsetsLists1;
//  for (auto const &m: offsets) {
//    offsetsLists1.push_back(m.first);
//  }
//  auto endOffsets1 = prev(offsetsLists1.end());
//
//  for (auto it = offsetsLists1.begin(); it != endOffsets1; it++) {
//    auto n = *next(it);
//    auto b = *it;
//    if (true || b + 50 > n) {
//      if (b + 1 != n) {
//        sort(beginning + b, beginning + n, compareSSN);
//      }
//    } else {
//      americanFlagSort(l, v, nullptr, b, n, field::ssn);
//    }
//  }

  l.clear();
  copy(v.begin(), v.end(), back_inserter(l));

  // Straight l.sort
//  l.sort(compare);

  // Vector sort
//  vector<Data *> v;
//  v.reserve(l.size());
//  copy(begin(l), end(l), back_inserter(v));
//  sort(v.begin(), v.end(), compare);
//  l.clear();
//  copy(v.begin(), v.end(), back_inserter(l));
}



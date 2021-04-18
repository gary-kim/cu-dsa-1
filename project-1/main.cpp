/*
 * dsa-1-project-1 will read in a file of commands for Lists and execute them
 * Copyright (C) 2021 Gary Kim <gary@garykim.dev>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "main.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

/**
 * If run with arguments, the 1st argument will be used as the input file
 * and the second argument will be used as the output file. It is possible
 * to also use "-" as a filename to use stdin or stdout.
 */
int main(int argc, char **argv) {
  std::string inputFilePath, outputFilePath;
  std::ofstream outputFile;
  std::ifstream inputFile;
  if (argc >= 3) {
    inputFilePath = std::string(argv[1]);
    outputFilePath = std::string(argv[2]);
  } else {
    std::cout << "Enter name of input file: ";
    std::cin >> inputFilePath;
    std::cout << "Enter name of output file: ";
    std::cin >> outputFilePath;
  }

  // setup stdin and stdout to the requested files
  if (inputFilePath != "-") {
    inputFile.open(inputFilePath);
    std::cin.rdbuf(inputFile.rdbuf());
  }
  if (outputFilePath != "-") {
    outputFile.open(outputFilePath);
    std::cout.rdbuf(outputFile.rdbuf());
  }

  runFile();
  return 0;
}

/**
 * Reads in a list of commands from stdin and executes each command
 * then outputs the results of each command to stdout
 */
void runFile() {
  // make an instance of Lists
  Lists list{new std::unordered_map<std::string, SimpleList<std::string> *>,
             new std::unordered_map<std::string, SimpleList<double> *>,
             new std::unordered_map<std::string, SimpleList<int> *>};

  // run each command
  while (std::cin.peek() != EOF) {
    std::string command;
    std::cin >> command;
    if (command == "create") {
      std::string name, type;
      std::cin >> name >> type;
      create(&list, name, type);
      continue;
    }
    if (command == "push") {
      std::string name, value;
      std::cin >> name >> value;
      push(&list, name, value);
      continue;
    }
    if (command == "pop") {
      std::string name;
      std::cin >> name;
      pop(&list, name);
      continue;
    }
  }
}

/**
 * create is an implementation for the create command that could be given.
 * @param mp Lists instance to add the created list into
 * @param name the name of the list to create
 * @param type the type of list to create
 */
void create(Lists *mp, std::string name, std::string type) {
  std::cout << "PROCESSING COMMAND: create " << name << " " << type << "\n";
  listContents listContent = getListContents(name);
  if (listContent == listContents::aString) {
    SimpleList<std::string> *list = (*mp->strings)[name];
    if (list != nullptr) {
      std::cout << "ERROR: This name already exists!\n";
      return;
    }
    if (type == "stack") {
      (*mp->strings)[name] = new Stack<std::string>();
    } else {
      (*mp->strings)[name] = new Queue<std::string>();
    }
    return;
  }
  if (listContent == listContents::aDouble) {
    SimpleList<double> *list = (*mp->doubles)[name];
    if (list != nullptr) {
      std::cout << "ERROR: This name already exists!\n";
      return;
    }
    if (type == "stack") {
      (*mp->doubles)[name] = new Stack<double>();
    } else {
      (*mp->doubles)[name] = new Queue<double>();
    }
    return;
  }
  if (listContent == listContents::anInteger) {
    SimpleList<int> *list = (*mp->ints)[name];
    if (list != nullptr) {
      std::cout << "ERROR: This name already exists!\n";
      return;
    }
    if (type == "stack") {
      (*mp->ints)[name] = new Stack<int>();
    } else {
      (*mp->ints)[name] = new Queue<int>();
    }
  }
}

/**
 * push is an implementation for the push command that could be given.
 * @param mp Lists instance to containing the list to be modified
 * @param name the name of the list to push the value onto
 * @param value the value to push onto the list
 */
void push(Lists *mp, std::string name, std::string value) {
  std::cout << "PROCESSING COMMAND: push " << name << " " << value << "\n";
  listContents listContent = getListContents(name);
  if (listContent == listContents::aString) {
    SimpleList<std::string> *list = (*mp->strings)[name];
    if (list == nullptr) {
      std::cout << "ERROR: This name does not exist!\n";
      return;
    }
    list->push(value);
    return;
  }
  if (listContent == listContents::aDouble) {
    SimpleList<double> *list = (*mp->doubles)[name];
    if (list == nullptr) {
      std::cout << "ERROR: This name does not exist!\n";
      return;
    }
    list->push(atof(value.c_str()));
    return;
  }
  if (listContent == listContents::anInteger) {
    SimpleList<int> *list = (*mp->ints)[name];
    if (list == nullptr) {
      std::cout << "ERROR: This name does not exist!\n";
      return;
    }
    list->push(atoi(value.c_str()));
  }
}

/**
 * pop is an implementation for the pop command that could be given.
 * @param mp Lists instance to containing the list to be modified
 * @param name the name of the list to push the value onto
 */
void pop(Lists *mp, std::string name) {
  std::cout << "PROCESSING COMMAND: pop " << name << "\n";
  listContents listContent = getListContents(name);
  if (listContent == listContents::aString) {
    SimpleList<std::string> *list = (*mp->strings)[name];
    if (list == nullptr) {
      std::cout << "ERROR: This name does not exist!\n";
      return;
    }
    if (list->isEmpty()) {
      std::cout << "ERROR: This list is empty!\n";
      return;
    }
    std::cout << "Value popped: " << list->pop() << "\n";
    return;
  }
  if (listContent == listContents::aDouble) {
    SimpleList<double> *list = (*mp->doubles)[name];
    if (list == nullptr) {
      std::cout << "ERROR: This name does not exist!\n";
      return;
    }
    if (list->isEmpty()) {
      std::cout << "ERROR: This list is empty!\n";
      return;
    }
    std::cout << "Value popped: " << list->pop() << "\n";
    return;
  }
  if (listContent == listContents::anInteger) {
    SimpleList<int> *list = (*mp->ints)[name];
    if (list == nullptr) {
      std::cout << "ERROR: This name does not exist!\n";
      return;
    }
    if (list->isEmpty()) {
      std::cout << "ERROR: This list is empty!\n";
      return;
    }
    std::cout << "Value popped: " << list->pop() << "\n";
    return;
  }
}

/**
 * Uses the name of the list to identify its contents
 * @param name the name of the list
 * @return listContents
 */
listContents getListContents(std::string name) {
  switch (name.at(0)) {
    case 's':
      return listContents::aString;
    case 'i':
      return listContents::anInteger;
    default:
    case 'd':
      return listContents::aDouble;
  }
}

//    Copyright (C) 2021 Gary Kim <gary@garykim.dev>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Affero General Public License as published
//    by the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#include <iostream>
#include "main.h"
#include <unordered_map>
#include <string>
#include <fstream>

int main(int argc, char** argv) {
    runFile("input.txt");
    return 0;
}

void runFile(std::string filename) {
    // map of everything
    std::unordered_map<std::string, listEntry> m;

    std::ifstream input;
    input.open(filename);

    // run each command
    while (input.peek() != EOF) {
        std::string command;
        input >> command;
        if (command == "create") {
            std::string name, type;
            input >> name >> type;
            create(m, name, type);
            continue;
        }
        if (command == "push") {
            std::string name, value;
            input >> name >> value;
            push(m, name, value);
            continue;
        }
        if (command == "pop") {
            std::string name;
            input >> name;
            pop(m, name);
            continue;
        }
    }
}

void create(std::unordered_map<std::string, listEntry>& m, std::string name, std::string type) {
    std::cout << "PROCESSING COMMAND: create " << name << " " << type << "\n";
    listEntry list = m[name];
    if (list.list != NULL) {
        std::cout << "ERROR: This name already exists!\n";
        return;
    }
    void* ta = NULL;
    listType lType = listType::queue;
    if (type == "queue") {
        switch (getListContents(name)) {
            case listContents::aString:
                ta = new Queue<std::string>(name);
                break;
            case listContents::aDouble:
                ta = new Queue<double>(name);
                break;
            case listContents::anInteger:
                ta = new Queue<int>(name);
                break;
        }
    } else {
        switch (getListContents(name)) {
            case listContents::aString:
                ta = new Stack<std::string>(name);
                break;
            case listContents::aDouble:
                ta = new Stack<double>(name);
                break;
            case listContents::anInteger:
                ta = new Stack<int>(name);
                break;
        }
       lType = listType::stack;
    }
    m[name] = listEntry{ta, lType};
}

void push(std::unordered_map<std::string, listEntry>& m, std::string name, std::string value) {
    std::cout << "PROCESSING COMMAND: push " << name << " " << value << "\n";
    listEntry list = m[name];
    if (list.list == NULL) {
        std::cout << "ERROR: This name does not exist!\n";
        return;
    }
    if (list.type == listType::queue) {
        switch (getListContents(name)) {
            case listContents::aString:
                ((Queue<std::string>*)(list.list))->push(value);
                break;
            case listContents::aDouble:
                ((Queue<double>*)(list.list))->push(atof(value.c_str()));
                break;
            case listContents::anInteger:
                ((Queue<int>*)(list.list))->push(atoi(value.c_str()));
                break;
        }
    } else {
        switch (getListContents(name)) {
            case listContents::aString:
                ((Stack<std::string>*)(list.list))->push(value);
                break;
            case listContents::aDouble:
                ((Stack<double>*)(list.list))->push(atof(value.c_str()));
                break;
            case listContents::anInteger:
                ((Stack<int>*)(list.list))->push(atoi(value.c_str()));
                break;
        }
    }
}

void pop(std::unordered_map<std::string, listEntry>& m, std::string name) {
    std::cout << "PROCESSING COMMAND: pop " << name << "\n";
    listEntry list = m[name];
    if (list.list == NULL) {
        std::cout << "ERROR: This name does not exist!\n";
        return;
    }
    if (list.type == listType::queue) {
        listContents contents = getListContents(name);
        if (contents == listContents::aString) {
            Queue<std::string>* l = (Queue<std::string>*)(list.list);
            if (l->isEmpty()) {
                std::cout << "ERROR: This list is empty!\n";
                return;
            }
            std::cout << "Value popped: " << l->pop() << "\n";
        } else if (contents == listContents::aDouble) {
            Queue<double>* l = (Queue<double>*)(list.list);
            if (l->isEmpty()) {
                std::cout << "ERROR: This list is empty!\n";
                return;
            }
            std::cout << "Value popped: " << l->pop() << "\n";
        } else {
            Queue<int>* l = (Queue<int>*)(list.list);
            if (l->isEmpty()) {
                std::cout << "ERROR: This list is empty!\n";
                return;
            }
            std::cout << "Value popped: " << l->pop() << "\n";
        }
    } else {
        listContents contents = getListContents(name);
        if (contents == listContents::aString) {
            Stack<std::string>* l = (Stack<std::string>*)(list.list);
            if (l->isEmpty()) {
                std::cout << "ERROR: This list is empty!\n";
                return;
            }
            std::cout << "Value popped: " << l->pop() << "\n";
        } else if (contents == listContents::aDouble) {
            Stack<double>* l = (Stack<double>*)(list.list);
            if (l->isEmpty()) {
                std::cout << "ERROR: This list is empty!\n";
                return;
            }
            std::cout << "Value popped: " << l->pop() << "\n";
        } else {
            Stack<int>* l = (Stack<int>*)(list.list);
            if (l->isEmpty()) {
                std::cout << "ERROR: This list is empty!\n";
                return;
            }
            std::cout << "Value popped: " << l->pop() << "\n";
        }
    }
}

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

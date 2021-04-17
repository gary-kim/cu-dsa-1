/*
 * dsa-1-project-1 will read in a file of commands for lists and execute them
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

#ifndef CU_DSA_1_MAIN_H
#define CU_DSA_1_MAIN_H

#include <stdexcept>
#include <string>
#include <unordered_map>

/**
 * A simple singly-linked list implementation
 * @tparam T the type of the value the list will store
 */
template <class T>
class List {
 private:
  std::string name;
  class Node {
   public:
    Node *next = NULL;
    T value;
    Node(T value) : value(value) {}
    Node(T value, Node *next) : value(value), next(next) {}
  };
  Node *start = NULL;
  Node *end = NULL;

 protected:
  void insertStart(T const &);
  void insertEnd(T const &);
  T remove();

 public:
  List(std::string name) : name(name) {}
  virtual void push(T const &) = 0;
  virtual T pop() = 0;
  bool isEmpty();
};

/**
 * self-explanatory
 * @tparam T the type of the value to be inserted
 * @param value the value to be inserted
 */
template <class T>
void List<T>::insertStart(T const &value) {
  if (this->start == NULL) {
    this->start = new Node(value);
    this->end = this->start;
    return;
  }
  Node *tmp = this->start;
  this->start = new Node(value, tmp);
  return;
}

/**
 * self-explanatory
 * @tparam T the type of the value to be inserted
 * @param value the value to be inserted
 */
template <class T>
void List<T>::insertEnd(T const &value) {
  if (this->end == NULL) {
    this->start = new Node(value);
    this->end = this->start;
    return;
  }
  Node *tmp = this->end;
  this->end = new Node(value);
  tmp->next = this->end;
}

/**
 * removes an element from the start of the list
 * @tparam T the type of the value to be removed
 * @return the value that was removed
 */
template <class T>
T List<T>::remove() {
  Node *tr = this->start;
  if (tr == NULL) {
    throw std::range_error("List is empty");
  }
  this->start = this->start->next;
  if (this->start == NULL) {
    this->end = NULL;
  }
  T t = tr->value;
  delete tr;
  return t;
}

/**
 * self-explanatory
 * @tparam T the type of the value the list contains
 * @return whether the list is empty
 */
template <class T>
bool List<T>::isEmpty() {
  return this->start == NULL;
}

/**
 * A queue implementation based on List
 * @tparam T the type of the value the queue will store
 */
template <class T>
class Queue : public List<T> {
 public:
  void push(T const &value) { this->insertEnd(value); }
  T pop() { return this->remove(); }
  using List<T>::List;
};

/**
 * A stack implementation based on List
 * @tparam T the type of the value the stack will store
 */
template <class T>
class Stack : public List<T> {
 public:
  void push(T const &value) { this->insertStart(value); }
  T pop() { return this->remove(); }
  using List<T>::List;
};

enum listType {
  stack = 0,
  queue = 1,
};

struct listEntry {
  void *list = NULL;
  listType type;
};

enum listContents {
  anInteger = 1,
  aDouble = 2,
  aString = 3,
};

void runFile();
void create(std::unordered_map<std::string, listEntry> *, std::string,
            std::string);
void push(std::unordered_map<std::string, listEntry> *, std::string,
          std::string);
void pop(std::unordered_map<std::string, listEntry> *, std::string);
listContents getListContents(std::string);

#endif  // CU_DSA_1_MAIN_H

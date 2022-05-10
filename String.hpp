/*
 Ashot Gimishyan
 October, 2021
 MIPT
*/

#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>
#pragma once

class String {
 public:
  String();
  ~String();
  String(uint64_t, char);
  String(const char*);
  String(const String&);

  const char* Data() const;
  bool Empty() const;
  uint64_t Size() const;
  void Clear();
  void PushBack(char);
  void PopBack();
  void Resize(uint64_t);
  void Resize(uint64_t, char);
  void Reserve(uint64_t);
  uint64_t Capacity() const;
  void ShrinkToFit();
  void Swap(String&);

  char& Front();
  const char& Front() const;
  char& Back();
  const char& Back() const;

  String& operator*=(uint64_t);
  String& operator=(const String&);
  String& operator+=(const String&);
  String& operator+=(const char*);
  String& operator+=(char);

  char& operator[](uint64_t idx);
  const char& operator[](uint64_t idx) const;

  String Join(const std::vector<String>& vec) const;
  std::vector<String> Split(const String& delim = " ");

  friend std::ostream& operator<<(std::ostream&, const String&);
  friend std::istream& operator>>(std::istream&, String&);

  friend bool operator<(const String& lhs, const String& rhs);
  friend String operator+(const String& str1, const String& str2);
  friend String operator*(const String& mystring, uint64_t n);
  friend uint64_t Find(String mystring, const String& delim, uint64_t start);

 private:
  char* str_;
  uint64_t size_;
  uint64_t capacity_;
};

bool operator>(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);
bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);

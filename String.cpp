/* Ashot Gimishyan
   October, 2021
   MIPT   */

#include "String.hpp"

String::String() {
  size_ = 0;
  capacity_ = 0;
  str_ = nullptr;
};

String::~String() {
  delete[] str_;
}

String::String(uint64_t str_size, char str_character) {
  size_ = str_size;
  capacity_ = 0;
  str_ = new char[size_ + 1];
  for (uint64_t i = 0; i < size_; ++i) {
    str_[i] = str_character;
    if (size_ > capacity_ && capacity_ == 0) {
      ++capacity_;
    } else if ((size_ > capacity_ && capacity_ != 0)) {
      capacity_ *= 2;
    }
  }
  str_[size_] = '\0';
}

String::String(const char * str_in) {
  size_ = 0;
  while (str_in[size_] != '\0') {
    size_++;
  }
  capacity_ = 0;
  str_ = new char[size_ + 1];
  for (uint64_t i = 0; i < size_ + 1; ++i) {
    str_[i] = str_in[i];
    if (size_ > capacity_ && capacity_ == 0) {
      ++capacity_;
    } else if ((size_ > capacity_ && capacity_ != 0)) {
      capacity_ *= 2;
    }
  }
  str_[size_] = '\0';
}

String::String(const String & my_string) {
  size_ = my_string.size_;
  str_ = new char[size_ + 1];
  capacity_ = my_string.capacity_;
  for (uint64_t i = 0; i < size_; ++i) {
    str_[i] = my_string.str_[i];
  }
  str_[size_] = '\0';
}

uint64_t String::Size() const {
  return size_;
}

bool String::Empty() const {
  return size_ == 0;
}

const char * String::Data() const {
  return str_;
}

void String::Clear() {
  size_ = 0;
}

char & String::operator[](uint64_t idx) {
  return const_cast < char & > (static_cast <
    const String & > ( * this).operator[](idx));
}

const char & String::operator[](uint64_t idx) const {
  return str_[idx];
}

void String::PushBack(char str_character) {
  ++size_;
  if (size_ - 1 == 0 && capacity_ == size_ - 1) {
    capacity_ = 1;
  } else if (size_ != 0 && capacity_ == size_) {
    capacity_ *= 2;
  }

  char * tmp_str = new char[size_];
  for (uint64_t i = 0; i < size_ - 1; ++i) {
    tmp_str[i] = str_[i];
  }
  delete[] str_;
  str_ = new char[size_ + 1];
  for (uint64_t i = 0; i < size_ - 1; ++i) {
    str_[i] = tmp_str[i];
  }
  delete[] tmp_str;
  str_[size_ - 1] = str_character;
  str_[size_] = '\0';
}

void String::PopBack() {
  if (( * this).Size() == 0 U) {
    return;
  }
  str_[size_ - 1] = '\0';
  --size_;
}

void String::Resize(uint64_t new_size) {
  if (capacity_ >= new_size) {
    size_ = new_size;
    return;
  }

  char * new_buf = new char[new_size];
  for (uint64_t i = 0; i < size_; ++i) {
    new_buf[i] = str_[i];
  }

  delete[] str_;
  str_ = new char[new_size];
  for (uint64_t i = 0; i < size_; ++i) {
    str_[i] = new_buf[i];
  }
  for (uint64_t i = size_; i < new_size; ++i) {
    if (new_size > capacity_ && capacity_ == 0) {
      ++capacity_;
    } else if ((new_size > capacity_ && capacity_ != 0)) {
      capacity_ *= 2;
    }
  }
  size_ = new_size;
  delete[] new_buf;
}

void String::Resize(uint64_t new_size, char str_character) {
  uint64_t old_size = size_;
  ( * this).Resize(new_size);
  if (new_size > old_size) {
    for (uint64_t i = old_size; i < new_size; ++i) {
      str_[i] = str_character;
    }
  }
}

void String::Reserve(uint64_t new_cap) {
  if (new_cap > capacity_) {
    capacity_ = new_cap;
  }
}

uint64_t String::Capacity() const {
  return capacity_;
}

void String::ShrinkToFit() {
  if (capacity_ > size_) {
    capacity_ = size_;
  }
}

void String::Swap(String & other) {
  std::swap(str_, other.str_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

char & String::Front() {
  return const_cast < char & > (static_cast <
    const String & > ( * this).Front());
}
const char & String::Front() const {
  return str_[0];
}
char & String::Back() {
  return const_cast < char & > (static_cast <
    const String & > ( * this).Back());
}
const char & String::Back() const {
  return str_[size_ - 1];
}

bool operator == (const String & lhs,
  const String & rhs) {
  return !(lhs < rhs || rhs < lhs);
}

bool operator != (const String & lhs,
  const String & rhs) {
  return !(lhs == rhs);
}

bool operator > (const String & lhs,
  const String & rhs) {
  return !(lhs < rhs) && !(lhs == rhs);
}

bool operator >= (const String & lhs,
  const String & rhs) {
  return !(lhs < rhs);
}

bool operator < (const String & lhs,
  const String & rhs) {
  uint64_t min_size = lhs.size_;
  if (lhs.size_ > rhs.size_) {
    min_size = rhs.size_;
  }
  for (uint64_t i = 0; i < min_size; ++i) {
    if (lhs.str_[i] < rhs.str_[i]) {
      return true;
    }
  }
  return ((lhs.size_ - min_size) < (rhs.size_ - min_size));
}

bool operator <= (const String & lhs,
  const String & rhs) {
  return !(lhs > rhs);
}

String operator + (const String & str1,
  const String & str2) {
  String tmp;
  tmp.size_ = str1.size_ + str2.size_;
  tmp.capacity_ = str1.capacity_ + str2.capacity_;
  tmp.str_ = new char[tmp.size_];

  for (uint64_t i = 0; i < str1.size_; ++i) {
    tmp.str_[i] = str1.str_[i];
  }

  for (uint64_t i = 0; i < str2.size_; ++i) {
    tmp.str_[i + str1.size_] = str2.str_[i];
  }
  return tmp;
}

String & String::operator = (const String & mystring) {
  if ( & mystring != this) {
    delete[] str_;
    size_ = mystring.size_;
    str_ = new char[size_ + 1];
    for (uint64_t i = 0; i < size_; ++i) {
      str_[i] = mystring.str_[i];
    }
    capacity_ = mystring.capacity_;
    str_[size_] = '\0';
  }
  return *this;
}

String & String::operator += (const char * str_in) {
  String tmp;
  tmp.size_ = 0;
  while (str_in[tmp.size_] != '\0') {
    tmp.size_++;
  }

  tmp.capacity_ = 0;
  for (uint64_t i = 0; i < tmp.size_; i++) {
    if (tmp.size_ > tmp.capacity_ && tmp.capacity_ == 0) {
      ++tmp.capacity_;
    } else if ((tmp.size_ > tmp.capacity_ && tmp.capacity_ != 0)) {
      tmp.capacity_ *= 2;
    }
  }

  return *this += tmp;
}

String & String::operator += (char str_character) {
  this -> PushBack(str_character);
  return *this;
}

String & String::operator += (const String & mystring) {
  * this = * this + mystring;
  return *this;
}

String operator * (const String & mystring, uint64_t num) {
  String tmp = "";
  uint64_t num_copy = num;
  if (num < 2) {
    return (num == 0) ? tmp : mystring;
  }
  num /= 2;
  tmp = mystring * num;
  tmp += tmp;

  return (num_copy % 2) != 0 U ? tmp += mystring : tmp;
}

String & String::operator *= (uint64_t num) {
  * this = * this * num;
  return *this;
}

std::ostream & operator << (std::ostream & os,
  const String & mystring) {
  os << mystring.str_;
  return os;
}

std::istream & operator >> (std::istream & is, String & mystring) {
  const int kMaxSize = 100;
  static char buffer[kMaxSize];

  is.getline(buffer, kMaxSize);
  uint64_t size = strlen(buffer);
  if (size > 0) {
    if (size > mystring.size_) {
      delete[] mystring.str_;
      mystring.str_ = new char[size + 1];
      mystring.capacity_ = size;
    }
    strcpy(mystring.str_, buffer);
    mystring.size_ = size;
  }
  return is;
}

String String::Join(const std::vector < String > & vector) const {
  String res_string("");
  uint64_t i = 0;
  uint64_t v_size = vector.size();
  if (v_size == 0) {
    return res_string;
  }

  while (i != v_size) {
    res_string += vector[i];
    if (i != (v_size - 1)) {
      res_string = res_string + ( * this);
    }
    ++i;
  }
  return res_string;
}

uint64_t Find(String mystring,
  const String & delim, uint64_t start) {
  for (uint64_t i = start; i < mystring.size_; ++i) {
    if (mystring.str_[i] == delim.str_[0] && delim.size_ == 1) {
      return i;
    }
    if (mystring.str_[i] == delim.str_[0] && delim.size_ > 1) {
      if (mystring.str_[i + 1] == delim.str_[1]) {
        return i;
      }
    }
  }
  return -1;
}

String Substr(String mystring, uint64_t start, uint64_t end) {
  String tmp("");
  for (uint64_t i = start; i < end; ++i) {
    tmp += mystring[i];
  }
  return tmp;
}

std::vector < String > String::Split(const String & delim) {
  String empty_str = "";
  if (size_ < delim.size_) {
    return {
      empty_str
    };
  }

  std::vector < String > res;
  if (size_ == delim.size_) {
    res.push_back(empty_str);
    res.push_back(empty_str);
    return res;
  }

  uint64_t start = 0;
  uint64_t end = 0;
  String tmp;

  while ((end = Find( * this, delim, start)) != -1) {
    tmp = Substr( * this, start, end);
    start = end + delim.size_;
    res.push_back(tmp);
  }

  res.push_back(Substr( * this, start, size_));
  return res;
}

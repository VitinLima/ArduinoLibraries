#include "arduino.h"
#include "ByteStr.h"

//ByteStr::ByteStr(){
//  _length = 0;
//}

ByteStr::ByteStr(byte b){
  _length = 0;
  append(b);
}

//ByteStr::ByteStr(ByteStr str){
//  _length = 0;
//  append(str);
//}

int ByteStr::length(){
  return _length;
}

void ByteStr::clear(){
  _length = 0;
}

void ByteStr::remove(int index){
  if(index >= _length){
    return;
  }
  for(int i = index; i < _length-1; i++){
    _str[i] = _str[i+1];
  }
  _length--;
}

void ByteStr::append(byte newByte){
  _str[_length++] = newByte;
}

int ByteStr::lastIndexOf(byte byteToFind){
  for(int i = _length-1; i > -1; i--){
    if(_str[i] == byteToFind){
      return i;
    }
  }
  return -1;
}

byte ByteStr::last(){
  return _str[length()-1];
}

ByteStr ByteStr::last(int upTo){
  ByteStr outputStr;
  for(int i = length()-upTo; i < length(); i++){
    outputStr += _str[i];
  }
  return outputStr;
}

ByteStr ByteStr::subStr(int from, int upTo){
  ByteStr outputStr;
  for(int i = from; i < from+upTo && i < length(); i++){
    outputStr += _str[i];
  }
  return outputStr;
}

void ByteStr::operator+=(byte newByte){
  append(newByte);
}

void ByteStr::operator+=(int newInt){
  ByteStr tmp;
  tmp += (byte)(newInt%10 + 48);
  newInt /= 10;
  while(newInt > 0){
    tmp += (byte)(newInt%10 + 48);
    newInt /= 10;
  }
  for(int i = tmp.length()-1; i > -1; i--){
    append(tmp[i]);
  }
}

void ByteStr::operator+=(char newChar){
  append((byte)newChar);
}

void ByteStr::operator+=(ByteStr str){
  for(int i = 0; i < str.length(); i++){
    append(str[i]);
  }
}

ByteStr ByteStr::operator+(byte newByte){
  ByteStr newStr;
  newStr += *this;
  newStr += newByte;
  return newStr;
}

ByteStr ByteStr::operator+(int newInt){
  ByteStr str;
  str += *this;
  ByteStr tmp;
  tmp += (byte)(newInt%10 + 48);
  newInt /= 10;
  while(newInt > 0){
    tmp += (byte)(newInt%10 + 48);
    newInt /= 10;
  }
  for(int i = tmp.length()-1; i > -1; i--){
    str += tmp[i];
  }
  return str;
}

ByteStr ByteStr::operator+(char newChar){
  ByteStr newStr;
  newStr += *this;
  newStr += newChar;
  return newStr;
}

ByteStr ByteStr::operator+(ByteStr str){
  ByteStr newStr;
  newStr += *this;
  newStr += str;
  return newStr;
}

void ByteStr::operator=(byte newByte){
  clear();
  append(newByte);
}

void ByteStr::operator=(int newInt){
  clear();
  ByteStr tmp;
  tmp += (byte)(newInt%10 + 48);
  newInt /= 10;
  while(newInt > 0){
    tmp += (byte)(newInt%10 + 48);
    newInt /= 10;
  }
  for(int i = tmp.length()-1; i > -1; i--){
    append(tmp[i]);
  }
}

void ByteStr::operator=(char newChar){
  clear();
  append((byte)newChar);
}

void ByteStr::operator=(ByteStr str){
  clear();
  for(int i = 0; i < str.length(); i++){
    append(str[i]);
  }
}

void ByteStr::operator<<=(int shiftSize){
  ByteStr str;
  for(int i = 0; i < _length; i++){
    str += _str[i];
  }
  for(int i = 0; i < _length; i++){
    _str[i] = str[i]<<1;
  }
  for(int i = 0; i < _length-1; i++){
    _str[i] |= str[i+1]>>7;
  }
}
void ByteStr::operator>>=(int shiftSize){
  ByteStr str;
  for(int i = 0; i < _length; i++){
    str += _str[i];
  }
  for(int i = 0; i < _length; i++){
    _str[i] = str[i]>>1;
  }
  for(int i = 0; i < _length-1; i++){
    _str[i+1] |= str[i]<<7;
  }
}

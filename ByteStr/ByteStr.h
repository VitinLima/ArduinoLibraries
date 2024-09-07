#ifndef ByteStr_h
#define ByteStr_h

#include "arduino.h"

class ByteStr : public Printable{
  public:
    ByteStr(byte b);
    ByteStr(const char *cstr = ""){
      _length = 0;
      for(int i = 0; i < strlen(cstr); i++){
        _str[_length++] = cstr[i];
      }
    };
    
    int length();
    int bufferLength();
    void clear();
    
    void append(byte newByte);
    void remove(int index);
    void resizeToContent();
    int lastIndexOf(byte byteToFind);
    byte last();
    ByteStr last(int upTo);
    ByteStr subStr(int from, int upTo);
    
    void operator=(byte newByte);
    void operator=(int newInt);
    void operator=(char newChar);
    void operator=(ByteStr str);
    
    ByteStr operator+(byte newByte);
    ByteStr operator+(int newInt);
    ByteStr operator+(char newChar);
    ByteStr operator+(ByteStr str);
    
    void operator+=(byte newByte);
    void operator+=(int newInt);
    void operator+=(char newChar);
    void operator+=(ByteStr str);
    
    byte& operator[](int index){
      if(index >= _length){
        _str[_length++] = 0x00;
        return _str[_length-1];
      }
      return _str[index];
    }
    
    void operator>>=(int shiftSize);
    void operator<<=(int shiftSize);
    
    size_t printTo(Print& p) const{
      size_t r = 0;
      for(int i = 0; i < _length; i++){
        r += p.print((char)_str[i]);
      }
      return r;
    }
  private:
    byte _str[50];
    int _length;
};

#endif

//
//  BitArray.h
//  Quad-Mech
//
//  Created by Preston Raab on 11/10/22.
//

#ifndef BitArray_h
#define BitArray_h

#include "ArduinoSTL-master/vector.h"

class BitArray{
  public:
    unsigned char* data;
    unsigned char height, realColumns, width;
    
    BitArray(unsigned char rows, unsigned char columns): height(rows), realColumns(columns + 8 - columns % 8), width(columns){
        data = new unsigned char[(realColumns >> 3)*rows];
    }
    
    ~BitArray(){
        delete[] data;
    }
    
    bool get(unsigned char row, unsigned char column){
        unsigned char index = column % 8;
        return (data[realColumns * row + (column >> 3)] << (7 - index)) >> 7;
    }
    
    void set(unsigned char row, unsigned char column, bool value){
        unsigned char index = column % 8;
        unsigned char* d = &data[realColumns * row + (column >> 3)];
        bool currrentValue = (*d << (7 - index)) >> 7;
        if(currrentValue == value){
            return;
        }
        else{
            d += value << index;
        }
    }
};

#endif /* BitArray_h */

//
//  Writer.h
//  ImageMazeSolver
//
//  Created by Preston Raab on 3/14/20.
//  Copyright © 2020 Preston Raab. All rights reserved.
//

#ifndef Writer_h
#define Writer_h

#include "Path.hpp"

class Writer{
public:
    virtual void write(Path* p) = 0;
};

#endif /* Writer_h */

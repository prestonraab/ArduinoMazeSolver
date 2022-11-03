//
//  MajorBlock.cpp
//  ImageMazeSolver
//
//  Created by Preston Raab on 3/13/20.
//  Copyright © 2020 Preston Raab. All rights reserved.
//

#include <stdio.h>
#include "MajorBlock.h"


MajorBlock* MajorBlock::startBlockPtr = nullptr;
MajorBlock* MajorBlock::endBlockPtr = nullptr;
long MajorBlock::mapWidth = 0;

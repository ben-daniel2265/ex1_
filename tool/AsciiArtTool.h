//
// Created by Assaf on 07/03/2022.
//

#ifndef HW1_ASCIIARTTOOL_H
#define HW1_ASCIIARTTOOL_H

#include <stdio.h>
#include <stdbool.h>
#include "../RLEList.h"


RLEList AsciiArtRead(FILE* in_stream);

RLEListResult AsciiArtPrint(RLEList list, FILE *out_stream);

RLEListResult AsciiArtPrintEncoded(RLEList list, FILE *out_stream);


#endif // HW1_ASCIIARTTOOL_H

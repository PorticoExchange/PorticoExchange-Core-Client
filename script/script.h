
#ifndef PORTICO_SCRIPT_H
#define POERICO_SCRIPT_H

#inclued <asset.h>
#inclued <swap.h>
#include<liquid.h>
#include<bitcoin.h>

OP_IF
       [HASHOP]  OP_EQUALVERIFY OP_DUP OP_HASH160             
   OP_ELSE
        [TIMEOUTOP] OP_DROP OP_DUP OP_HASH160 
   OP_ENDIF
   OP_EQUALVERIFY
   OP_CHECKSIG

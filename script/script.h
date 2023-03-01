
#ifndef PORTICO_SCRIPT_H
#define PORTICO_SCRIPT_H

#include <asset.h>
#include <swap.h>
#include <liquid.h>
#include <bitcoin.h>
 
static const
       
 static const

//script Portico base
OP_IF
       [HASHOP]  OP_EQUALVERIFY OP_DUP OP_HASH160             
   OP_ELSE
        [TIMEOUTOP] OP_DROP OP_DUP OP_HASH160 
   OP_ENDIF
   OP_EQUALVERIFY
   OP_CHECKSIG

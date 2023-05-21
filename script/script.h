
#ifndef PORTICO_SCRIPT_H
#define PORTICO_SCRIPT_H

#include <asset.h>
#include <swap.h>
#include <element.h>
#include <bitcoin.h>
 
static const asset
       
static const swap 
 
static element 

static bitcoin 

//script Portico base
OP_IF
       [HASHOP]  OP_EQUALVERIFY OP_DUP OP_HASH160             
   OP_ELSE
        [TIMEOUTOP] OP_DROP OP_DUP OP_HASH160 
   OP_ENDIF
   OP_EQUALVERIFY
   OP_CHECKSIG

// stdafx.h : file di inclusione per file di inclusione di sistema standard
// o file di inclusione specifici del progetto utilizzati di frequente, ma
// modificati raramente
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <mutex>

typedef struct {
	int op1, op2;
	char opt;
	int score;
	std::vector<int> next;
}result;


// TODO: fare riferimento qui alle intestazioni aggiuntive richieste dal programma

#pragma once
#include "Service.h"
typedef struct {

	Service* service;
}Console;

void ui_delete(Console* console, char* command);
void ui_updateBot(Console* console, char* command);
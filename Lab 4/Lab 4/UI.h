#pragma once
#include "Service.h"
typedef struct {

	Service* service;
}Console;

int ui_delete(Console* console, char* command);
int ui_updateBot(Console* console, char* command);
int ui_add(Console* console, char* command);
void ui_list(Console* console, char* command);
void run(Console* console);
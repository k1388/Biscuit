#pragma once
#include "data_struct.h"
#include "iniio.h"

struct list_node* gen_list(
    char*               presetPath
);

int gen_sandbox(
    struct list_node*   head,
    char*               programPath
);





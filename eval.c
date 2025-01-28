#include "eval.h"

#include <stdio.h>
#include <tensorflow/c/c_api.h>

TF_Graph* model_graph = NULL;
TF_Session* session = NULL;
TF_Status* status = NULL;

void load(const char* modelPath) {
    
}

void eval() {
    printf("Hello from TensorFlow C library version %s\n", TF_Version());
}
#define MAX_MEMORY_SIZE 1024*1024*1024 // 1 Go


static unsigned char mem[MAX_MEMORY_SIZE] = {};
static int i = 0;

/*
Objective : allocate memory space
Input : Number of Bytes
Output : poiter to this allocated memory
*/
void * malloc(long int size){

    if (i + size > MAX_MEMORY_SIZE){
        return 0;
    }
    void *ptr = &mem[i];
    i+= size;
    return ptr;
}

/*
Objective : free memory space
Input : pointer to the memory to free
*/
void free(void *ptr){
    // Do nothing
}

/*
Objective : clear memory space
Input : None
*/
void clear_memory(){
    i = 0;
}

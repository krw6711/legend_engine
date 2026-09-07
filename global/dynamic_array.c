// #include "./dynamic_array.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <stdbool.h>

// int* new_int_array(size_t len){
//     void *raw_mem = calloc(len, sizeof(int));
//     if(raw_mem == NULL){
//         printf("out of memory");
//         return NULL;
//     }
//     return raw_mem;
// }

// DArray new_array_info(int *array, unsigned int len){
//     return (DArray){
//         .array = array,
//         .length = len,
//         .filled = 0,
//         .cursor = 0
//     };
// }

// DArray new_darray(size_t len){
//     return new_array_info(new_int_array(len), (int)len);
// }

// int expand(DArray *buf)
// {
//     size_t new_size = ((size_t)buf->length * 2) * sizeof(int);
//     void* new_ptr = realloc(buf->array, new_size);
//     if(new_ptr ==  NULL){
//         printf("cant expand, oout of memory");
//         return 1;
//     }
//     buf->array = new_ptr;
//     buf->length*= 2;
//     return 0;
// }

// int collapse(DArray *buf, size_t len)
// {
//     if(len == 0){
//         printf("can not decrease by nothing");
//         return 1;
//     }
//     size_t new_size = ((size_t)buf->length - len) * sizeof(int);
//     void* new_ptr = realloc(buf->array, new_size);
//     if(new_ptr ==  NULL){
//         printf("cant expand, oout of memory");
//         return 1;
//     }
//     buf->array = new_ptr;
//     buf->length-= (int)len;
//     return 0;
// }

// int d_insert(DArray *buf, void item){
//     if(buf->length == buf->filled){
//         if(expand(buf)){
//             printf("can not insert, no space");
//             return 1;
//         }
//     }
//     buf->array[buf->cursor] = item;
//     buf->cursor++;
//     buf->filled++;
//     return 0;
// }

// int d_remove(DArray *buf, int index) // 2
// {
//     if(index < 0 && index < buf->length){
//         printf("out of bounds");
//         return 1;
//     }
//     // [10 ,20, (30), 40]
//     //  0   1    2    3
//     for(int i = index; i < (buf->filled - 1); i++){
//         // index 2 = index 3
//         buf->array[i] = buf->array[i + 1];
//     }
//     // decrease the size to delete index 3
//     collapse(buf, 1);
//     buf->filled--;
//     buf->cursor--;
//     return 0;
// }

// // int d_index_of(DArray *buf, void* item)
// // {
// //     for (int i = 0; i < buf->filled; i++) {
// //         if((buf->array)+i == item) return i;
// //     }
// //     return -1;
// // }

// // void print_darray(DArray *buf){
// //     for(int i = 0; i < buf->filled; i++){
// //         printf("%d\n", buf->array[i]);
// //     }
// // }

// int d_get_value(DArray *buf, int index)
// {
//     if(index >= 0 && index < buf->length) return buf->array[index];
//     return -1;
// }

// int d_edit_value(DArray *buf, int index, int value){
//     if(index < 0 && index < buf->length) return 1;
//     buf->array[index] = value;
//     return 0;
// }

// void SDL_free_darray(DArray *buf)
// {
//     SDL_free(buf->array);
//     buf->array = NULL;
// }
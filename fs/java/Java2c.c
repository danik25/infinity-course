#include <stdio.h> /*printf*/
#include <stdlib.h> /*calloc*/

#define FUNC_NUM 2

enum PLACE {CTOR, TO_STRING};


typedef void (*(vtable_t)[])();
typedef void (*vtable_func_t) ();
typedef struct class metadata_t;


struct class{
    vtable_t *(vtable);
    char* name;
    size_t size;
    metadata_t *super;
};

typedef struct object{
    metadata_t *class;
}object_t;

typedef struct Animal{
    object_t object;
    char* name;
    int age;
}animal_t;

/*declerations*/
void Ctor();
char* ToString(object_t * object);
/*-----------*/

vtable_t Classvtable = {
    Ctor,
    (vtable_func_t)ToString
};

metadata_t class_object = {
    &Classvtable,
    "Object",
    sizeof(object_t),
    NULL
};

object_t* alloc(metadata_t *class)
{
    object_t *ret = (object_t*)calloc(1, class->size);
    ret->class = class;
    ((*(class->vtable))[CTOR])();

    return(ret);    
}

/******** vtable ********/

void Ctor()
{
    printf("ctor!!\n");
}

char* ToString(object_t * object)
{
	return(object->class->name);
}

/*=============main=============*/

int main()
{
    object_t* obj = alloc(&class_object);
    /*printf("%s\n", (char *(*)()(*(obj->class->vtable))[TO_STRING])());*/
    char *(*ptrToString)()  = (char *(*)(object_t *))((*(obj->class->vtable))[TO_STRING]);
    printf("%s\n", ptrToString(obj));
    return(0);
}
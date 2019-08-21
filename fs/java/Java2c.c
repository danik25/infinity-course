#include <stdio.h> /*printf*/
#include <stdlib.h> /*calloc*/
#include <string.h> /*strcpy*/


typedef void (*(vtable_t)[])();
typedef void (*vtable_func_t) ();

enum FunctionPlacement {TO_STRING, SAY_HELLO, GET_NUM_MASTERS, FINALIZE};

typedef struct class metadata_t;
char String[1024];

struct class{
    vtable_t *(vtable);
    char* name;
    size_t size;
    metadata_t *super;
};

typedef struct object{
    metadata_t *class;
}object_t;

/***********************************************************************************/

/***********************************************************************************/
/*                                     structs                                     */
/***********************************************************************************/

typedef struct Animal{
    object_t object;
    int num_legs;
	int num_masters;
	int ID;
}animal_t;

typedef struct Dog{
    animal_t animal;
    int num_legs;
}dog_t;

typedef struct Cat{
    animal_t animal;
    char colors[20];
	int num_masters;
}cat_t;

typedef struct LegendaryAnimal{
    cat_t cat;
}lag_t;

/***********************************************************************************/

/***********************************************************************************/
/*                            global variables (static)                            */
/***********************************************************************************/

int animal_counter = 0;
static void CreateArray();
void foo(animal_t* a);

/***********************************************************************************/
/*                              functions declerations                             */
/***********************************************************************************/

/*************** constructors ***************/
/* object */
void object_Ctor(object_t* obj);

/* animal */
void animal_Ctor(animal_t* obj);
void animal_Ctor2(animal_t* obj, int num_masters);

/* dog */
void dog_Ctor(dog_t* dog);

/* cat */
void cat_Ctor(cat_t* cat);
void cat_Ctor2(cat_t* cat, char* colors);

/* legendary */
void lag_Ctor(lag_t* lag);

/*************** vtable functions *************/
/* object */
char* object_ToString(object_t * this);
void object_finalize(object_t * this);

/* animal */
char* animal_ToString(animal_t * this);
void animal_sayHello(animal_t * this);
void animal_showCounter(); /* static */
int animal_getNumMasters(animal_t * this);
void animal_finalize(animal_t * this);

/* dog */
char* dog_ToString(dog_t * this);
void dog_sayHello(dog_t * this);
void dog_finalize(dog_t * this);

/* cat */
char* cat_ToString(cat_t * this);
void cat_finalize(cat_t * this);

/* legendary */
char* lag_ToString(cat_t * this);
void lag_sayHello(dog_t * this);
void lag_finalize(lag_t * this);

/****************initializers ****************/ 
/* animal */
void animal_StaticInitializers();
void animal_initialization(animal_t* anm);

/* dog */
void dog_StaticInitializers();
void dog_initialization(dog_t* dog);

/* cat */
void cat_StaticInitializers();
void cat_initialization(cat_t* cat);

/* legendary */
void lag_StaticInitializers();

/***********************************************************************************/


/*============================= vtables initialization =============================*/
/* object */
vtable_t Classvtable = {
    (vtable_func_t)object_ToString
};

/* animal */
vtable_t Animalvtable = {
    (vtable_func_t)animal_ToString, /* override */
    (vtable_func_t)animal_sayHello,
    (vtable_func_t)animal_getNumMasters,
    (vtable_func_t)animal_finalize /* override */
};

/* dog */
vtable_t Dogvtable = {
    (vtable_func_t)dog_ToString, /* override */
    (vtable_func_t)dog_sayHello, /* override */
    (vtable_func_t)animal_getNumMasters,
    (vtable_func_t)dog_finalize /* override */
};

/* cat */
vtable_t Catvtable = {
    (vtable_func_t)cat_ToString, /* override */
    (vtable_func_t)animal_sayHello, 
    (vtable_func_t)animal_getNumMasters,
    (vtable_func_t)cat_finalize /* override */
};

/* legendary */
vtable_t Lagvtable = {
    (vtable_func_t)lag_ToString, /* override */
    (vtable_func_t)lag_sayHello, /* override */
    (vtable_func_t)animal_getNumMasters,
    (vtable_func_t)lag_finalize /* override */
};

/*==================================================================================*/

/*================================== class objects =================================*/
/* object */
metadata_t object_class_object = {
    &Classvtable,
    "Object",
    sizeof(object_t),
    NULL
};

/* animal */
metadata_t animal_class_object = {
    &Animalvtable,
    "Animal",
    sizeof(animal_t),
    &object_class_object
};

/* dog */
metadata_t dog_class_object = {
    &Dogvtable,
    "Dog",
    sizeof(dog_t),
    &animal_class_object
};

/* cat */
metadata_t cat_class_object = {
    &Catvtable,
    "Cat",
    sizeof(cat_t),
    &animal_class_object
};

/* legendary */
metadata_t lag_class_object = {
    &Lagvtable,
    "Legendary",
    sizeof(lag_t),
    &cat_class_object
};

/*==================================================================================*/

object_t* alloc(metadata_t *class)
{
    object_t *ret = (object_t*)calloc(1, class->size);
    ret->class = class;

    return(ret);    
}

/***********************************************************************************/
/*                                   constructors                                  */
/***********************************************************************************/
/* object */
void object_Ctor(object_t* obj)
{
    (void)obj;
}

/* animal */
void animal_Ctor(animal_t* anm)
{
    object_Ctor((object_t*)anm);

    animal_initialization(anm);

    printf("Animal Ctor\n");
	anm->ID = ++animal_counter;
    
    (*(anm->object.class->vtable))[SAY_HELLO](anm); /*animal_sayHello(anm);*/
	animal_showCounter();

    printf("%s\n", ((char*(*)(animal_t*))((*(anm->object.class->vtable))[TO_STRING]))(anm));
    printf("%s\n", ((char*(*)(object_t *))((*(object_class_object.vtable))[TO_STRING]))((object_t*)anm));
}

void animal_Ctor2(animal_t* anm, int num_masters)
{
    object_Ctor((object_t*)anm);

    animal_initialization(anm);
    printf("Animal Ctor int\n");
	anm->ID = ++animal_counter;
	anm->num_masters = num_masters;
}

/* dog */
void dog_Ctor(dog_t* dog)
{
    animal_Ctor2((animal_t*)dog, 2);
    dog_initialization(dog);
	printf("Dog Ctor\n");
}

/* cat */
void cat_Ctor(cat_t* cat)
{
    cat_Ctor2(cat, "black");
    printf("Cat Ctor\n");
	cat->num_masters = 2;
}

void cat_Ctor2(cat_t* cat, char* colors)
{
    animal_Ctor((animal_t*)cat);
    cat_initialization(cat);
    strcpy(cat->colors, colors);
	printf("Cat Ctor with color: %s\n", cat->colors);
}

/* legendary */
void lag_Ctor(lag_t* lag)
{
    cat_Ctor((cat_t*) lag);
    printf("Legendary Ctor\n");
}

/***********************************************************************************/
/*                                  initializers                                   */
/***********************************************************************************/
/* animal */
void animal_initialization(animal_t* anm)
{
    printf("Instance initialization block Animal\n");
    anm->num_legs = 5;
    anm->num_masters = 1;
}

/* dog */
void dog_initialization(dog_t* dog)
{
    printf("Instance initialization block Dog\n");
    dog->num_legs = 4;
}

/* cat */
void cat_initialization(cat_t* cat)
{
    cat->num_masters = 5;
}
/***********************************************************************************/

/***********************************************************************************/
/*                               static initializers                               */
/***********************************************************************************/
/* animal */
void animal_StaticInitializers()
{
    printf("Static block Animal 1\n");
    printf("Static block Animal 2\n");
}

/* dog */
void dog_StaticInitializers()
{
    printf("Static block Dog\n");
}

/* cat */
void cat_StaticInitializers()
{
    printf("Static block Cat\n");
}

/* legendary */
void lag_StaticInitializers()
{
    printf("Static block Legendary Animal\n");
}

/***********************************************************************************/
/*                           vtable's functions definition                         */
/***********************************************************************************/

/* object */
char* object_ToString(object_t * this)
{
    sprintf(String, "%s@%p\n", this->class->name, (void*)this);
	return(String);
}

void object_finalize(object_t * this)
{
	(void)this;
}

/* animal */
char* animal_ToString(animal_t * this)
{
    sprintf(String, "%s %d\n", "Animal with ID:", this->ID);
	return(String);
}

void animal_sayHello(animal_t * this)
{
    printf("Animal Hello!\n");
	printf("I have %d legs\n", this->num_legs);
}

void animal_showCounter() /* static */
{
	printf("%d\n", animal_counter);
}

int animal_getNumMasters(animal_t * this)
{
	return (this->num_masters);
}

void animal_finalize(animal_t * this)
{
    printf("finalize Animal with ID: %d\n", this->ID);
    ((void*(*)(animal_t*))((*(object_class_object.vtable))[FINALIZE]))(this);
}

/* dog */
char* dog_ToString(dog_t * this)
{
    sprintf(String, "%s %d\n", "Dog with ID: ", this->animal.ID);
	return(String);
}

void dog_sayHello(dog_t * this)
{
    printf("Dog Hello!\n");
	printf("I have %d legs\n", this->num_legs);
}

void dog_finalize(dog_t * this)
{
    printf("finalize Dog with ID: %d\n", this->animal.ID);
    ((void*(*)(dog_t*))((*(animal_class_object.vtable))[FINALIZE]))(this);

}

/* cat */
char* cat_ToString(cat_t * this)
{
    sprintf(String, "%s %d\n", "Cat with ID: ", this->animal.ID);
	return(String);
}

void cat_finalize(cat_t * this)
{
    printf("finalize Cat with ID: %d\n", this->animal.ID);
    ((void*(*)(cat_t*))((*(animal_class_object.vtable))[FINALIZE]))(this);

}

/* legendary */
char* lag_ToString(cat_t * this)
{
    sprintf(String, "%s %d\n", "LegendaryAnimal with ID: \n", this->animal.ID);
	return(String);
}

void lag_sayHello(dog_t * this)
{
    (void)this;
    printf("Legendary Hello!\n");
}

void lag_finalize(lag_t * this)
{
    printf("finalize LegendaryAnimal with ID: %d\n", this->cat.animal.ID);
    ((void*(*)(lag_t*))((*(cat_class_object.vtable))[FINALIZE]))(this);

}

/***********************************************************************************/
/***** static functions ****/
void foo(animal_t* a)
{
    printf("%s\n", ((char*(*)(animal_t*))((*(a->object.class->vtable))[TO_STRING]))(a));
}

/*============= main =============*/

int main()
{
    object_t* animal = NULL;
    object_t* dog = NULL; 
    object_t* cat = NULL;
    object_t* lag = NULL;

    /* animal */
    animal = alloc(&animal_class_object);
    animal_StaticInitializers();
    animal_Ctor((animal_t*)animal);
    printf("\n");

    /* dog */
    dog = alloc(&dog_class_object);
    dog_StaticInitializers();
    dog_Ctor((dog_t*)dog);
    printf("\n");

    /* cat */
    cat = alloc(&cat_class_object);
    cat_StaticInitializers();
    cat_Ctor((cat_t*)cat);
    printf("\n");

    /* legendary */
    lag = alloc(&lag_class_object);
    lag_StaticInitializers();
    lag_Ctor((lag_t*)lag);
    printf("\n");

    animal_showCounter();
    printf("\n");

    printf("%d\n",((animal_t*)animal)->ID);
	printf("%d\n",((animal_t*)dog)->ID);
	printf("%d\n",((animal_t*)cat)->ID);
	printf("%d\n",((animal_t*)lag)->ID);

    CreateArray();

    free(animal);
    free(dog);
    free(cat);
    free(lag);

    return(0);
}

/*----------------------------------------------------------------------*/

static void CreateArray()
{
    object_t* dog = NULL; 
    object_t* cat1 = NULL;
    object_t* cat2 = NULL;
    object_t* lag = NULL;
    object_t* animal = NULL;

    animal_t* array[5];

    int i = 0;

    printf("array:\n");

    /* dog */
    dog = alloc(&dog_class_object);
    dog_Ctor((dog_t*)dog);
    printf("\n");

    /* cat 1*/
    cat1 = alloc(&cat_class_object);
    cat_Ctor((cat_t*)cat1);
    printf("\n");

    /* cat 2*/
    cat2 = alloc(&cat_class_object);
    cat_Ctor2((cat_t*)cat2, "white");
    printf("\n");

    /* legendary */
    lag = alloc(&lag_class_object);
    lag_Ctor((lag_t*)lag);
    printf("\n");

    /* animal */
    animal = alloc(&animal_class_object);
    animal_Ctor((animal_t*)animal);
    printf("\n");

    array[0] = (animal_t*)dog;
    array[1] = (animal_t*)cat1;
    array[2] = (animal_t*)cat2;
    array[3] = (animal_t*)lag;
    array[4] = (animal_t*)animal;
	
    for(i = 0; i < 5; ++i)
    {
		(*(array[i]->object.class->vtable))[SAY_HELLO](array[i]);
        printf("%d\n", ((int(*)(animal_t*))((*(array[i]->object.class->vtable))[GET_NUM_MASTERS]))(array[i]));            
	}

    for(i = 0; i < 5; ++i)
    {
		foo(array[i]);
	}

    /* free */
    for(i = 4; i >= 0; --i)
    {
		free(array[i]);
	}
}

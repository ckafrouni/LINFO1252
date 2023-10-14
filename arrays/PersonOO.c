#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person_t person_t;

struct person_t
{
    char *firstName;
    char *lastName;
    int age;
};

char *getFirstName(person_t *this)
{
    return this->firstName;
}

char *getLastName(person_t *this)
{
    return this->lastName;
}

int getAge(person_t *this)
{
    return this->age;
}

char *getFullName(person_t *this)
{
    char *fullName = (char *)malloc(strlen(this->firstName) + strlen(this->lastName) + 2);
    strcpy(fullName, this->firstName);
    strcat(fullName, " ");
    strcat(fullName, this->lastName);
    return fullName;
}

void _free(person_t *this)
{
    free(this->firstName);
    free(this->lastName);
    free(this);
}

struct PersonMethods
{
    char *(*getFirstName)(person_t *);
    char *(*getLastName)(person_t *);
    int (*getAge)(person_t *);
    char *(*getFullName)(person_t *);
    void (*free)(person_t *);
} Person = {
    .getFirstName = getFirstName,
    .getLastName = getLastName,
    .getAge = getAge,
    .getFullName = getFullName,
    .free = _free
};


person_t *newPerson(char *firstName, char *lastName, int age)
{
    person_t *person = (person_t *)malloc(sizeof(person_t));
    person->firstName = strdup(firstName);
    person->lastName = strdup(lastName);
    person->age = age;

    return person;
}

int main(int argc, char **argv)
{
    person_t *p1 = newPerson("John", "Doe", 19);
    

    printf("First name = %s\n", Person.getFirstName(p1));
    printf("Last name = %s\n", Person.getLastName(p1));
    printf("Full name = %s\n", Person.getFullName(p1));
    printf("Age = %d\n", Person.getAge(p1));

    Person.free(p1);

    return EXIT_SUCCESS;
}
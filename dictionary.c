/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include<stdbool.h>
#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH+1];
    struct node* next;    
}
node;

node* HashTable[SIZE] = {0};

//hash function---source: reddit.com
int hash(char* needs_hashing)
{
    unsigned int hash_num = 0;
    for (int i=0, n=strlen(needs_hashing); i<n; i++)
        hash_num = (hash_num << 2) ^ needs_hashing[i];
    return hash_num % SIZE;
}
unsigned int count=0;



/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int len=strlen(word);
    char word_copy[len+1];
    for(int i=0;i<len;i++)
    {
        word_copy[i]=tolower(word[i]);//convert every letter in word to lowercase which will remove the prob. of some uppercase letters
    }
    word_copy[len]='\0';
    
    int h=hash(word_copy[len]);
    node* cursor= HashTable[h];
    
    while(cursor!=NULL)
    {
        if(strcmp(cursor->word,word_copy==0))
        return true;
        
        else
        cursor=cursor->next;
    }
    return false;
    
    
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    bool isLoaded = false;
    FILE* fp;
    fp=fopen(dictionary,"r");
    if(fp==NULL)
    {
        return false;
    }
    
    while(!feof(fp))
    {
        node* new_node = malloc(sizeof(node));
        if(new_node==NULL)
        {
            printf("memory not allocated\n");
            return false;
        }
        
        fscanf(fp,"%s",new_node->word);
        new_node->next=NULL;
        count++;
        
        int h = hash(new_node->word);
        node* head = HashTable[h];
        if(head==NULL)
        {
            HashTable[h]=new_node;
        }
        else
        {
            new_node->next = HashTable[h];
            HashTable[h]=new_node;
        }
    }
    isLoaded=true;
    fclose(fp);
    return true;
    
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if(isLoaded)
    {
        return count;
    }
    else
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}

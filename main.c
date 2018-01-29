#include "test_suite.h"
#include "rb_node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void readFile(FILE* inFile,struct rb_node * root){


    size_t chunkSize=1*sizeof(char);//we read 1 character at a time
    char *buf = malloc(chunkSize);
    char word[255];//our tempory word

    int wordLen=0;


    if (inFile) {

        while ((fread(buf, 1, chunkSize, inFile)) > 0) {



            if(isspace(buf[0])) {

                word[wordLen] = '\0';
                char *wordToInsert = malloc((1 + wordLen) * sizeof(char));
                strcpy(wordToInsert, word);

                struct rb_node *newNode = malloc(sizeof(struct rb_node));
                newNode->word = wordToInsert;
                newNode->parent=NULL;
                /*
                 * If the node that we are trying to insert already exists, then we free the node we
                 * just created
                 */
                //printf(word);

                rb_insert(root,newNode);
                rb_restore_after_insert(root,newNode);




                wordLen=0;
            }else{

                word[wordLen]=(char)tolower((int)buf[0]);
                wordLen++;
            }


        }
        fclose(inFile);
    }

}


void writeFile(FILE *outFile,struct rb_node * root){

    if(root->word!=NULL){

        writeFile(outFile,root->left);//We first go to the left

        fprintf(outFile,root->word);//we print our word to the file
        fprintf(outFile,": "); //then the ':'
        fprintf(outFile,"%d",root->count);//then the count
        fprintf(outFile,"\n");//Then move to the next line

        writeFile(outFile,root->right);//We then go to the right node
    }
}

/* main */
int main(int argc, char *argv[]) {
    struct rb_node *root = malloc(sizeof(struct rb_node));
    root->parent=NULL;
    FILE* inputFile=fopen("C:\\Users\\Peter\\ClionProjects\\msl-clang-002\\data\\words.shakespeare.txt","r");
    readFile(inputFile,root);
    //fclose(inputFile);
    FILE* outFile=fopen("C:\\Users\\Peter\\ClionProjects\\msl-clang-002\\data\\output.txt","w");
    writeFile(outFile,root);
   // fclose(outFile);
}

#include <stdio.h>
#include "StrList.h"
#include <string.h>


int main()
{

    int user_choice=-1;

    int ans=0;

    struct _StrList* my_list;
    my_list=StrList_alloc();


    while (user_choice!=0)
    {
        printf("choose an integer between 0 and 13!\n");
        scanf("%d",&user_choice);
        //switch-case:
        switch (user_choice)
        {
            case 0: // V
                break;
            case 1: // V

                printf("choose the number of words you want to enter:\n");
                int num_of_words = 0;

                scanf("%d", &num_of_words);

                for (int i = 0; i < num_of_words; i++)
                {
                    char* word = (char*)malloc(sizeof(char) * 100); // assuming max word length is 100
                    if (word == NULL)
                    {
                        printf("Memory allocation failed!\n");
                        break;
                    }
                    scanf("%s", word);

                    char* resized_word_case1 = (char*)realloc(word, sizeof(char) * (strlen(word) + 1)); // +1 for null terminator
                    if (resized_word_case1 == NULL) {
                        printf("Memory reallocation failed!\n");
                        break;
                    }
                    word = resized_word_case1; // update word pointer
                    StrList_insertLast(my_list,word);

                }
                break;
            case 2: // V

                printf("choose index to insert to:\n");
                int index_case2 = 0;
                scanf("%d", &index_case2);

                printf("choose a word to insert:\n");
                char* word = (char*)malloc(sizeof(char) * 100); // assuming max word length is 100
                if (word == NULL)
                {
                    printf("Memory allocation failed!\n");
                    break;
                }
                scanf("%s", word);

                char* resized_word_case2 = (char*)realloc(word, sizeof(char) * (strlen(word) + 1)); // +1 for null terminator
                if (resized_word_case2 == NULL) {
                    printf("Memory reallocation failed!\n");
                    break;
                }
                word = resized_word_case2; // update word pointer
                StrList_insertAt(my_list, word, index_case2);
                break;

            case 3: // V
                StrList_print(my_list);
                break;
            case 4: // V
                printf("%d\n",(int)StrList_size(my_list));
                break;
            case 5: // V
                printf("choose index to print:\n");
                int index_case5=0;
                scanf("%d",&index_case5);
                StrList_printAt(my_list,index_case5);
                break;
            case 6: // V

                printf("%d\n",StrList_printLen(my_list));

                break;
            case 7: // V
                printf("enter the word you wish to check how many times it appears in the list:\n");
                char* word_to_check_appearance_case7 = (char*)malloc(sizeof(char) * 100); // assuming max word length is 100
                if (word_to_check_appearance_case7 == NULL)
                {
                    printf("Memory allocation failed!\n");
                    break;
                }
                scanf("%s", word_to_check_appearance_case7);

                char* resized_word_case7 = (char*)realloc(word_to_check_appearance_case7, sizeof(char) * (strlen(word_to_check_appearance_case7) + 1)); // +1 for null terminator
                if (resized_word_case7 == NULL) {
                    printf("Memory reallocation failed!\n");
                    break;
                }
                word_to_check_appearance_case7 = resized_word_case7; // update word pointer

                printf("%d\n",StrList_count(my_list,word_to_check_appearance_case7));
                free(word_to_check_appearance_case7);
                break;

            case 8: // X
                printf("enter the word you wish to delete all her appearances in the list:\n");
                char* word_to_check_appearance_case8 = (char*)malloc(sizeof(char) * 100); // assuming max word length is 100
                if (word_to_check_appearance_case8 == NULL)
                {
                    printf("Memory allocation failed!\n");
                    break;
                }
                scanf("%s", word_to_check_appearance_case8);

                char* resized_word_case8 = (char*)realloc(word_to_check_appearance_case8, sizeof(char) * (strlen(word_to_check_appearance_case8) + 1)); // +1 for null terminator
                if (resized_word_case8 == NULL)
                {
                    printf("Memory reallocation failed!\n");
                    break;
                }
                word_to_check_appearance_case8 = resized_word_case8; // update word pointer
                StrList_remove(my_list, word_to_check_appearance_case8);
                free(word_to_check_appearance_case8);
                break;


            case 9: // V
                printf("choose index to remove: ");
                int index_case9=0;
                scanf("%d",&index_case9);
                StrList_removeAt(my_list,index_case9);
                break;

            case 10: // V
                StrList_reverse(my_list);
                break;
            case 11: // V
                printf("");
                int size_list_case11=(int)StrList_size(my_list);
                for (int i = 0; i < size_list_case11; i++)
                {
                    StrList_removeAt(my_list,0);
                }
                break;
            case 12: // V
                StrList_sort(my_list);
                break;
            case 13: // V
                ans=StrList_isSorted(my_list);
                if(ans==0)
                {
                    printf("false\n");
                }
                else
                {
                    printf("true\n");
                }

                break;
            default:
                printf("Enter an integer between 0 and 13!");
                break;
        }

    }

    free(my_list);

    return 0;
}

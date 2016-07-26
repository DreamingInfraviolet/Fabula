#include <cstdio.h>
#include "fabula.h"

const char* source = "scene hi { \"Yo\" \"Hellooo\" }";

void PrintChoices(ChoiceList* choices)
{
    Choice* choice;
    int counter = 1;
    for(choice = choices->choices;
        choices < choices->choices+choices->choiceCount;
        ++choice)
    {
        printf("Choice %i: %s - %s\n",
            counter++,
            choice->content.head,
            choice->content.body);
    }
}

void PrintScene(FScene* scene)
{
    printf("Scene: %s\n", scene->name.str);
    printf("Header: %s\n", scene->content.head);
    printf("Content: %s\n\n", scene->content.body);
    PrintChoices(&scene->choiceList);
    printf("**************************************************\n\n");
}

/* Returns the 0-indexed choice specified by the user in 1-indexed format. */
int GetChoiceSelection(int choiceCount)
{
    int scanCount, value;
    do
    {
        scanCount = scanf("%i", &value);
    } while(scanCount==0 || value < 1 || value > choiceCount);
    return value-1;
}

int main()
{
    //Initialise
    if(!FInit())
    {
        printf("Unable to initialise Fabula.\n");
        return 1;
    }

    //Parse
    if(!FParseString(source))
    {
        printf("Unable to parse the string.\n");
        return 2;
    }

    /*Main loop*/
    FScene* scene;

    /*The current scene in this case will only be null if there are no
     * scenes, or if we have reached the end.
       An ending scene has no choices and no default target.
       */
       
    while((scene = FCurrentScene()) != 0)
    {
        PrintScene(scene);
        if(scene->choices.count==0)
            FCurrentScene(scene->choiceList.defaultTarget);
        else
            FCurrentScene(scene->choiceList.choices[
                            GetChoiceSelection(scene->choiceList.count)]
                         );
    }

    //End
    FShutdown();
}
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string txt);
int count_sentences(string txt);
int count_score(int count_sentences, int count_words, int count_letters);

int main(void)
{

    string txt = get_string("Text: ");

    int s = count_sentences(txt);
    int w = count_words(txt);
    int l = count_letters(txt);
    int sc = count_score(s, w, l);

    if (sc < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (sc >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", sc);
    }
}
// count letters
int count_letters(string txt)
{
    int letters = 0;
    for (int i = 0, len = strlen(txt); i < len; i++)
    {
        if (isalpha(txt[i]))
        {
            letters = letters + 1;
        }
    }
    return letters;
}
// count words
int count_words(string txt)
{
    int words = 1;
    for (int i = 0, len = strlen(txt); i < len; i++)
    {
        if (isspace(txt[i]))
        {
            words = words + 1;
        }
    }
    return words;
}
// count sentences
int count_sentences(string txt)
{
    int sentences = 0;
    for (int i = 0, len = strlen(txt); i < len; i++)
    {
        if (txt[i] == '.' || txt[i] == '?' || txt[i] == '!')
        {
            sentences = sentences + 1;
        }
    }
    return sentences;
}
// count the grade score
int count_score(int sentences, int words, int letters)
{
    return (round(0.0588 * (((float)letters * 100) / (float)words) - 0.296 * (((float)sentences * 100) / (float)words) - 15.8));
}
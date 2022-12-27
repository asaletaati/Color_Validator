/*
Asal Etaati, final project of CS50X-Harvard
This project is used to help front-end developers or learners who want to know more about color codes.
This Command Line Argument is made for CS50X-Harvard final project, not for other purposes!
It's a command-line argument written in C.
Plz, Execute this command at the terminal prompt: ./final color_coding_type_number
argv[0] = Usage or "final"
argv[1] = color_coding_type_number
KEYS for color_coding_type_number: 1,2,3
1: verifying a HEX code, for example: #FFFFFF
2: verifying an RGB code, for example: rgb(255, 255, 255)
3: verifying a color name in English, for example: White
*/

// libraries 
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>


// Function declaration
bool HEX();
bool RGB();
bool EN_WORD();


// COMMAND LINE ARGUMENT 
int main(int argc, string argv[])
{
    // checking any possible mistakes that users can make in data entry
    if (argc != 2) // If the input does not contain exactly 2 commands, return 1
    {
        printf("./usage color_coding_type_number\n( Input must contain exactly two commands )\n");
        return 1;
    }
  
    string s = argv[1];
  
    if (strlen(s) != 1) // When the input is a 2-char(digit) number like 23, the program returns 1. The program can return 0, just when the input is a single-char(digit) number, such as 2 or 3
    {
        printf("color_coding_type_number must be 1 or 2 or 3\n1- HEX 2- RGB 3- Names of colors in English\n");
        return 1;
    }
  
    if (!isdigit(s[0])) // If argv[1] (color_coding_type_number) is'nt an integer, return 1
    {
        printf("color_coding_type_number must be an integer\n");
        return 1;
    }

    int n = atoi(&s[0]); // converting argv[1] to an integer
  
    if (n > 3 || n < 1) // check if argv[1] is 1 or 2 or 3
    {
        printf("color_coding_type_number just can be 1 or 2 or 3\n");
        return 1;
    }
    // End of checking any possible mistakes that users can make in data entry


    if (atoi(&s[0]) == 1) // If color_coding_type_number = HEX code, implement this function
    {
        HEX();

    }
    else if (atoi(&s[0]) == 2) // If color_coding_type_number = RGB code, implement this function
    {
        RGB();
    }
    else // If color_coding_type_number = Names of colors in English, implement this function
    {
        EN_WORD();
    }

    return 0;
}




// FUNCTIONS:
/*
bool HEX:
****
Some situations in a HEX code, (to make sure it is a HEX code):
1- A HEX code contains exactly 6 characters.
2- A HEX code can only consist of numbers or alphabets.
3- The numbers in a hexadecimal code can be: 1 2 3 4 5 6 7 8 9 A B C D E F, so we cannot have an alphabet greater than F.
**** 
*/
bool HEX(void)
{
    string  x = get_string("Wanna verify a HEX code? Then enter your HEX code:\n #");
    for (int i = 0; i < strlen(x); i++)
    {
        if (strlen(x) != 6 || (!isalpha(x[i]) && !isdigit(x[i])) || (isalpha(x[i]) 
                && (toupper(x[i]) > 
                    'F'))) // ****
        {
            printf("Sorry this is'nt a HEX code! :(\n");
            return false;
        }
    }
    printf("Yep! This is a HEX code :)\n");
    return true;
}



/*
An RGB code consists of 3 elements (red, green and blue).
We cannot have more than 255 of each color!
*/
bool RGB(void)
{
    printf("Wanna verify an RGB? Then enter your RGB code:) (Red, Green, Blue)\n");
    for (int i = 0; i < 3; i++)
    {
        string color[] = {"Red", "Green", "Blue"}; // list of RGB colors
        unsigned int x = get_int("Plz, enter the %dth color of your RGB code (that specifies the amount of %s you wanna have):\n", i + 1, color[i]);
        if (x > 255)
        {
            printf("Sorry this is'nt an RGB code:(\n");
            return false;
        }
    }
    printf("Yep! This is an RGB code:)\n");
    return true;
}



/*
If the input is a color name in English!
I created a file that contains a list of color names
Be careful, I have not written all the colors that exist in the world!
Only my syntax is important. And you can add more color names if you desire.
This function searches for the given color
If it exists in the file, it will return true and tell you that it is a valid color name in English!
If it doesn't exist in the file, it will return false and tell you that the color name is not valid in English!
*/
bool EN_WORD(void)
{
    printf("Wanna varify a color name in English? Then enter your considered color name: ");
    FILE *file = fopen("colors.txt", "r"); // open the file
    if (file == NULL) // If the txt file does not exist, print this massage, close the file and return false
    {
        printf("The txt file is not found!\n");
        fclose(file);
        return false;
    }
    
    // !!!
    int buffer = 255; // the longest English word has 255 chars
    char color[19]; // because there are 19 color names in my txt file
    scanf("%s", color); // asking for an input to start searching in the file
    char line[buffer];
    
    /*
    We give this variable the initial value of 1. Later, we will say, if the color name
    is found in the file, change the value of the variable to 0. So, after the While loop, 
    if the value of the variable is still 1, it means the given color name 
    is not found in the file.
    And, if the value of the variable changes to 0, the given name is found in the file.
    */
    
    int  found_the_color_name = 1; 
    while (fgets(line, buffer, file)) 
    // search for the given input(color name)in the file
    {
        char *t = strstr(line, color);
        if (t != NULL) // if it's found:
        {
            found_the_color_name = 0;
            printf("Yep! This is a valid color name! :)\n"); // if the color name is found in the file, return True and print this massage
            fclose(file); // close the file
            break; // and break the while loop
            return true;     
        }
    }
    if (found_the_color_name != 0) 
    {
        printf("sorry, This is'nt a valid color name! :(\n"); // if the name is'nt found in the file. print this massage, close the file and return false
        fclose(file);
        return false;
    }
    // !!!
    /*
    !!!
    Also, I was inspired by this source:
    https://www.efaculty.in/c-programs/check-whether-a-given-word-exists-in-a-file-or-not-program-in-c/
    !!!
    */
    return true;
}


/*
You can refer to https://www.w3schools.com/colors/colors_names.asp
to find more color names
*/
// This is cs50 and this is my final project

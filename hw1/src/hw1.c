#include "hw1.h"
#define DEFAULT_N 320

// For your helper functions (you may add additional files also)
// DO NOT define a main function here!

//Validates arguments
char validargs(int argc, char** argv, FILE** in, FILE** out) {
	char ret = 0;

	const unsigned int alphabetLength = strleng(Alphabet);
	int n = 0;

	//printf("Alphabet length scanned: %d\n", alphabetLength);

	if(argc <= 1 || argc > 6)
		return 0;

	char *firstArg = 	argv[1];
	char *secondArg = 	argv[2];
	char *thirdArg = 	argv[3];
	char *fourthArg = 	argv[4];
	char *fifthArg = 	argv[5];

	//First check if the first arg is h.
	if(streq(firstArg, "-h"))
		return 0x80;
	else if(argc != 5 && argc != 6)
		return 0;

	//Parse first argument
	if(streq(firstArg, "-s")){
		// Set the second msb
		ret |= 0x40;

		//Was n passed in?
		if(argc == 6){

			//Get the inputted number
			if(sscanf(fifthArg, "%d", &n) == 0){
				//Exit if no int can be scanned
				return 0;
			}

			if(n < 0)
				return 0;

		}else{

			// Or use the default if no number was passed in
			n = DEFAULT_N;

		}

		int mod = n%alphabetLength;

		// Set the lower 5 bits to whatever this is
		ret |= mod;

	}else if(streq(firstArg, "-t")){

		//Firstly, -t and n cannot be passed at the same time
		if(argc == 6)
			return 0;

		//Ensure that the second msb is not set (clear it)
		ret &= ~0x40;
		ret |= DEFAULT_N%alphabetLength;

	}else
		return 0;

	//Parse second argument
	if(streq(secondArg, "-d"))
		//Set third msb
		ret |= 0x20;
	else if(streq(secondArg, "-e"))
		//Clear third msb
		ret &= ~0x20;
	else
		//If it's anything else, return failure
		return 0;

	//Parse third argument (input file)
	if(streq(thirdArg, "-")){

		*in = stdin;

	}else if((*in = fopen(thirdArg, "r")) == NULL)
		return 0;

	//Parse fourth argument (output file)
	if(streq(fourthArg, "-"))
		*out = stdout;
	else if((*out = fopen(fourthArg, "w")) == NULL)
		return 0;


	return ret;

}

//Main function for substitution encryption/decryption
void substitutionCipher(FILE *in, FILE *out, const int n){

	//Initialize our char to zero
	char c = '\0';

	const char* alphabetCopy = Alphabet;
	const int alphabetLength = strleng(alphabetCopy);

	//printf("\n\nFound alphabet %s : length %d\n\n", alphabetCopy, alphabetLength);

	while((c = fgetc(in)) != EOF)
	{

		//Convert lower case char to upper case
		processSubChar(&c, alphabetCopy, alphabetLength, n);
		fputc(c, out);

	}

}

//Processes a character for substitution cipher
void processSubChar(char *c, const char *alphabet, int alphabetLength, int shiftAmnt){

	int index = 0;

	//Change lowercase to uppercase only
	const int diff = 'a' - 'A';
	*c = (*c >= 'a' && *c <= 'z')?(*c - diff):(*c);

	index = findIndex(*c, alphabet);
	//printf("\nFound index for %c in %s: %d\n", *c, alphabet, index);

	if(index == -1)
		return;

	index += shiftAmnt;
	//printf("Shift amount %d added = %d\n", shiftAmnt, index);

	index %= alphabetLength;
	//printf("Shifted index %% length = %d\n\n", index);

	if(index<0)
		index+=alphabetLength;

	*c = getChar(index, alphabet);

}

//Calculates string length
int strleng(const char *str){

	register int count = 0; 	//Counter
	const char *temp = str; 	//Copy the pointer, just so stuff doesn't get messed up

	while(*temp++)
		count++;

	return count;

}

//Returns if two strings are equivalent
int streq(const char *str1, const char *str2){

	//Compare lengths
	if(strleng(str1) != strleng(str2))
		return 0;

	//Compare each character
	while(*str1 && *str2){

		//Compare and increment
		if(*str1++ != *str2++)
			return 0;

	}

	return 1;

}

//Find the index of a char in a string
int findIndex(const char c, const char* string)
{

	unsigned int index = 0;

	do{

		if(c == *string)
			return index;

		index++;

	}while(*string++);

	//Character not found
	return -1;

}

//Gets the char at a specific index of a string
char getChar(const int index, const char* string){

	int stringLength = strleng(string);

	if(index <= -1 || index >= stringLength)
		return '\0';

	return *(string += index);

}

//Copies a string into another
void strcopy(const char *orig, char *dest){

	while((*dest++ = *orig++));

}
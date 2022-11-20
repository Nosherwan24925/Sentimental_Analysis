#include<iostream>
#include<fstream>
using namespace std;


void clearFile(void);

// Dictionaary Making Functions...

void readRawData(void);
void rawGarbageRemove(char*, int);
void rawStopWordsRemove(char*, int);
void caseChange(char*, int);
void removeDuplicate(void);
void DictionaryMaking(void);
void writeRaw(char*);
//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

// Sentence Input and Garbage Removal Functions
void ClearSentenceFile(void);
void inputSentence(void);
void garbageRemove(char*,int);
void stopWords(char*,int);
void WriteSentence(char*);
int* ReadColumnsFromFile(int*);
char** ReadSentence(int*,int*);
void DictionaryRead(char**, int*, int*);
void DisplaySentence(char**, int*, int*);
void deleteSentence(char**, int*, int*);

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
int main()
{
	char *input =new char;
	*input = '\0';



	// clear Function will delete all data on txt files except raw data file
	clearFile();

	// readRawData Function will read raw txt file.
		// all garbage and stop words will be removed and stored the cleaned words in another txt file.
	readRawData();

	// read data from cleaned data and write single words in another file 
	removeDuplicate();

	// read words from full cleaned data file and generete dictionary.
	DictionaryMaking();

	cout << "Dictionary is Generated!" << endl;

	cout << "Enter E to Exit :" << endl;
	cout << "Enter other than E to start Program :" << endl;
	while (cin >> *input)
	{
		if (*input == 'E' || *input == 'e')
			break;

		char** Sentence = NULL;
		int* Columns = NULL;
		int* Rows = new int;
		*Rows = 0;


		
		// take input from user.
		// send the word to removeGarbage function to remove garbage words.
		// then send the word to caseChangefuncton to convert in small letter.
		// then send to stopWords function and removed the stop words.
		// at end write the word in txt file named sentence.
		ClearSentenceFile();
		inputSentence();

		// read sentence txt file and count the words, then create Columns array.
		Columns = ReadColumnsFromFile(Rows);

		// read sentence txt file and store the words in sentence Jagged Array.
		Sentence = ReadSentence(Columns, Rows);

		// Display the sentence on console.
		DisplaySentence(Sentence, Columns, Rows);

		// compare the sentence with dictionary
		// state the sentiment of sentence.
		DictionaryRead(Sentence, Columns, Rows);

		// deleting the sentence, Columns and row.
		deleteSentence(Sentence, Columns, Rows);


		cout << "Enter E to Exit :" << endl;
		cout << "Enter other than E to start Program :" << endl;
	}
	
	cout << "Program is Exited:" << endl;
	delete input;
	input = nullptr;

	system("pause");

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clearFile(void)
{
	ofstream writeFileOne, writeFileTwo, writeFileThree;

	writeFileOne.open("cleanData.txt");
	writeFileOne << "";
	writeFileOne.close();

	writeFileTwo.open("cleandatafull.txt");
	writeFileTwo << "";
	writeFileTwo.close();

	writeFileThree.open("dictionary.txt");
	writeFileThree << "";
	writeFileThree.close();

	

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ClearSentenceFile()
{
	ofstream writeFileFour;
	writeFileFour.open("sentence.txt");
	writeFileFour << "";
	writeFileFour.close();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void readRawData(void)
{
	int size = 20;
	char* input = new char[size];
	int sizeOfword = 0;
	for (int zero = 0; zero < size; zero++)
	{
		input[zero] = '\0';
	}

	ifstream readFile;

	readFile.open("rawdata.txt");

	if (!readFile.is_open())
	{
		cout << "File not Opened in readRawData Function:" << endl;
	}
	else
	{
		cout << "Loading...! Please Wait For A While." << endl;
		cout << "Dictionary is Generating..." << endl;
		while (readFile >> input)
		{
			sizeOfword = 0;
			if (input[0] == '0' || input[0] == '1')
			{

			}


			for (int i = 0; input[i] != '\0'; i++)
			{
				sizeOfword++;
			}


			rawGarbageRemove(input, sizeOfword);

			for (int zero = 0; zero < size; zero++)
			{
				input[zero] = '\0';
			}

		}

	}


	input = nullptr;
	readFile.close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rawGarbageRemove(char* input, int sizeOfWord)
{
	int check = 0;
	for (int index = 0; index < sizeOfWord; index++)
	{
		if ((input[index] >= 'A' && input[index] <= 'Z' || input[index] >= 'a' && input[index] <= 'z' || input[index] == '0' || input[index] == '1'))
		{
			check++;
		}

	}
	if (check == sizeOfWord)
	{
		caseChange(input, sizeOfWord);
		rawStopWordsRemove(input, sizeOfWord);
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rawStopWordsRemove(char* input, int sizeOfWord)
{
	int size = 20;
	char* inputTwo = new char[size];
	for (int null = 0; null < size; null++)
	{
		inputTwo[null] = '\0';
	}
	int sizeOfWordTwo = 0;
	bool check = true;
	ifstream obj;
	obj.open("stopword.txt");
	if (!obj.is_open())
		cout << "File not Opened in rawStopRemove Function :" << endl;
	else
	{
		while (obj >> inputTwo)
		{
			check = false;
			sizeOfWordTwo = 0;

			for (int i = 0; inputTwo[i]; i++)
				sizeOfWordTwo++;

			if (sizeOfWord == sizeOfWordTwo)
			{
				sizeOfWordTwo = 0;
				for (int i = 0; i < sizeOfWord; i++)
				{
					if (input[i] == inputTwo[i])
						sizeOfWordTwo++;
				}
				if (sizeOfWord == sizeOfWordTwo)
					check = true;

			}
			if (check == true)
				break;

			for (int null = 0; null < size; null++)
			{
				inputTwo[null] = '\0';
			}
		}
		if (check == false)
			writeRaw(input);

	}

	obj.close();


	inputTwo = nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void caseChange(char* input, int sizeOfWord)
{
	for (int index = 0; index < sizeOfWord; index++)
	{
		if (input[index] >= 'A' && input[index] <= 'Z')
		{
			input[index] = int(input[index] + 32);
		}
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void removeDuplicate(void)
{
	const int size = 20;
	int key = 1;
	ifstream readData;
	ifstream readDataOne;
	ofstream drop;
	bool check = false;
	char input[size] = { '\0' };
	char inputTwo[size] = { '\0' };
	int sizeOfInput = 0;
	int sizeOfInputOne = 0;
	readData.open("cleanData.txt");
	if (!readData.is_open())
		cout << "File not Opened removeDuplicate:" << endl;
	else
	{
		while (readData >> input)
		{
			sizeOfInput = 0;
			if (input[0] == '0' || input[0] == '1')
			{
				//cout << endl;
			}
			else
			{

				for (int i = 0; input[i] != '\0'; i++)
				{
					sizeOfInput++;
				}
				readDataOne.open("cleandatafull.txt");
				if (!readDataOne.is_open())
					cout << "File not Opened remove duplicate:" << endl;
				else
				{
					while (readDataOne >> inputTwo)
					{

						sizeOfInputOne = 0;
						check = true;
						for (int i = 0; inputTwo[i] != '\0'; i++)
						{
							sizeOfInputOne++;
						}
						if (sizeOfInput == sizeOfInputOne)
						{
							sizeOfInputOne = 0;

							for (int i = 0; i < sizeOfInput; i++)
							{
								if (input[i] == inputTwo[i])
								{
									sizeOfInputOne++;
								}
							}
						}
						if (sizeOfInputOne == sizeOfInput)
						{
							check = false;
							break;
						}
						for (int i = 0; i < size; i++)
						{
							inputTwo[i] = '\0';
						}

					}
				}
				readDataOne.close();

				if (key == 1)
				{
					key = 2;
					drop.open("cleandatafull.txt", ios::app);
					if (!drop.is_open())
						cout << "File not Opened:" << endl;
					else
					{
						drop << input << endl;
					}
					drop.close();
				}
				if (check == true)
				{
					drop.open("cleandatafull.txt", ios::app);
					if (!drop.is_open())
						cout << "File not Opened:" << endl;
					else
					{
						drop << input << endl;
					}
					drop.close();
				}

				for (int i = 0; i < size; i++)
				{
					input[i] = '\0';
				}

			}
		}
	}
	readData.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void caseChange(char** SentenceArray, int* Columns, int* Rows)
{

	for (int index = 0; index < *Rows; index++)
	{
		for (int indexOne = 0; indexOne < Columns[index]; indexOne++)
		{

			if (SentenceArray[index][indexOne] >= 'A' && SentenceArray[index][indexOne] <= 'Z')
			{
				SentenceArray[index][indexOne] = int(SentenceArray[index][indexOne] + 32);
			}

		}
	}

}

void deleteSentence(char** Sentence, int* Columns, int* Rows)
{
	for (int index = 0; index < *Rows; index++)
	{
		delete[] Sentence[index];
	}
	delete[] Sentence;
	Sentence = nullptr;

	delete[] Columns;
	Columns = nullptr;

	delete Rows;
	Rows = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int* ReadColumnsFromFile(int* Rows)
{
	int columnSize = 0;
	int size = 20;
	char* input = new char[size];
	for (int null = 0; null < size; null++)
	{
		input[null] = '\0';
	}
	int sizeOfWord = 0;

	ifstream ReadFile;

	ReadFile.open("sentence.txt");
	if (!ReadFile.is_open())
		cout << "File not Opended in ReadColumns Function:" << endl;
	else
	{
		while (ReadFile >> input)
		{
			sizeOfWord++;
		}
		
	}

	ReadFile.close();
	columnSize = sizeOfWord;
	sizeOfWord = 0;
	for (int null = 0; null < size; null++)
	{
		input[null] = '\0';
	}

	int* newColumn = new int[columnSize];

	ReadFile.open("sentence.txt");
	if (!ReadFile.is_open())
		cout << "File not Opended in ReadColumns Function:" << endl;
	else
	{
		int key = 0;
		int count = 0;
		while (ReadFile >> input)
		{
			count = 0;
			for (int i = 0; input[i] != '\0'; i++)
			{
				count++;
			}
			sizeOfWord = count;

			newColumn[key]=sizeOfWord;
			key++;
			*Rows = *Rows + 1;

			for (int null = 0; null < size; null++)
			{
				input[null] = '\0';
			}
		}
		
	}
	ReadFile.close();


	/*delete[] input;
	input = nullptr;*/

	return newColumn;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


char** ReadSentence(int*Columns, int*Rows)
{
	char** Sentence = new char* [*Rows];
	for (int index = 0; index < *Rows; index++)
	{
		Sentence[index] = new char[Columns[index]];
	}

	
	ifstream ReadFile;
	ReadFile.open("sentence.txt");
	if (!ReadFile.is_open())
		cout << "File not Opended in ReadColumns Function:" << endl;
	else
	{
		for (int i = 0; i < *Rows; i++)
		{
			for (int j = 0; j < Columns[i]; j++)
			{
				ReadFile >> Sentence[i][j];
			}
		}

	}
	ReadFile.close();

	return Sentence;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void writeRaw(char* input)
{
	ofstream drop;
	drop.open("cleanData.txt", ios::app);
	if (!drop.is_open())
		cout << "File not Opened Of:" << endl;
	else
	{
		if (input[0] == '0' || input[0] == '1')
			drop << endl;

		drop << input << " ";
	}

	drop.close();

}


void DictionaryMaking(void)
{
	const int size = 20;
	char input[size] = { '\0' };
	char inputOne[size] = { '\0' };
	int sizeOfInput = 0;
	int sizeOfInputOne = 0;
	long long totalCount = 0;
	long long positiveCount = 0;
	long long negativeCount = 0;
	ifstream readFileOne, readFileTwo;
	ofstream drop;
	char *key = new char;
	*key = '\0';
	readFileOne.open("cleandatafull.txt");
	if (!readFileOne.is_open())
	{
		cout << "file not opened in function DictionaryMaking" << endl;
	}
	else
	{
		while (readFileOne >> input)
		{
			
			totalCount = 0;
			negativeCount = 0;
			positiveCount = 0;
			sizeOfInput = 0;
			for (int index = 0; input[index] != '\0'; index++)
			{
				sizeOfInput++;
			}

			readFileTwo.open("cleanData.txt");
			if(!readFileTwo.is_open())
				cout << "file not opened in function DictionaryMaking" << endl;
			else
			{
				
				while (readFileTwo >> inputOne)
				{
					sizeOfInputOne = 0;
					if (inputOne[0] == '0')
						*key ='0';
					else if (inputOne[0] == '1')
						*key = '1';

					else
					{
						
						for (int i = 0; inputOne[i]!='\0'; i++)
						{
							sizeOfInputOne++;
						}

						if (sizeOfInput == sizeOfInputOne)
						{
							sizeOfInputOne = 0;
							for (int i = 0; i < sizeOfInput; i++)
							{
								if (input[i] == inputOne[i])
									sizeOfInputOne++;
							}
						}
						if (sizeOfInput == sizeOfInputOne)
						{
							totalCount = totalCount + 1;
							if (*key == '0')
								negativeCount = negativeCount + 1;
							if (*key == '1')
								positiveCount = positiveCount + 1;
						}
					}

					for (int zero = 0; zero < size; zero++)
					{
						inputOne[zero] = '\0';
					}
				}
				readFileTwo.close();
			}

			drop.open("dictionary.txt", ios::app);
			if (!drop.is_open())
				cout << "File not opened in function dictionary making:" << endl;
			else
			{

				drop << input << " " << totalCount << " " << positiveCount << " " << negativeCount << " " << endl;
			}
			drop.close();
			for (int zero = 0; zero < size; zero++)
			{
				input[zero] = '\0';
			}
		}
		readFileOne.close();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void inputSentence()
{
	int size = 20;
	int sizeOfWord = 0;
	char* input = new char[size];
	for (int null = 0; null < size; null++)
	{
		input[null] = '\0';
	}
	cout << "Enter Sentence And Press Fullstop to Terminate Sntence :" << endl;
	while (cin >> input)
	{
		if (input[0] == '.')
		{
			break;
		}
		else
		{
			sizeOfWord = 0;
			for (int countletter = 0; countletter < input[countletter]!='\0'; countletter++)
			{
				sizeOfWord++;
			}

			 garbageRemove(input,sizeOfWord);
		}


		for (int null = 0; null < size; null++)
		{
			input[null] = '\0';
		}
	}

	delete[] input;
	input = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void DisplaySentence(char** SentenceArray, int* Column, int *RowsOfMatrix)
{
	cout << endl;
	cout << "Sentence Without Garbage and StopWords !" << endl;
	cout << endl;
	for (int i = 0; i < *RowsOfMatrix; i++)
	{
		for (int j = 0; j < Column[i]; j++)
		{
			cout << SentenceArray[i][j];
		}
		cout << " ";
	}
	cout << endl;
	cout << endl;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////


void garbageRemove(char* input,int sizeOfWord)
{
	int sizeOfWordTwo = 0;
	for (int index = 0; index < sizeOfWord; index++)
	{
		if (input[index] >= 'A' && input[index] <= 'Z' || input[index] >= 'a' && input[index] <= 'z')
		{
			sizeOfWordTwo++;
		}
	}
	if (sizeOfWord == sizeOfWordTwo)
	{
		caseChange(input, sizeOfWord);
		stopWords(input,sizeOfWord);
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void stopWords(char* input,int sizeOfWord)
{
	bool check = false;
	char* inputFile = new char[20];
	for (int null = 0; null < 20; null++)
	{
		inputFile[null] = '\0';
	}
	int sizeOfWordTwo = 0;
	ifstream readFile;
	readFile.open("stopword.txt");
	if (!readFile.is_open())
		cout << "File not opened in function stopwords:" << endl;
	else
	{
		while (readFile>>inputFile)
		{
			check = true;
			sizeOfWordTwo = 0;
			for (int index = 0; inputFile[index] != '\0'; index++)
			{
				sizeOfWordTwo++;
			}
			if (sizeOfWord == sizeOfWordTwo)
			{
				sizeOfWordTwo = 0;
				for (int index = 0; index < sizeOfWord; index++)
				{
					if (input[index] == inputFile[index])
					{
						sizeOfWordTwo++;
					}
				}
			}
			if (sizeOfWord == sizeOfWordTwo)
			{
				check = false;
				break;
			}



			for (int null = 0; null < 20; null++)
			{
				inputFile[null] = '\0';
			}
		}

		if (check == true)
		{
			
			WriteSentence(input);
		}

		readFile.close();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WriteSentence(char* input)
{
	ofstream WriteSentence;
	WriteSentence.open("sentence.txt", ios::app);
	if (!WriteSentence.is_open())
		cout << "File not Opened in WriteSentence Sunction:" << endl;
	else
	{
		WriteSentence << input << endl;
	}
	WriteSentence.close();
}

void DictionaryRead(char** SentenceArray, int* Columns, int* Rows)
{
	int size = 20;
	ifstream readFile;
	char* Input = new char[size];
	for (int null = 0; null < size; null++)
	{
		Input[null] = '\0';
	}
	int sizeOfInput = 0;
	bool check = false;
	int sizeOfInputOne = 0;
	int TotalCount = 0, Positive = 0, Negative = 0;
	double total = 0;
	double positive = 0;
	double negative = 0;
	double rNegative = 0.0;
	double rPositive = 0.0;
	for (int index = 0; index < *Rows; index++)
	{
		readFile.open("dictionary.txt");

		if (!readFile.is_open())
		{
			cout << "File not Opened:" << endl;
		}
		else
		{
			while (readFile >>Input>>TotalCount>>Positive>>Negative )
			{
				sizeOfInput = 0;
				check = false;
				for (int i = 0; Input[i]!='\0' ; i++)
				{
					sizeOfInput++;
				}

				if (sizeOfInput == Columns[index])
				{
					sizeOfInputOne=0;
					for (int i = 0; i < Columns[index];i++)
					{
						if (SentenceArray[index][i] == Input[i])
						{
							sizeOfInputOne++;
						}
					}
				}

				if (sizeOfInputOne == Columns[index])
				{
					check = true;
					break;
				}

				for (int null = 0; null < size; null++)
				{
					Input[null] = '\0';
				}

			}
			if (check == true)
			{
				total = TotalCount + total;
				positive = Positive + positive;
				negative = Negative + negative;
			}
			for (int null = 0; null < size; null++)
			{
				Input[null] = '\0';
			}
			
		}

	
		readFile.close();

	}

	rNegative = negative / total;
	rPositive = positive / total;
	cout << endl;
	cout << endl;
	cout << endl;
	if (total == 0)
	{
		cout << "The Words has Not been Found in Dictionary!" << endl;
	}
	else
	{


		cout << "Without Normalization " << endl;
		cout << "Total Count : " << total << endl;
		cout << "Total Positive Count : " << positive << endl;
		cout << "Total Negative Count : " << negative << endl;
		if (negative > positive)
			cout << "The Text is Negative : " << endl;
		else
			cout << "The Text is Positive :" << endl;

		cout << endl;
		cout << endl;
		cout << endl;
		cout << "With Normalization :" << endl;
		cout << "Negative Count : " << rNegative << endl;
		cout << "Positive Count : " << rPositive << endl;
		if (rNegative > rPositive)
			cout << "The Text is Negative :" << endl;
		else
			cout << "The Text is Positive :" << endl;
	}

}
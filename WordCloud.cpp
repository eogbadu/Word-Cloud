#include "WordCloud.h"

// WordCloud (Default Constructor) - Used to pass an essay (in input file)
// and generates word list and frequency
WordCloud::WordCloud()
{
  m_fileName = "proj5_test1.txt";
  m_cloud = new LL<string>();
}

// WordCloud (Overloaded Constructor) - Used to pass an essay (in input file)
// and generates word list and frequency
WordCloud::WordCloud(string fileName)
{
  m_fileName = fileName;
  m_cloud = new LL<string>();
}

//~WordCloud (Destructor) - Deallocates m_cloud
WordCloud::~WordCloud()
{
  delete m_cloud;
  m_cloud = nullptr;
}

// LoadFile - Loads a file (everything as a string although could be anything
// stringlike)
void WordCloud::LoadFile()
{
  // Declare variables
  string word;
  ifstream inStream;
  // Open to file to read and perform check
  // to make sure it opened successfully
  inStream.open(m_fileName);
  if(inStream.fail())
  {
    cout << "File failed to load.\n";
  }
  else
  {
    while (inStream >> word)
    {
      // Remove punctuation from begining and the end of a word
      RemovePunct(word);

      // Convert all words to lowercase
      for (string::iterator it = word.begin(); it!=word.end(); ++it)
      {
	*it = (char)tolower(*it);
      }

      // Insert the word into m_cloud
      m_cloud->Insert(word);
    }
  }
}

// RemovePunct - When passed a string, removes all non letter punctation
// on the beginning or end of the string.
void WordCloud::RemovePunct(string &word)
{
  // Check if the word ends with a punctuation
  // Remove if it is a punctuation
  if (ispunct(word.back()))
  {
    word.erase(word.end() - 1);
  }

  // Check if the word starts with a punctuation
  // Remove if it is a punctuation
  if (ispunct(word.front()))
  {
    word.erase(word.begin());
  }
}

// RemoveCommon - Iterates through m_cloud and removes all common words
// after they are read
void WordCloud::RemoveCommon()
{
  // Declare variables
  vector <string> matchedWords; // Vector to hold common words in m_cloud

  // Locate common words in m_cloud and store them in vector
  for (int i = 0; i < m_cloud->GetSize(); i++)
  {
    vector<string>::const_iterator it;
    for (it=EXCLUDE_LIST.begin(); it!=EXCLUDE_LIST.end(); ++it)
    {
      if ((*m_cloud)[i].first == *it ) 
      {
	matchedWords.push_back((*m_cloud)[i].first);
      }
    }
  }

  // Remove the common words from m_cloud
  vector<string>::iterator it;
  for (it=matchedWords.begin(); it!=matchedWords.end(); ++it)
  {
     m_cloud->RemoveAt(*it);
  }

  // Call Remove singles to ask user if they want
  // to remove words with a frequency of 1
  RemoveSingles();
}

// RemoveSingles - Asks the user if they would like to remove words
// with a frequency of 1 
// Should use the overloaded [] NOTE: Don't forget m_cloud is a pointer!
void WordCloud::RemoveSingles()
{
  // Declare variables
  string choice;
  bool goodChoice = false;
  vector <string> matchedWords; // Vector to hold words with frequency of 1
  
  do
  {
    cout << "Would you like to remove all words with a frequency of 1?"
	 << endl;
    cin >> choice;


    // Change string to uppercase
    for (string::iterator it = choice.begin(); it!=choice.end(); ++it)
    {
      *it = (char)toupper(*it);
    }

    // Confirm that the choice entered is a valid choice
    vector<string>::const_iterator it;
    for (it=CHOICES.begin(); it!=CHOICES.end(); ++it)  
    {
      if (choice == *it)
      {
	goodChoice = true;
      }
    }
  } while (!goodChoice);

  // If user chooses yes/y
  if ((choice == CHOICES.at(0)) || (choice == CHOICES.at(1)))
  {
    // Locate words with frequency of 1 in m_cloud and store them in vector
    for (int i = 0; i < m_cloud->GetSize(); i++)
    {
      if ((*m_cloud)[i].second == 1)
      {
	matchedWords.push_back((*m_cloud)[i].first);
      }
    }

    // Remove the words from m_cloud
    vector<string>::iterator it;
    for (it=matchedWords.begin(); it!=matchedWords.end(); ++it)
    {
      m_cloud->RemoveAt(*it);
    }
    
    // Print out number of words removed from m_cloud
    cout << matchedWords.size() << " words removed." << endl;
  }
  // If user chooses No/n
  else
  {
    cout << "0 words removed." << endl;
  }
}

// Export - Iterates through m_cloud and exports to file "data:frequency" 
void WordCloud::Export()
{
  // Declare variables
  string fileName;
  ofstream myFile;
  int fileNameLength;
  int position1;

  // Get file name from user and validate
  cout << "What would you like to call the export file?" << endl;
  cin >> fileName;
  fileNameLength = int(fileName.length());
  position1 = fileNameLength - TXT_LENGTH;

  // Check if filename is too short or doesn't end with .txt
  while ((fileNameLength <= TXT_LENGTH)
         || (fileName.substr(position1) != TEXT))
  {
    cout << "       ****FILE NAME ERROR****" << endl;
    cout << "File name must be at least 5 characters"
         << " and must be a text file (.txt)\n" << endl;
    cout << "What would you like to call the export file?" << endl;
    cin >> fileName;
    fileNameLength = int(fileName.length());
    position1 = fileNameLength - TXT_LENGTH;
  }

  // Open to file to read and perform check
  // to make sure it opened successfully
  myFile.open(fileName);
  if(myFile.fail())
  {
    cout << "File failed to load.\n";
  }
  else
  {
    myFile << *m_cloud;
    cout << "Output to export file " << fileName << endl;
    cout << m_cloud->GetSize() << " unique words exported" << endl;
    
    myFile.close();
  }
}

// Start - Calls LoadFile, RemoveCommon, Diplay, and Export 
void WordCloud::Start()
{
  LoadFile();
  RemoveCommon();
  m_cloud->Display();
  cout << "END" << endl;
  Export();
}

//Patrick Keppler and Connor Wright, 2019
#include "FileReader/fastafilereader.h"
#include "FileReader/alphabetfilereader.h"
#include "SuffixTree/SuffixTree.h"

int main(int argc, char * argv[])
{
  int testMode, length;
  char * cString;
  fstream fastaFile, alphabetFile;
  SuffixTree suffixTree;
  FastaFileReader fastaReader;
  AlphabetFileReader alphabetReader;
  string fastaString;
  assert(argc >= 3);

  fastaFile.open(argv[1], fstream::in);
  alphabetFile.open(argv[2], fstream::in);
  testMode = 0;

  if(argc > 3)
  {
    testMode = atoi(argv[3]);
  }

  if(fastaFile.is_open() && alphabetFile.is_open())
  {

      fastaReader = FastaFileReader(&fastaFile);
      alphabetReader = AlphabetFileReader(&alphabetFile);
      fastaString = fastaReader.getSequenceByIndex(0).nucleotideSequence;
      //add the $ to the end of the input string
      fastaString.append("$");
      //get char *, length
      length = fastaString.length();
      //const char * immutableStr = fastaString.c_str();
      //cString = new char[length];
      //strcpy(cString, immutableStr);
      //create a suffix tree
      suffixTree = SuffixTree();
      //TODO:replace with McCreight when ready
      STData::startTimer();
      suffixTree.McCreightInsert(&fastaString);
      //suffixTree.basicInsert(&fastaString);
      STData::stopTimer();
      //1's place is 1: do dfs
      if((testMode & 1) == 1)
      {
        STData::init(&fastaString, length);
        suffixTree.DFS();
        //2's place is 1: print bwt
        if((testMode & 2) == 2)
        {
          STData::printBwt();
        }
        //4's place is 1: print other data
        if((testMode & 4) == 4)
        {
          STData::printData();
        }

        if((testMode & 16) == 16)
        {
          STData::printLongestRepeat();
        }
      }
      if((testMode & 8) == 8)
      {
        STData::printElapsedTime();
      }
      if((testMode & 32) == 32)
      {
        printf("pausing\n");
        getchar();
      }
      //done, delete BWT
      STData::done();

  }


  return 0;
}

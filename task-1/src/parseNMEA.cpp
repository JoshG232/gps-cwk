#include "earth.h"
#include "parseNMEA.h"
#include "string"
#include <iostream>
#include <vector>
using namespace std;
namespace NMEA
{

  bool isWellFormedSentence(std::string sentence)
  {
      // Stub definition, needs implementing

      //$GP

//      bool failed = false;
      string dollarSign = "$";
      string gChar = "G";
      string pChar = "P";
      int count = 0;
      char GPCheck1 = sentence[0];
      char GPCheck2 = sentence[1];
      char GPCheck3 = sentence[2];
//      cout << GPCheck1 << ", " << GPCheck2 << ", " << GPCheck3 << endl;
//      cout << dollarSign << ", " << gChar << ", " << pChar << endl;
      if (GPCheck1 == dollarSign[0]){
//          cout << "Dollar Sign Good" << endl;
          count++;
      }
      if (GPCheck2 == gChar[0]){
//          cout << "G Good" << endl;
          count++;
      }
      if (GPCheck3 == pChar[0]){
//          cout << "P Good" << endl;
          count++;
      }
      cout << "Count: " << count << endl;
      if(count == 3){
          // Three letters
          if (sentence.size() < 7){
              cout << "Less than 7" << endl;
              return false;
          }
          char char1 = sentence[3];
          char char2 = sentence[4];
          char char3 = sentence[5];
          cout << char1 << ", " << char2 << ", " << char3 << endl;

          if (isalpha(char1) and isalpha(char2) and isalpha(char3)){
              // *

              string starString = "*";
              char star = sentence[sentence.size() -3];
              char starTwo = starString[0];

        //      cout << star << endl;
              if (star == starTwo){
                  // Checking for $ and * in between
                  string starSign = "*";
                  vector<char> sentenceArr(sentence.begin(),sentence.end());
                  int illCharacterCount = 0;
                  for (const char &c: sentenceArr) {
                      cout << c;
                      if (c == dollarSign[0] or c == starSign[0]){
                        illCharacterCount++;
                      }
                  }
                  if (illCharacterCount > 2){
                      return false;
                  } else {
                      char hex1 = sentence[sentence.size() -2];
                      char hex2 = sentence[sentence.size() -1];



                      if (isxdigit(hex1) and isxdigit(hex2)){
                          return true;
                      } else {
                          return false;
                      }
                  }

              } else {
                  return false;
              }

          }
          else {
              cout << "Failed for 4,5 and 6 not being characters" << endl;
              return false;
          }

      }
      else {
          cout << "No match to $GP" << endl;
          return false;
      }







////      Hexadecimal


//      cout << "Test: " << failed << endl;
//      //Test output
//      if (failed == true){
//          return false;
//      } else {
//          return true;
//      }
  }

  bool hasValidChecksum(std::string)
  {
      // Stub definition, needs implementing
      return false;
  }

  SentenceData extractSentenceData(std::string)
  {
      // Stub definition, needs implementing
      return {"",{}};
  }

  GPS::Position positionFromSentenceData(SentenceData)
  {
      // Stub definition, needs implementing
      return GPS::Earth::NorthPole;
  }

  Route routeFromLog(std::istream &)
  {
      // Stub definition, needs implementing
      return {};
  }

}

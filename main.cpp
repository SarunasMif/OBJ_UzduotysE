#include "header.h"

using namespace std;

void Printfile(map<string, Data>& map) {
   ofstream Write;

   Write.open("Output.txt");

   for (const auto &Adata : map) {
      if (Adata.second.number > 1) {
         Write << "[" << Adata.first << "] was used [" << Adata.second.number << "] times." << endl;
      }
   }

   Write.close();
} // prints out word and how many times ot was used

void printLinks(map<int, string>& map) {
   ofstream write;

   write.open("LinkList.txt");

   for (const auto &Adata : map) {
      write << Adata.second << endl;
   }

   write.close();
} // prints out found links

void BuildReff(map<string, Data>& map) {
   ofstream Write;

   Write.open("Refference_table.txt");

   Write << left << setw(20) << "Words" << "| " << setw(51) << "Lines" << endl;
   Write << "-----------------------------------------------------------------------" << endl;

   for (const auto &Adata : map) {
      const string& word = Adata.first;
      const Data& data = Adata.second;

      if (data.number > 1) {
         Write << left << setw(20) << word << "|";

         for (int line : data.lines) {
            Write << line << "; ";
         }
         Write << endl;
         Write << "--------------------|--------------------------------------------------" << endl;

      }

   }

   Write.close();

} // Prints a cross-reference table

void ToLower(string& word) {
   for (char &Adata : word) {
      Adata = tolower(Adata);
   }
} // Thes words and makes every letter lowercase

vector<string> cleanline(string& line) {
   vector<string> cleaned_line;
   string word;
   size_t found = line.find_first_of(",.!:;?'()[]{}…’–/$#%^&*@$");

   while (found != string::npos) {
      line.erase(found, 1);
      found = line.find_first_of(",.!:;?'()[]{}…’–/$#%^&*@$", found + 1);
   }

   line.erase(remove(line.begin(), line.end(), '"'), line.end());

   istringstream Line(line);

   while (Line >> word) {
      cleaned_line.push_back(word);
   }

   return cleaned_line;
} // Takes line and removes punctuations abd returns line to ReadFile

vector<string> getURL(string& line) {
   vector<string> URLS;
   string word;
   vector<string> Url_ends_gen = {".com", ".edu", ".gov", ".org", ".mil", ".net"};
   vector<string> Url_ends_nat = {".au", ".in", ".br", ".it", ".ca", ".mx", ".fr", ".tw", ".il", ".uk", ".lt", ".lv", ".kr", ".jp", ".is", ".ie", ".gr", ".ge", ".ee", ".be", ".at", ".al",
   ".de", ".cz", ".cy", ".ru", ".dm", ".cn", ".eu", ".us", ".ua", ".tw", ".tr", ".sk", ".si", ".se", ".rs", ".pt", ".pl", ".nz", ".no", ".md", ".id", ".hr", ".fi", ".ca", ".by", ".am"};
   istringstream Line(line);

   while (Line >> word) {

      for (string& end : Url_ends_gen) {

         if (word.find(end) != string::npos) {

            if (word.find(".") != string::npos) {
               word.erase(remove(word.end() - 1, word.end(), '.'), word.end());
               word.erase(remove(word.end() - 1, word.end(), '/'), word.end());
               word.erase(remove(word.end() - 1, word.end(), ','), word.end());
            }// If the link is at the end of the sentence the . at the end of the link is removed

            URLS.push_back(word);
         }
      }

      for (string& end : Url_ends_nat) {
         if (word.find(end) != string::npos) {

            if (word.find(".") != string::npos) {
               word.erase(remove(word.end() - 1, word.end(), '.'), word.end());
               word.erase(remove(word.end() - 1, word.end(), '/'), word.end());
               word.erase(remove(word.end() - 1, word.end(), ','), word.end());
            }// If the link is at the end of the sentence the . at the end of the link is removed

            URLS.push_back(word);
         }
      }

   }

   return URLS;
} // Takes line and finds url in it and sends it back to ReadLink

void ReadFile(string filename, map<string, Data>& map) {
   ifstream Read;
   string str_placeholder;
   int line = 1;

   Read.open(filename);

   while(getline(Read, str_placeholder)) {
      vector<string> Line = cleanline(str_placeholder);

      for (string& word : Line) {
         ToLower(word);
         map[word].number++;
         map[word].lines.insert(line);
      }

      line++;
   }

   Printfile(map);
   BuildReff(map);

   Read.close();
} // Reads the text file and inputs data to associative arrays

void ReadLink(string filename, map<int, string>& map) {
   ifstream read;
   string str_placeholder;
   int key = 0;

   read.open(filename);

   while(getline(read, str_placeholder)) {
      vector<string> Line = getURL(str_placeholder);

      for (string& url : Line) {
         ToLower(url);
         map[key++] = url;
      }
   }

   printLinks(map);

   read.close();
} // Reads the text file and inputs data to associative arrays

int main() {
   string i_filename = "test.txt";
   string l_filename = "test.txt";

   map<string, Data> Info;
   map<int, string> Links;
   // Asociative array

   ReadFile(i_filename, Info);
   ReadLink(l_filename, Links);

   system("pause");

   return 0;
}
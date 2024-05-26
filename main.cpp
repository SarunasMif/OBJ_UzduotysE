#include "header.h"

using namespace std;

void Printfile(map<string, Data>& map) {
   ofstream Write;

   Write.open("Output.txt");


   for (const auto &Adata : map) {
      if (Adata.second.number > 1) {
         Write << Adata.first << " was used " << Adata.second.number << " times." << endl;
      }
   }

   Write.close();
}

void printLinks(map<int, string>& map) {
   ofstream write;

   write.open("LinkList.txt");

   for (const auto &Adata : map) {
      write << Adata.second << endl;
   }

   write.close();
}

void BuildReff(map<string, Data>& map) {
   ofstream Write;

   Write.open("Refference_table.txt");

   for (const auto &Adata : map) {
      if (Adata.second.number > 1) {
         Write << Adata.first << " was found in lines ";

         for (int line : Adata.second.lines) {
            Write << line << " ";
         }

         Write << endl;
      }
   }

   Write.close();

} // Padaryti, kad atrodytu kaip lentele

void ToLower(string& word) {
   for (char &Adata : word) {
      Adata = tolower(Adata);
   }
}

vector<string> cleanline(string& line) {
   vector<string> cleaned_line;
   string word;
   size_t found = line.find_first_of(",.!:;?'()[]{}…’–");

   while (found != string::npos) {
      line.erase(found, 1);
      found = line.find_first_of(",.!:;?'()[]{}…’–", found + 1);
   }

   line.erase(remove(line.begin(), line.end(), '"'), line.end());

   istringstream Line(line);

   while (Line >> word) {
      cleaned_line.push_back(word);
   }

   return cleaned_line;
}

vector<string> getURL(string& line) {
   vector<string> URLS;
   string word;
   size_t found = line.find("http");
   istringstream Line(line);

   while (Line >> word) {
      if (word.find("http") != string::npos) {

         if (word.find(".") != string::npos) {
            word.erase(remove(word.end() - 1, word.end(), '.'), word.end());
         }// If the link is at the end of the sentence the . at the end of the link is removed

         URLS.push_back(word);
      }
   }

   return URLS;
}

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
}

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
}

int main() {
   string i_filename = "Input.txt";
   string l_filename = "Links.txt";

   map<string, Data> Info;
   map<int, string> Links;

   ReadFile(i_filename, Info);
   ReadLink(l_filename, Links);

   system("pause");

   return 0;
}
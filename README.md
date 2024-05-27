# OBJ_UzduotysE

Egzamino užduotis, kurioje panaudojami associative arrays ir std::string.

# Kodo pavyzdžiai

## `ReadFile()`

Funkcija paima iš .txt failo po 1 eilute ir ją nusiunčia į funkciją `cleanline()`, kad išimtu skyrybos ženklus ir i map array ideda žodį kaip key ir padidina kiek kartų buvo panaudotas žodis ir kurioje eilutėje buvo rastas.

```cpp
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
```

## `cleanline()`

Funkcija paima eilutę atsiųsta iš `ReadFile()` ir praeina pro ją ir su find_first_of funkcija išima visus skyrybos ženklus, kurios aš parinkau pagal Lynchburgo Universiteto specifikacas: https://www.lynchburg.edu/academics/writing-center/wilmer-writing-center-online-writing-lab/grammar/a-quick-guide-to-punctuation/ ir IELTS specifikacijas: https://ieltsliz.com/ielts-tips-how-words-are-counted/. Išvalytus žodžius priskiria i vector ir grąžina į `ReadFile()` funkciją.

```cpp
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
```

# Failai

## `Input.txt`

Sudaryti `Input.txt` aš paėmiau tris savo 12-oje klasėje rašytus anglų kalbos rašinius ir sukėliau juos į vieną failą, nes jie parašyti korektiškai ir išvengiama problemų tieasiogiai kopijuojant iš Wikipedia.

## `Links.txt`

`Links.txt` buvo sugeneruotas AI dėl paprastumo ir kad būtų pakankamai pilnos formos linkų, kuriuos būtų galima paimti.
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

/*
  Parte 1
    true 1251
    false
    false

    false
    true 1
    true 1751
Parte 2
    834 840
    1751 1799
Parte 3
    297 301
*/

// Lecuta de archivos
vector<char> readTXT(const string &name) {
  vector<char> vector;
  ifstream file(name);
  // Abre el archivo y lo va leyendo línea por línea
  if (file.is_open()) {
    char character;
    while (file.get(character)) {
      if (character != '\n')
        vector.push_back(character);
    }
    file.close();
  } else {
    // Si el archivo no se pudo leer, regresa un mensaje de error
    // y el vector vacio
    std::cerr << "No se pudo abrir el archivo: " << name << std::endl;
    return vector;
  }
  return vector;
}

// LPS
vector<int> LPS(const vector<char> pattern) {
  int len = pattern.size();
  vector<int> lps(len, 0);
  int actualLen = 0;
  int i = 1;

  while (i < len) {
    if (pattern[i] == pattern[actualLen]) {
      actualLen++;
      lps[i] = actualLen;
      i++;
    } else {
      if (actualLen != 0) {
        actualLen = lps[actualLen - 1];
      } else {
        lps[i] = 0;
        i++;
      }
    }
  }

  return lps;
}

// KMP
void KMP(const vector<char> str, const vector<char> pattern) {
  if (str.size() < pattern.size()) {
    cout << "\tfalse" << endl;
  } else {
    // Arreglo LPS del patron a buscar
    vector<int> lps = LPS(pattern);
    // Longitud del patron
    int pLen = pattern.size();
    int i = 0;
    int j = 0;

    // Analiza que el patron se encutren dentro del texto principal
    while (i < str.size()) {
      if (str[i] == pattern[j]) {
        i++;
        j++;
      }

      // Si el patron se encuentra por completo en el texto principal, devuelve
      // "true" y la posición inicial del patron en el texto principal
      if (j == pLen) {
        cout << "\ttrue " << i - pLen + 1 << endl;
        break;
        // Si no se ha recorrido todo el patron y aun falta text por analizar,
        // pero j es diferente de 0 actualiza j, sino i avanza
      } else if (i < str.size() && pattern[j] != str[i]) {
        if (j != 0) {
          j = lps[j - 1];
        } else {
          i++;
        }
      }
      // Si ya se recorrio todo el texto principal y no se ha encontrado por
      // completo el patron, regresa un "false"
      if (i == str.size() && j != pLen) {
        cout << "\tfalse" << endl;
      }
    }
  }
}

// Longest palindrome
pair<int, int> manacher(const vector<char> str) {
  int n = str.size();
  // Si no hay cadena a analizar
  if (n == 0) {
    return make_pair(0, 0);
  }

  // Nueva cadena para tratar cadenas de longitud impar
  vector<char> newChain(2 * n + 1);
  for (int i = 0; i < n; i++) {
    newChain[2 * i] = '#';
    newChain[2 * i + 1] = str[i];
  }
  newChain[2 * n] = '#';

  int len = newChain.size();
  // Arreglo para almacenar la longitud de los palindromos
  vector<int> pLen(len, 0);
  // Centro y borde derecho del palindromo actual
  int center = 0, right = 0;
  for (int i = 0; i < len; i++) {
    // Espejo de i en relacion al centro
    int mirr = 2 * center - 1;

    // Verificamos si i está dentro del borde derecho actual
    if (i < right) {
      pLen[i] = min(right - i, pLen[mirr]);
    }

    // Expandimos al rededor de i
    int a = i + (1 + pLen[i]);
    int b = i - (1 + pLen[i]);
    while (a < len && b >= 0 && newChain[a] == newChain[b]) {
      pLen[i]++;
      a++;
      b--;
    }

    // Si el nuevo borde derecho excede el actual, actualizamos
    if (i + pLen[i] > right) {
      center = i;
      right = i + pLen[i];
    }
  }

  // Longitud y posicion del palindromo mas largo
  int maxLen = 0, centerIndex = 0;
  for (int i = 0; i < len; i++) {
    if (pLen[i] > maxLen) {
      maxLen = pLen[i];
      centerIndex = i;
    }
  }

  // posiciones inicial y final del palindromo
  int start = (centerIndex - maxLen) / 2 + 1;
  int end = start + maxLen - 1;

  return make_pair(start, end);
}

// Longest common substring
pair<int, int> findLongestCommonSubstring(const vector<char> str1,
                                          const vector<char> str2) {

  int m = str1.size();
  int n = str2.size();

  // Creamos una tabla para almacenar las longitudes de los substring comunes
  vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

  int mLen = 0; // Longitud del substring común más largo
  int end = 0; // Índice final del substring común más largo en el primer vector

  // Llenamos la tabla dp
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (str1[i - 1] == str2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        if (dp[i][j] > mLen) {
          mLen = dp[i][j];
          end = i - 1;
        }
      }
    }
  }

  // Si no se encontró un substring común, devolvemos -1
  if (mLen == 0) {
    return make_pair(-1, -1);
  }

  // Devolvemos la posición del substring en el primer vector
  int start = end - mLen + 1;
  return make_pair(start + 1, end + 1);
}

int main() {
  // Leemos los archivos y almacenamos su contenido en los vectores
  vector<char> transmission1 = readTXT("transmission1.txt");
  vector<char> transmission2 = readTXT("transmission2.txt");
  vector<char> mcode1 = readTXT("mcode1.txt");
  vector<char> mcode2 = readTXT("mcode2.txt");
  vector<char> mcode3 = readTXT("mcode3.txt");

  // KMP
  cout << "Parte 1" << endl;
  KMP(transmission1, mcode1);
  KMP(transmission1, mcode2);
  KMP(transmission1, mcode3);
  cout << endl;
  KMP(transmission2, mcode1);
  KMP(transmission2, mcode2);
  KMP(transmission2, mcode3);

  // Longest palindrome (manacher)
  cout << "Parte 2" << endl;
  pair<int, int> resultM1 = manacher(transmission1);
  cout << "\t" << resultM1.first << " " << resultM1.second << endl;

  pair<int, int> resultM2 = manacher(transmission2);
  cout << "\t" << resultM2.first << " " << resultM2.second << endl;

  // Longes common substring
  cout << "Parte 3" << endl;
  pair<int, int> resultLCS =
      findLongestCommonSubstring(transmission1, transmission2);
  cout << "\t" << resultLCS.first << " " << resultLCS.second << endl;
}

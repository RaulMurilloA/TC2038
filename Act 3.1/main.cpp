#include <bits/stdc++.h>
#include <iostream>

using namespace std;

/*Pruebas
  Prueba 1:
    5
    poca
    loco
    loca
    lapiz
    pozo
    3
    loco
    loca
    pozo
    lapiz
    loca
    loco
    poca
    pozo
    1
    1
    1

  Prueba 2:
    5
    apple
    banana
    app
    bat
    ball
    3
    app
    bat
    grape
    app
    apple
    ball
    banana
    bat
    1
    1
    0

  Prueba 3:
    6
    manzana
    banana
    pera
    naranja
    uva
    limon
    4
    manzana
    pera
    kiwi
    sandia
    banana
    limon
    manzana
    naranja
    pera
    uva
    1
    1
    0
    0

  Prueba 4:
    4
    perro
    gato
    pelota
    raton
    3
    gato
    pajaro
    raton
    gato
    pelota
    perro
    raton
    1
    0
    1
*/

// Estructura TRIE
struct TrieNode {
  bool isEndOfWord;
  TrieNode *children[27];

  TrieNode() {
    isEndOfWord = false;
    for (int i = 0; i < 26; ++i) {
      children[i] = nullptr;
    }
  }
};

// Función para insertar una palabra en el Trie
void insert(TrieNode *root, const string &word) {
  TrieNode *current = root;
  for (char c : word) {
    int index = c - 'a';
    if (!current->children[index]) {
      current->children[index] = new TrieNode();
    }
    current = current->children[index];
  }
  current->isEndOfWord = true;
}

// Función para buscar una palabra en el Trie
bool search(TrieNode *root, const string &word) {
  TrieNode *current = root;
  for (char c : word) {
    int index = c - 'a';
    if (!current->children[index]) {
      return false;
    }
    current = current->children[index];
  }
  return current != nullptr && current->isEndOfWord;
}

// Función para realizar un recorrido DFS del Trie
void dfs(TrieNode *node, string &currentWord) {
  if (node->isEndOfWord) {
    cout << currentWord << endl;
  }
  for (int i = 0; i < 26; ++i) {
    if (node->children[i]) {
      currentWord.push_back('a' + i);
      dfs(node->children[i], currentWord);
      currentWord.pop_back();
    }
  }
}

int main() {
  int N, M;
  cin >> N;
  // N palabras a insertar en la estructura
  TrieNode *root = new TrieNode();
  for (int i = 0; i < N; i++) {
    string word;
    cin >> word;
    insert(root, word);
  }

  cin >> M;
  // Arreglo booleano de los resultados
  bool array[M];
  // M palabras a buscar
  for (int i = 0; i < M; i++) {
    string word;
    cin >> word;
    bool found = search(root, word);
    array[i] = found;
  }

  // Recorrido DFS
  string currentWord;
  dfs(root, currentWord);

  // Resultados de la búsqueda
  for (int i = 0; i < M; i++) {
    cout << array[i] << endl;
  }

  // Liberamos memoria
  delete root;
}

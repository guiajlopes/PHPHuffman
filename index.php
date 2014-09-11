<?php

include_once 'HuffmanNode.inc';
include_once  'Huffman.inc';

define('FILE_PATH', 'texto.txt');



$values = getDicionary(FILE_PATH);
$huffman = new Huffman($values);
$huffman->buildTree();

echo '<pre>';
print_r($huffman->getRoot());
echo '</pre>';

/**
 * Realiza a leitura de um arquivo e transfere para um array de char.
 *
 * @param string $file_path
 *   Caminho do arquivo a ser lido.
 *
 * @return array
 *   Um Array de char ordenado contendo o dicionário do arquivo e suas respectivas frequencias.
 *
 * @see SplFileObject Class
 */
function getDicionary($file_path) {
  // Array contendo as palavras.
  $palavras = array();

  // Faz a leitura do arquivo.
  $file = new SplFileObject($file_path);
  // Percorre linhas a linha do arquivo.
  while (!$file->eof()) {
    $line = $file->fgetss();
    // Percorre letra a letra da linha.
    for ($i = 0; $i < strlen($line); $i++) {
      // Verifica se palavra já existe no dicionario.
      if (isset($palavras[$line[$i]])) {
        // Incrementa o contador da palavra.
        $palavras[$line[$i]] = $palavras[$line[$i]] + 1;
      }
      else {
        $palavras[$line[$i]] = 1;
      }
    }
  }

  arsort($palavras);
  return  $palavras;
}

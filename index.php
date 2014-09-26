<?php

include_once 'HuffmanNode.inc';
include_once  'Huffman.inc';

// Seta as constantes.
define('FILE_PATH', 'texto.txt');

$values = getDicionary(FILE_PATH);
$huffman = new Huffman($values);
$huffman->buildTree();
$huffman->codify($huffman->getRoot());


$root = $huffman->getRoot();

$codify_array = $huffman->getCodify();
$codifyFile = codifyFile(FILE_PATH, $codify_array, $values);

$name = 'codify.txt';
$file = fopen($name, 'w');
fwrite($file, $codifyFile);
fclose($file);

echo '<h1> Arquivo codificado </h1>';
echo '<div>';
echo $codifyFile;
echo '</div>';

/**
 * Codifica string para transferencia.
 *
 * @param string $file_path
 *  Path do arquivo que deve ser codificado.
 * @param array $codify_array
 *  Array com as codificações.
 * @param array $dicionary
 *  Array com o dicionario das palavras lidas no arquivo.
 *
 * @return string
 *  Retorna uma String contendo o dicionario serializado mais o arquivo codificado.
 *
 * @see SplFileObject Class
 */
function codifyFile($file_path, $codify_array, $dicionary) {
  $codifed = serialize($dicionary);
  // Faz a leitura do arquivo.
  $file = new SplFileObject($file_path);
  // Percorre linhas a linha do arquivo.
  while (!$file->eof()) {
    $line = $file->fgetss();
    // Percorre letra a letra da linha.
    for ($i = 0; $i < strlen($line); $i++) {
      // $escreve = fwrite($fp, $codify_array[$line[$i]]);
      $codifed .= $codify_array[$line[$i]];
    }
  }
  return $codifed;
}

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

<?php

//include_once 'index.php';
include_once 'HuffmanNode.inc';
include_once  'Huffman.inc';

$codifyString = '';

$codifyFile = new SplFileObject('codify.txt');
while (!$codifyFile->eof()) {
  $line = $codifyFile->fgetss();
  $codifyString .= $line;
}


echo '<h1> Arquivo decodificado </h1>';
echo '<div>';
echo decodeFile($codifyString);
echo '</div>';


/**
 * Function para decodificar arquivo.
 *
 * @param string $codifyFile.
 *  Arquivo codificado.
 *
 * @return string
 *  String decodificada.
 */
function decodeFile($codifyFile) {
  // Pega o Dicionario
  $file = explode('}' ,$codifyFile);
  $dicionary = $file[0] . '}';
  $dicionary = unserialize($dicionary);

  // Cria arvore a partir do dicionario.
  $huffman = new Huffman($dicionary);
  // Da um build na árvore
  $huffman->buildTree();

  // Pega a string do arquivo.
  $arquivo = $file[1];

  // echo $arquivo;

  return $huffman->decodeBinary(str_split($arquivo));
}

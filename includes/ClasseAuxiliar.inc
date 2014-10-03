<?php
namespace TrabalhoGA\Includes;
use SplFileObject;

class ClasseAuxiliar {
  private $file_path;
  private $razao_decode;

  function __construct($file_path = NULL) {
    if (!is_null($file_path)) {
      $this->file_path = $file_path;
    }
  }

  /**
   * Realiza a leitura de um arquivo e transfere para um array de char.
   *
   * @return array
   *   Um Array de char ordenado contendo o dicionário do arquivo e suas respectivas frequencias.
   *
   * @see SplFileObject Class
   */
  function getDicionary() {
    // Array contendo as palavras.
    $palavras = array();

    // Faz a leitura do arquivo.
    $file = new SplFileObject($this->file_path);
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

  /**
   * Codifica string para transferencia.
   *
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
  function codifyFile($codify_array, $dicionary) {
    $codifed = serialize($dicionary);
    // Faz a leitura do arquivo.
    $file = new SplFileObject($this->file_path);
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
   * Pega o valor médio da codificação
   *
   * @param array $codify_array
   *   Array contendo bits codificados.
   *
   * @return float
   *  Retorna um float contendo o valor medio da codificação.
   */
  function getValorMedio($codify_array) {
    $total = 0;
    foreach ($codify_array as $binary) {
      $total += strlen($binary);
    }

    return number_format($total / count($codify_array), 2);
  }

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
    $this->razao_decode = strlen($dicionary);
    $dicionary = unserialize($dicionary);

    // Cria arvore a partir do dicionario.
    $huffman = new Huffman($dicionary);
    // Da um build na árvore
    $huffman->buildTree();

    // Pega a string do arquivo.
    $arquivo = $file[1];
    $this->razao_decode += (strlen($arquivo) / 8);
    $this->razao_decode = number_format($this->razao_decode / filesize($this->file_path), 2);

    return $huffman->decodeBinary(str_split($arquivo));
  }

  function getRazao() {
    return $this->razao_decode;
  }

}

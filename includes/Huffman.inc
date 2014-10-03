<?php
namespace TrabalhoGA\Includes;

class Huffman {
  private $dicionary;
  private $stack;
  private $root;
  private $roots;
  private $right_element;
  private $codify_array;

  /**
   * Construtor de classe
   *
   * @param object $root
   *   Objeto do tipo BSTNode.
   */
  function __construct($dicionary) {
    $this->dicionary = $dicionary;

    $keys = array_keys($dicionary);
    // $this->right_element[$keys[0]] = array_shift($dicionary);
    $this->stack = $dicionary;
  }

  /**
   * Retorna o parametro com o array codificado
   *
   * @return array
   *   Array contendo codificação binária para as strings.
   */
  function getCodify() {
    return $this->codify_array;
  }


  /**
   * Verifica se está vazio.
   *
   * @return
   *   Retorna TRUE se estiver vazio e FALSE se não estiver.
   */
  public function isEmpty() {
    return empty($root);
  }

  /**
   * Método geter para pegar o elemento root.
   *
   * @return object
   *   Elemento raiz.
   */
  public function getRoot() {
    return $this->root;
  }

  /**
   * Monta a árvore de huffman.
   */
  public function buildTree() {
    while (!empty($this->stack)) {
      // Remove os dois ultimos elementos (menores) da pilha.
      $first_element = $this->removeFromStack();
      $second_element = $this->removeFromStack();

      $root_data = $first_element->data . $second_element->data;
      $root_frequencia = $first_element->frequencia + $second_element->frequencia;
      $root_element = new HuffmanNode($root_data, $root_frequencia);
      // Verifica qual a maior frequencia.
      if ($first_element->frequencia >= $second_element->frequencia) {
        $root_element->left = $first_element;
        $root_element->right = $second_element;
      }
      else {
        $root_element->right = $first_element;
        $root_element->left = $second_element;
      }

      // Verifica se a pilha está vazia.
      if (!empty($this->stack)) {
        // Adiciona na pilha.
        $this->stack[$root_element->data] = $root_element->frequencia;
        // Adiciona no array de raizes.
        $this->roots[$root_element->data] = $root_element;
      }
      else {
        $this->root = $root_element;
      }
    }

    // foreach ($this->right_element as $data => $frequencia) {
    //   $right_element = new HuffmanNode($data, $frequencia);
    //   $root_element = new HuffmanNode($this->root->data . $right_element->data, $this->root->frequencia + $right_element->frequencia);

    //   $root_element->left = $this->root;
    //   $root_element->right = $right_element;
    //   $this->root = $root_element;
    // }
  }

  /**
   * Codifica para binário.
   *
   * @param object $root
   *   Root da árvore.
   *
   * @param string $binary
   *   Codificação binária.
   */
  public function codify($root, $binary = NULL) {
    if (!empty($root->left)) {
      $this->codify($root->left, $binary . '1');
    }
    if (!empty($root->right)) {
      $this->codify($root->right, $binary . '0');
    }
    if (empty($root->right) && empty($root->left)) {
      $this->codify_array[$root->data] = $binary;
    }
  }

  /**
   * Decodify binary.
   *
   * @param string $binary
   *   Binário correspondente a posição na árvore.
   *
   * @return String
   *   String total do decode.
   */
  public function decodeBinary(&$binary, $string = NULL) {
    $root = $this->root;

    if (empty($binary)) {
      return nl2br($string);
    }


    if ($root->is_folha()) {
      $position = array_shift($binary);
    }
    else {
      while (!$root->is_folha()) {
        $position = array_shift($binary);
        if ($position == 1) {
          $root = $root->left;
        }
        else {
          $root = $root->right;
        }
      }
    }

    $string .= $root->data;

    return $this->decodeBinary($binary, $string);
  }

  /**
   * Remove elemento da pilha.
   */
  public function removeFromstack() {
    if (!empty($this->stack)) {
      // Ordena a fila.
      arsort($this->stack);
      // Pega as chaves do array.
      $keys = array_keys($this->stack);
      // Pega o menor elemento.
      $last_element = count($keys) - 1;
      $frequencia = array_pop($this->stack);
      $data = $keys[$last_element];

      if (!isset($this->roots[$data])) {
        $node =  new HuffmanNode($data, $frequencia);
        return $node;
      }
      return $this->roots[$data];
    }
    return FALSE;
  }
}

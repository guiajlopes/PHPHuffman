<?php

class Huffman {
  private $dicionary;
  private $stack;
  private $root;
  private $roots;

  /**
   * Construtor de classe
   *
   * @param object $root
   *   Objeto do tipo BSTNode.
   */
  function __construct($dicionary) {
    $this->dicionary = $dicionary;
    $this->stack = $dicionary;
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
   * Monta a árvore.
   */
  public function buildTree() {
    while (!empty($this->stack)) {
      $first_element = $this->removeFromStack();
      $second_element = $this->removeFromStack();

      $root_data = $first_element->data . $second_element->data;
      $root_frequencia = $first_element->frequencia + $second_element->frequencia;
      $root_element = new HuffmanNode($root_data, $root_frequencia);
      if ($first_element->frequencia >= $second_element->frequencia) {
        $root_element->left = $first_element;
        $root_element->right = $second_element;
      }
      else {
        $root_element->right = $first_element;
        $root_element->left = $second_element;
      }


      if (!empty($this->stack)) {
        $this->stack[$root_element->data] = $root_element->frequencia;
        $this->roots[$root_element->data] =  $root_element;
      }
      else {
        $this->root = $root_element;
      }
    }
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

<?php

class HuffmanNode {
  public $data;
  public $frequencia;
  public $left;
  public $right;

  /**
   * Construtor de classe.
   */
  public function __construct($data = NULL, $frequencia = NULL) {
    $this->data = $data;
    $this->left = NULL;
    $this->right = NULL;
    $this->frequencia = $frequencia;
  }
}

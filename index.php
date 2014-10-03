<?php
include_once 'includes/HuffmanNode.inc';
include_once  'includes/Huffman.inc';
include_once 'includes/ClasseAuxiliar.inc';
include_once 'vendor/autoload.php';

use TrabalhoGA\Includes\ClasseAuxiliar;
use TrabalhoGA\Includes\Huffman;

\Slim\Slim::registerAutoloader();

$loader = new Twig_loader_Filesystem('templates');
$twig = new Twig_Environment($loader);
$app = new \Slim\Slim();

define('FILE_PATH', 'texto.txt');

$app->get('/', function() use ($app, $twig){
  echo $twig->render('index.html');
});

$app->get('/decode', function() use ($app, $twig) {
  $codifyString = '';

  $codifyFile = new \SplFileObject('codify.txt');
  while (!$codifyFile->eof()) {
    $line = $codifyFile->fgetss();
    $codifyString .= $line;
  }

  echo $twig->render('decode.html', array('body' => ClasseAuxiliar::decodeFile($codifyString)));
});

$app->get('/encode', function () use ($app, $twig) {
  $classe_auxiliar = new ClasseAuxiliar(FILE_PATH);
  $dicionary = $classe_auxiliar->getDicionary();
  $huffman = new Huffman($dicionary);
  $huffman->buildTree();
  $huffman->codify($huffman->getRoot());

  $root = $huffman->getRoot();

  $codify_array = $huffman->getCodify();

  $codifyFile = $classe_auxiliar->codifyFile($codify_array, $dicionary);

  $name = 'codify.txt';
  $file = fopen($name, 'w');
  fwrite($file, $codifyFile);
  fclose($file);

  echo $twig->render('encode.html', array(
    'arquivo' => $codifyFile,
    'tamanho' => $classe_auxiliar->getValorMedio($codify_array),
  ));
});

$app->run();


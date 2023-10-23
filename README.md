# sb-montador
Repositório para o trabalho 1 da disciplina de Software Básico 2023.2, UnB

## Integrantes
**Luca Delpino Barbabella - 180125559**  
**Lucca Beserra Huguet - 160013259**  

## Sistema operacional utilizado
Distro: Pop!_OS 22.04 LTS
Kernel: 6.5.4-76060504-generic

## Versões
**C++17**
**g++ 11.4.0**

## Instruções de compilação
```
$ gcc montador.cpp -lstdc++ -o montador
$ g++ simulador.cpp -o simulador

```

## Funcionamento do programa: Caso .asm


```
$ ./montador myprogram.asm
```

O programa recebe o arquivo de entrada (com extensão) por argumento na linha de comando . 
O programa dá como saída o arquivo com o mesmo nome MUDANDO a extensão para .obj

## Funcionamento do programa: Caso .mcr

Caso o arquivo de entrada tenha extensão “.mcr”, o montador irá chamar uma passagem
de pre-processamento onde irá processar as macros.
Esse modo irá gerar dois arquivos:
- myprogram.pre
- myprogram.obj  

O arquivo .pre se trata do arquivo pré-processado com macros tratadas e o arquivo .obj é o código objeto

## Rodando o simulador

Após compilar o simulador conforme indicado, escreva o seguinte no terminal para executá-lo:
```
$ ./simulador arquivo_obj.obj
```
Onde "arquivo_obj.obj" é o arquivo objeto gerado pelo montador.



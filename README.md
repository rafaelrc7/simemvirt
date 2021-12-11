# Simulador de memória virtual
Segundo trabalho de INF1316

## Alunos

- Rafael Ribeiro de Carvalho (2011104)
- Pedro Piquet Fernandes de Sousa (2011040)
- Paulo de Saldanha da Gama de Moura Vianna (2020704)

## Descrição do código

### Estrutura da dados
#### Memória Física
A memória física é representada por um array de structs do tipo frame. O struct guarda informações como os bits M e R (este tratado pelo algorítimo usado).

#### Page Table
A Page table é implementada como um array de structs de page, que guardam o endereço na memória física onde está carregada, se tiver carregada.

### Módulos

#### Algorítimos
Existem 3 módulos que representam cada algorítimo, FIFO 2nd chance (second-chance.c), NRU (nru.c), LFU (lfu.c).

#### Main
O processamento dos argumentos e do arquivo acontecem na main. O arquivo é lido em loop até chegar ao seu fim.

#### Linked List
Para o FIFO 2nd chance foi implementado um simples módulo de linked list que é usado para implementar a fila.

#### Mem-simu
Este módulo implementa o swapin e swapout nas estruturas de dados que representam a memória.

## Execução dos códigos

### LFU

#### compilador.log

```
./sim-virtual LFU compilador.log 8 16

Page faults: 2404
Page writes: 210

./sim-virtual LFU compilador.log 32 16

Page faults: 1785
Page writes: 742
```

#### compressor.log

```
./sim-virtual LFU compressor.log 8 16

Page faults: 255
Page writes: 0

./sim-virtual LFU compressor.log 32 16

Page faults: 172
Page writes: 0
```


#### matriz.log

```
./sim-virtual LFU matriz.log 8 16

Page faults: 2214
Page writes: 150

./sim-virtual LFU matriz.log 32 16

Page faults: 1811
Page writes: 1055
```


#### simulador.log

```
./sim-virtual LFU simulador.log 8 16

Page faults: 3468
Page writes: 1231


./sim-virtual LFU simulador.log 32 16

Page faults: 2678
Page writes: 1903
```



### NRU


#### compilador.log

```
./sim-virtual NRU compilador.log 8 16

page faults: 2530
page writes: 0


./sim-virtual NRU compilador.log 32 16

page faults: 38601
page writes: 620
```


#### compressor.log

```
./sim-virtual NRU compressor.log 8 16

Page faults: 255
Page writes: 0


./sim-virtual NRU compressor.log 32 16

Page faults: 172
Page writes: 0
```


#### matriz.log

```
./sim-virtual NRU matriz.log 8 16

Page faults: 4260
Page writes: 0


./sim-virtual NRU matriz.log 32 16

Page faults: 35558
Page writes: 1613
```


#### simulador.log

```
./sim-virtual NRU simulador.log 8 16

Page faults: 33261
Page writes: 0


./sim-virtual NRU simulador.log 32 16

Page faults: 59651
Page writes: 5812
```



### FIFO2


#### compilador.log

```
./sim-virtual FIFO2 compilador.log 8 16

Page faults: 2392
Page writes: 163


./sim-virtual FIFO2 compilador.log 32 16

Page faults: 3420
Page writes: 837
```


#### compressor.log

```
./sim-virtual FIFO2 compressor.log 8 16

Page faults: 255
Page writes: 0


./sim-virtual FIFO2 compressor.log 32 16

Page faults: 172
Page writes: 0
```


#### matriz.log

```
./sim-virtual FIFO2 matriz.log 8 16

Page faults: 2214
Page writes: 74

./sim-virtual FIFO2 matriz.log 32 16

Page faults: 1982
Page writes: 651
```


#### simulador.log

```
./sim-virtual FIFO2 simulador.log 8 16

Page faults: 3436
Page writes: 978


./sim-virtual FIFO2 simulador.log 32 16

Page faults: 3067
Page writes: 1402
```


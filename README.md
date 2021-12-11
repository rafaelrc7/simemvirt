# Simulador de memória virtual
Segundo trabalho de INF1316

## Alunos

- Rafael Ribeiro de Carvalho (2011104)
- Pedro Piquet Fernandes de Sousa (2011040)
- Paulo de Saldanha da Gama de Moura Vianna (2020704)


## Execução dos códigos

### LFU

#### compilador.log

./sim-virtual LFU compilador.log 8 16

Page faults: 2404
Page writes: 210

./sim-virtual LFU compilador.log 32 16

Page faults: 1785
Page writes: 742

compressor.log

./sim-virtual LFU compressor.log 8 16

Page faults: 255
Page writes: 0

./sim-virtual LFU compressor.log 32 16

Page faults: 172
Page writes: 0


matriz.log

./sim-virtual LFU matriz.log 8 16

Page faults: 2214
Page writes: 150

./sim-virtual LFU matriz.log 32 16

Page faults: 1811
Page writes: 1055


simulador.log

./sim-virtual LFU simulador.log 8 16

Page faults: 3468
Page writes: 1231


./sim-virtual LFU simulador.log 32 16

Page faults: 2678
Page writes: 1903



### NRU


compilador.log

./sim-virtual NRU compilador.log 8 16

page faults: 2530
page writes: 0


./sim-virtual NRU compilador.log 32 16

page faults: 38601
page writes: 620


compressor.log

./sim-virtual NRU compressor.log 8 16

Page faults: 255
Page writes: 0


./sim-virtual NRU compressor.log 32 16

Page faults: 172
Page writes: 0


matriz.log

./sim-virtual NRU matriz.log 8 16

Page faults: 4260
Page writes: 0


./sim-virtual NRU matriz.log 32 16

Page faults: 35558
Page writes: 1613


simulador.log

./sim-virtual NRU simulador.log 8 16

Page faults: 33261
Page writes: 0


./sim-virtual NRU simulador.log 32 16

Page faults: 59651
Page writes: 5812


### FIFO2


compilador.log

./sim-virtual FIFO2 compilador.log 8 16

Page faults: 2207
Page writes: 132


./sim-virtual FIFO2 compilador.log 32 16

Page faults: 1356
Page writes: 432


compressor.log

./sim-virtual FIFO2 compressor.log 8 16

Page faults: 255
Page writes: 0


./sim-virtual FIFO2 compressor.log 32 16

Page faults: 172
Page writes: 0


matriz.log

./sim-virtual FIFO2 matriz.log 8 16

Page faults: 2144
Page writes: 30


./sim-virtual FIFO2 matriz.log 32 16

Page faults: 1509
Page writes: 460


simulador.log

./sim-virtual FIFO2 simulador.log 8 16

Page faults: 2973
Page writes: 694


./sim-virtual FIFO2 simulador.log 32 16

Page faults: 2112
Page writes: 1002

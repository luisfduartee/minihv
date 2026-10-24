# MiniHV - Escopo 25

Hipervisor monolítico desenvolvido em C11 estrito para a unidade curricular.

## Funcionalidades Implementadas
- **Arquitetura**: C11 estrito (-std=c11 -Wall -Wextra -Werror -pedantic), sem *warnings* nem fugas de memória.
- **Escalonamento**: Política LOTTERY (=5$), suporte a 1 pCPU e até 4 VMs.
- **Gestão de Memória**: Paginação PAG com algoritmo de substituição NRU e cota local.
- **Armazenamento**: Algoritmo de disco LOOK.
- **Logs e Extra**: Registo de eventos em JSONL (minihv_output.jsonl) e funcionalidade de SNAPSHOT (minihv_snapshot.jsonl).

## Como Compilar e Executar
Certifica-te de que tens o GCC instalado e corre:
`ash
make
./minihv.exe
`
